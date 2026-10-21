#pragma once 

#include "fileinfo.h"
#include <stdint.h>

const int MAX_LEN = 64;
const int MAX_NAME_MARK = 16;
const int MAX_MARKS = 500;

struct Label {
    char name [MAX_NAME_MARK];
    uint16_t address;
};

int  RunAssembler     (FileInfo* data);
int  AssemblerLine    (FileInfo* data, char* line, char* out, size_t* byte_count);

void AddVersionToFile (FileInfo* data, size_t* byte_count);

int  SkipNoLabels     (FileInfo* data, char* ptr, size_t* byte_count);
int  RunLabels        (FileInfo* data);

int  FindLabel        (FileInfo* data, const char* name);