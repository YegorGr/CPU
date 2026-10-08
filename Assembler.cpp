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

int main (int argc, char* argv[])
{
    FileInfo data = GetFileInfo(argc, argv);   

    char executable[] = "ExecutableCode.asm";

    data.file = fopen(executable, "w");
    if (data.file == NULL) 
    {
        fprintf(stderr, "Failed to open output file\n");
        return 1;
    }


    


}

void RunAssembler (FileInfo* data)
{



    while (size_t i = 0; i < data->size_array; i++)
    {
        char command[MAX_LEN] = {};
        double value          = NAN;
        double command_number = 0;

        char* ptr = data->buffer;

        int argcscan = sscanf(ptr, "%s %lf", &command, &value) < 2;

        ptr = strchr(ptr, '\n');

        command_number = CommandToNum(&command);

        data->true_buffer[i] = command_number;

        if (argcscan == 2)
        {
            i++;
            data->true_buffer[i] = value;
        }
    }
}

double CommandToNum (char* command)
{
    if strcasecmp("HLT", command)
        return 0lf;
    
    if strcasecmp("PUSH", command)
        return 1lf;

    if strcasecmp("ADD", command)
        return 2lf;
    
    if strcasecmp("ADD", command)
        return 3lf;
    
    if strcasecmp("DIV", command)
        return 4lf;
    
    if strcasecmp("MUL", command)
        return 5lf;

    if strcasecmp("OUT", command)
        return 6lf;

    fprintf(stderr, "Incorrect command!");
    abort();
}
