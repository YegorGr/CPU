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

Label Labels[MAX_MARKS] = {};

int main (int argc, const char* argv[])
{
    FileInfo data = GetFileInfo(argc, argv);   

    char executable[] = "ex_code.bin";

    data.LabelsPtr = Labels;

    if (RunLabels(&data) != 0 || RunAssembler(&data) != 0)
    {
        fprintf(stderr, "Assembling failed\n");
        free(data.true_buffer);
        free(data.buffer);
        
        return 1;
    }

    data.file = fopen(executable, "wb");
    if (data.file == NULL)
    {
        fprintf(stderr, "Failed to open output file\n");
        free(data.true_buffer);
        free(data.buffer);

        return 1;
    }

    size_t c_written = fwrite(data.true_buffer, sizeof(char), data.size_code, data.file);

    if (c_written != data.size_code)
        fprintf(stderr, "Error of write to file!");
    else
        printf("Success write to file!");

    fclose(data.file);

    free(data.true_buffer);
    free(data.buffer);
}