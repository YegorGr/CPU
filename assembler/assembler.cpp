#include "assembler.h"
#include "fileinfo.h"

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

void RunAssembler (FileInfo* data)
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
    ssize_t byte_count = 0;
    bool is_running    = true;

    while (is_running == true)
    {
        char command[MAX_LEN] = {};
        double value          = NAN;

        int argcscan = sscanf(ptr, "%s %lf", command, &value);

        if (argcscan <= 0)
            break;

        data->true_buffer[byte_count] = CommandToNum(command); // why bite_count++???
        byte_count++;

        if (argcscan == 2)
        {
            memcpy(&data->true_buffer[byte_count], &value, sizeof(double));
            byte_count += sizeof(double);
        }

        char* next = strchr(ptr, '\n');

        if (next != NULL)
            ptr = next + 1;
        else
            is_running = false;
    }

    data->size_code   = byte_count;
    data->true_buffer = (char*) realloc(data->true_buffer, data->size_code);
}

char CommandToNum (char* command)
{
    if (strcasecmp("HLT", command) == 0)
        return 0;
    
    if (strcasecmp("PUSH", command) == 0)
        return 1;

    if (strcasecmp("ADD", command) == 0)
        return 2;
    
    if (strcasecmp("SUB", command) == 0)
        return 3;
    
    if (strcasecmp("DIV", command) == 0)
        return 4;
    
    if (strcasecmp("MUL", command) == 0)
        return 5;

    if (strcasecmp("OUT", command) == 0)
        return 6;

    fprintf(stderr, "Incorrect command!");
    abort();
}