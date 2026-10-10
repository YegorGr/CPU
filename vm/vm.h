#pragma once

#include "stack.h"
#include <stddef.h>

struct cpu_data {
    stackelem_t* buffer;
    size_t       capacity;
    size_t       pc;
    stack_t*     cpu_stack;
};

void RunCpu(cpu_data* cpu_data);