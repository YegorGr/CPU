#pragma once 

#include "fileinfo.h"

const int MAX_LEN = 5;

int RunAssembler (FileInfo* data);
int AssembleLine (char* line, char* out, size_t* byte_count);
