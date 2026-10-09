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


int main (int argc, const char* argv[])
{
    FileInfo data = GetFileInfo(argc, argv);   

    char executable[] = "ExecutableCode.txt";

    data.file = fopen(executable, "wb");
    if (data.file == NULL) 
    {
        fprintf(stderr, "Failed to open output file\n");
        return 1;
    }

    RunAssembler(&data);

    size_t c_written = fwrite(data.true_buffer, sizeof(char), data.size_code, data.file);

    if (c_written != data.size_code)
        fprintf(stderr, "Error of write to file!");
    else
        printf("Success write to file!");

    fclose(data.file);

    free(data.true_buffer);
    free(data.buffer);
}