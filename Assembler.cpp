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

    
}