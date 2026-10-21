#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>
#include <math.h>

#include "assembler.h"
#include "fileinfo.h"
#include "commands.h"

int RunAssembler (FileInfo* data)
{
    assert(data != NULL);
    assert(data->buffer != NULL);

    data->true_buffer = (char*) calloc(data->size_array, sizeof(double));

    if (data->true_buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed for true_buffer!\n");
        return -1;
    }

    char* ptr          = data->buffer;
    char* end          = data->buffer + data->real_size;
    size_t byte_count  = 0;
    
    AddVersionToFile (data, &byte_count);

    while (ptr < end)
    {
        if (*ptr == '\0')
        {
            ptr++;
            continue;
        }
        
        if (AssemblerLine(data, ptr, data->true_buffer, &byte_count) != 0)
            return -1;

        ptr += strlen(ptr) + 1; 
    }

    data->size_code   = byte_count;
    data->true_buffer = (char*) realloc(data->true_buffer, data->size_code);

    return 0;
}

int AssemblerLine (FileInfo* data, char* line, char* out, size_t* byte_count)
{
    char command  [MAX_LEN] = {};
    char argument [MAX_LEN] = {};

    int argsscan = sscanf(line, "%63s %63s", command, argument);

    if (argsscan <= 0)
        return 0;
    
    const CommandInfo* info = CommandToNum(command);

    if (info == NULL)
    {
        fprintf(stderr, "Unknown command [%s]\n", command);
        return -1;
    }

    if ((info->arg == ARG_NUMBER || info->arg == ARG_REG || info->arg == ARG_MARK) && argsscan != 2)
    {
        fprintf(stderr, "There are to few or many arguments or the second argument is not correct!");
        return -1;
    }

    if (info->arg == ARG_NONE && argsscan != 1)
    {
        fprintf(stderr, "The command [%s] needs no arguments!", info->name);
        return -1;
    }

    out[*(byte_count)] = (char) info->code;
    (*byte_count)++;

    if (info->arg == ARG_NUMBER)
    {
        double value = NAN;
        sscanf(argument, "%lf", &value);

        memcpy(&out[*byte_count], &value, sizeof(double));
        *byte_count += sizeof(double);
    }

    if (info->arg == ARG_REG)
    {
        char reg = (char) RegisterToNum(argument);

        if (reg < 0 || reg >= REGS_COUNT)
        {
            fprintf(stderr, "Unknown register!");
            return -1;
        }

        out[(*byte_count)] = reg; 
        (*byte_count)++;
    }

    if (info->arg == ARG_MARK)
    {
        int label_index = FindLabel(data, argument);

        if (label_index == -1) 
        {
            fprintf(stderr, "Unknown label [%s]\n", argument);
            return -1;
        }

        uint16_t address = data->LabelsPtr[label_index].address;
        
        memcpy(&out[*byte_count], &address, sizeof(uint16_t));
        *byte_count += sizeof(uint16_t);
    }
    
    return 0;
}

void AddVersionToFile (FileInfo* data, size_t* byte_count)
{
    const char signature [] = {'D', 'D', 'X', '1'};

    memcpy(data->true_buffer, signature, sizeof(signature));

    size_t byte_shift = sizeof(signature) / sizeof(signature[0]);

    *byte_count  = byte_shift;
}

int RunLabels (FileInfo* data)
{
    assert(data != NULL);
    assert(data->buffer != NULL);

    char*  ptr        = data->buffer;
    char*  end        = data->buffer + data->real_size;
    size_t byte_count = SIGNATURESIZE;

    while (ptr < end)
    {
        char* line_end = strchr(ptr, '\n');
        if (line_end == NULL)
            line_end = end;      
        *line_end = '\0';

        char* comment = strchr(ptr, ';');
        if (comment != NULL)
            memset(comment, '\0', (size_t)(line_end - comment));

        char* label = strchr(ptr, ':');
        if (label != NULL)
        {
            *label = '\0';

            char* name_start = ptr;
            while (isspace(*name_start)) 
                name_start++;

            size_t len = strlen(name_start);

            while (len > 0 && isspace(name_start[len - 1]))
                name_start[--len] = '\0';

            strncpy(data->LabelsPtr[data->index].name, name_start, MAX_NAME_MARK - 1);
            data->LabelsPtr[data->index].address = byte_count;
            data->index++;
        
            memset(ptr, '\0', (size_t)(line_end - ptr));
        }
       else if (*ptr != '\0')
        {
            if (SkipNoLabels(data, ptr, &byte_count) != 0)
                return -1;
        }

        ptr = line_end + 1;
    }

    return 0;
}

int SkipNoLabels (FileInfo* data, char* ptr, size_t* byte_count)
{
    char command  [MAX_LEN] = {};
    char argument [MAX_LEN] = {};

    int argsscan = sscanf(ptr, "%63s %63s", command, argument);

    if (argsscan <= 0)
        return 0;
    
    const CommandInfo* info = CommandToNum(command);

    if (info == NULL)
    {
        fprintf(stderr, "Unknown command [%s]\n", command);
        return -1;
    }

    if ((info->arg == ARG_NUMBER || info->arg == ARG_MARK || info->arg == ARG_REG || info->arg == ARG_MARK) && argsscan != 2)
    {
        fprintf(stderr, "There are to few or many arguments or the second argument is not correct!");
        return -1;
    }

    if (info->arg == ARG_NONE && argsscan != 1)
    {
        fprintf(stderr, "The command [%s] needs no arguments!", info->name);
        return -1;
    }

    (*byte_count)++;

    if (info->arg == ARG_NUMBER)
        *byte_count += sizeof(double);

    if (info->arg == ARG_MARK)
        *byte_count += sizeof(uint16_t);

    if (info->arg == ARG_REG)
        *byte_count += sizeof(char);

    return 0;
}

int FindLabel (FileInfo* data, const char* name)
{
    for (int i = 0; i < data->index; i++) 
    {
        if (strcmp(data->LabelsPtr[i].name, name) == 0)
            return i;
    }

    return -1;
}