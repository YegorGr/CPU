#include "Stack.h"
#include "VM.h"

#include <stdio.h> 
#include <stdlib.h>

int main()
{
    double data[] = {1, 30.000, 1, 800, 2, 6, 0};
    size_t code_size = sizeof(data) / sizeof(data[0]);

    stack_t cpu_stack = {};
    StackInit(&cpu_stack, 40);

    cpu_data cpu = {};

    cpu.capacity    = code_size;
    cpu.buffer      = data;
    cpu.pc          = 0;
    cpu.cpu_stack   = &cpu_stack;

    RunCpu(&cpu);

    StackDestroy(&cpu_stack);

    getchar();
}