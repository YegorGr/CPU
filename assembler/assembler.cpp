#include "assembler.h"
#include "fileinfo.h"
#include "commands.h"

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

int RunAssembler (FileInfo* data)
{
    assert(data != NULL);
    assert(data->buffer != NULL);

    data->true_buffer = (char*) calloc(data->size_array, sizeof(double));

    if (data->true_buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed for true_buffer!\n");
        abort();
    }

    char* ptr          = data->buffer;
    size_t byte_count  = 0;

    while (*ptr != '\0')
    {
        char* end_str = strchr(ptr, '\n');

        if (end_str != NULL)
            *end_str = '\0';
        
        if (*ptr != '\0')
        {
            if (AssemblerLine(ptr, data->true_buffer, &byte_count) != 0)
                return -1;
        }
        
        if (end_str == NULL)
            break;

        ptr = end_str + 1;
    }

    data->size_code   = byte_count;
    data->true_buffer = (char*) realloc(data->true_buffer, data->size_code);

    return 0;
}

int AssemblerLine (char* line, char* out, size_t* byte_count)
{
    char* comment = strchr(line, ';');
    if (comment != NULL)
        *comment = '\0';

    char command  [MAX_LEN] = {};
    char argument [MAX_LEN] = {};

    int argsscan = sscanf(line, "%255s %255s", command, argument);

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
            abort();
        }

        out[(*byte_count)] = reg; 
        (*byte_count)++;
    }
    
    return 0;
}