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

int OpenAndGetName (int argc, const char** argv)
{
    int descriptor = -1;

    if (argc >= 2)
        descriptor = OpenFile(argv[1]);
    else 
    {
        char* filename = GetFileName();
        descriptor     = OpenFile(filename);
        free(filename);
    }

    return descriptor;
}

FileInfo GetFileInfo (int argc, const char** argv)
{
    FileInfo data = {};

    data.descriptor = OpenAndGetName (argc, argv);
    data.size_array = FileSize       (data.descriptor);
    data.buffer     = CopyFromFile   (data.descriptor, data.size_array);

    close(data.descriptor);

    return data;
}

char* GetFileName(void)
{
    const int MAXNAME = 256;
    const int MAXTRIES = 3;
    int tries = 0;

    char* filename = (char*) calloc(MAXNAME, sizeof(char));

    printf(HINT "\nWrite the file name for sorting the lines.");

    while(tries < MAXTRIES)
    {
        printf(HINT "\nTries left: %d" HINT
              "\nFilename (" SUCCESS "name.txt" HINT "): " RESET, MAXTRIES - tries);

        if (fgets(filename, MAXNAME, stdin) != NULL)
        {
            filename[strcspn(filename, "\r\n")] = '\0';
            return filename;
        }

        tries++;
    }

    return NULL;
}

int OpenFile (const char* filename) 
{
    int descriptor = open(filename, _O_RDONLY);

    if (descriptor == -1)
    {
        fprintf(stderr, PART_C "\n%s" RESET, strerror(errno));
        abort();
    }

    return descriptor;
}

size_t FileSize (int descriptor)
{
    assert(descriptor != -1);

    struct stat mystat = {};
    fstat(descriptor, &mystat);

    size_t size_array = mystat.st_size + 2;

    return size_array;
}

char* CopyFromFile (int descriptor, size_t size_array)
{
    char* buffer     = (char*) (calloc(size_array, sizeof(char)));
    size_t real_size = read(descriptor, buffer, size_array);

    memset(&buffer[real_size], 0, size_array - real_size);

    return buffer;
}