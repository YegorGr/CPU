#include "Assembler.h"
#include "Fileinfo.h"

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

int main (int argc, const char* argv[])
{
    FileInfo data = GetFileInfo(argc, argv);   

    char executable[] = "ExecutableCode.txt";

    data.file = fopen(executable, "w");
    if (data.file == NULL) 
    {
        fprintf(stderr, "Failed to open output file\n");
        return 1;
    }

    RunAssembler(&data);

    fwrite(data.true_buffer, sizeof(double), data.size_code, data.file);
    
    fclose(data.file);

    free(data.true_buffer);
    free(data.buffer);
}

void RunAssembler (FileInfo* data)
{
    assert(data != NULL);
    assert(data->buffer != NULL);

    bool is_running = true;

    char command[MAX_LEN] = {};
    double value          = NAN;
    double command_number = 0;


    data->true_buffer = (double*) calloc(data->size_array, sizeof(double));
    if (data->true_buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed for true_buffer!\n");
        abort();
    }

    char* ptr  = data->buffer;
    assert(ptr != NULL);

    for (size_t i = 0; i < data->size_array && is_running; i++)
    {
        char* next = strchr(ptr, '\n');
        
        command[MAX_LEN] = {};
        value = NAN;

        int argcscan = sscanf(ptr, "%s %lf", command, &value);

        command_number = CommandToNum(command);

        data->true_buffer[i] = command_number;

        if (argcscan == 2)
        {
            i++;
            data->true_buffer[i] = value;
        }

        ptr = next + 1;

        if (next == NULL)
            is_running = false;

        data->size_code = i;
    }

    data->true_buffer = (double*) realloc(data->true_buffer, data->size_code);
}

double CommandToNum (char* command)
{
    if (strcasecmp("HLT", command) == 0)
        return 0.0;
    
    if (strcasecmp("PUSH", command) == 0)
        return 1.0;

    if (strcasecmp("ADD", command) == 0)
        return 2.0;
    
    if (strcasecmp("SUB", command) == 0)
        return 3.0;
    
    if (strcasecmp("DIV", command) == 0)
        return 4.0;
    
    if (strcasecmp("MUL", command) == 0)
        return 5.0;

    if (strcasecmp("OUT", command) == 0)
        return 6.0;

    fprintf(stderr, "Incorrect command!");
    abort();
}
