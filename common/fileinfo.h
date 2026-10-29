#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>

struct Label;

#define HINT    "\x1b[93m"            //!< Sand color (yellow but light yellow)
#define SUCCESS "\x1b[38;5;46m"       //!< Bright green color (specially for success)
#define BOLD    "\x1b[1m"             //!< Very fat (like me)
#define RESET   "\x1b[0m"             //!< To reset style
#define PART_C  "\x1b[38;5;203m"      //!< Bright red color

typedef struct {
    int     descriptor;
    size_t  size_array;
    size_t  size_code;
    ssize_t  real_size;
    char*   buffer;
    char*   true_buffer;
    FILE*   file;
    Label*  LabelsPtr;
    int     index;
} FileInfo;

int      OpenAndGetName  (int argc, const char** argv);
FileInfo GetFileInfo     (int argc, const char** argv);

char*    GetFileName     (void);
int      OpenFile        (const char* filename);
size_t   FileSize        (int descriptor);
char*    CopyFromFile    (int descriptor, size_t size_array, FileInfo* data);