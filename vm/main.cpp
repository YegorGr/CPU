#include "stack.h"
#include "vm.h"
#include "fileinfo.h"

#include <stdio.h> 
#include <stdlib.h>

int main (int argc, const char* argv[])
{
    FileInfo data = GetFileInfo(argc, argv);  

    if (CheckHeader(&data) != 0) 
    {
         free(data.buffer); 
         return -1; 
    }    
    stack_t stk1 = {};
    stack_t stk2 = {};
    StackInit(&stk1, 40);
    StackInit(&stk2, 20);
    
    cpu cpu_data = {};

    cpu_data.capacity    = data.real_size - SIGNATURESIZE;
    cpu_data.buffer      = data.buffer + SIGNATURESIZE;
    cpu_data.pc          = 0;
    cpu_data.cpu_stack   = &stk1;
    cpu_data.cpu_return  = &stk2;

    RunVm(&cpu_data);

    StackDestroy(cpu_data.cpu_stack);
    StackDestroy(cpu_data.cpu_return);

    free(data.buffer);

    getchar();
}