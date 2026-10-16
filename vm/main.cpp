#include "stack.h"
#include "vm.h"
#include "fileinfo.h"

#include <stdio.h> 
#include <stdlib.h>

int main (int argc, const char* argv[])
{
    FileInfo data = GetFileInfo(argc, argv);  

    CheckHeader(&data);
    
    stack_t stk1 = {};
    StackInit(&stk1, 40);
    
    cpu cpu_data = {};

    cpu_data.capacity    = data.real_size - SIGNATURESIZE;
    cpu_data.buffer      = data.buffer + SIGNATURESIZE;
    cpu_data.pc          = 0;
    cpu_data.cpu_stack   = &stk1;

    RunVm(&cpu_data);

    StackDestroy(cpu_data.cpu_stack);

    free(data.buffer);

    getchar();
}