#pragma once

#include "stack.h"
#include <stddef.h>

enum Commands {
    HLT  = 0,
    PUSH = 1,
    ADD  = 2,
    SUB  = 3,
    DIV  = 4,
    MUL  = 5,
    OUT  = 6,
};

struct cpu_data {
    stackelem_t* buffer;
    size_t       capacity;
    size_t       pc;
    stack_t*     cpu_stack;
};

void RunCpu(cpu_data* cpu_data);