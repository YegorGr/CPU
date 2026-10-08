#pragma once

#include <ctype.h>

#define HINT    "\x1b[93m"            //!< Sand color (yellow but light yellow)
#define SUCCESS "\x1b[38;5;46m"       //!< Bright green color (specially for success)
#define BOLD    "\x1b[1m"             //!< Very fat (like me)
#define RESET   "\x1b[0m"             //!< To reset style
#define PART_C  "\x1b[38;5;203m"      //!< Bright red color

typedef struct {
    int     descriptor;
    size_t  size_array;
    char*   buffer;
    double* true_buffer;
    FILE*   file;
} FileInfo;

int      OpenAndGetName  (int argc, const char** argv);
FileInfo GetFileInfo     (int argc, const char** argv);

char*    GetFileName     (void);
int      OpenFile        (const char* filename);
size_t   FileSize        (int descriptor);
char*    CopyFromFile    (int descriptor, size_t size_array);