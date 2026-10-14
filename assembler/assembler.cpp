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

    while (ptr != NULL && *ptr != '\0')
    {
        char* end_str = strchr(ptr, '\n');

        if (end_str != NULL)
            *end_str = '\0';
        
        if (AssembleLine(ptr, data->true_buffer, &byte_count) != 0)
            return -1;
        
        if (end_str == NULL)
            break;

        ptr = end_str + 1;
    }

    data->size_code   = byte_count;
    data->true_buffer = (char*) realloc(data->true_buffer, data->size_code);

    return 0;
}

int AssembleLine (char* line, char* out, size_t* byte_count)
{
    char* comment = strchr(line, ';');
    if (comment != NULL)
        *comment = '\0';

    char word   [MAX_LEN] = {};
    double value          = 0;

    int argsscan = sscanf(line, "%s %lf", word, &value);

    if (argsscan <= 0)
        return 0;
    
    const CommandInfo* info = CommandToNum(word);

    if (info == NULL)
    {
        fprintf(stderr, "Unknown command [%s]\n", word);
        return -1;
    }

    if ((info->arg == ARG_NUMBER || info->arg == ARG_REG || info->arg == ARG_MARK) && argsscan != 2)
    {
        fprintf(stderr, "There are to few or many arguments or the second argument is not a nubmer");
        return -1;
    }

    if (info->arg == ARG_NONE && argsscan != 1)
    {
        fprintf(stderr, "The command [%s] needs no arguments!", info->name);
        return -1;
    }

    out[*(byte_count)] = (char) info->number;
    (*byte_count)++;

    if (info->arg == ARG_NUMBER)
    {
        memcpy(&out[*byte_count], &value, sizeof(double));
        *byte_count += sizeof(double);
    }
    
    return 0;
}