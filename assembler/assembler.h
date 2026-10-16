#pragma once 

#include "fileinfo.h"

const int MAX_LEN = 5;
const int MAX_MARKS = 500;

int  RunAssembler     (FileInfo* data);
int  AssemblerLine    (FileInfo* data, char* line, char* out, size_t* byte_count);

void AddVersionToFile (FileInfo* data, size_t* byte_count);

int  SkipNoLabels     (FileInfo* data, char* ptr, size_t* byte_count);
void RunLabels        (FileInfo* data);