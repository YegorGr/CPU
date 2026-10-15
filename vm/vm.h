#pragma once

#include "stack.h"
#include "commands.h"
#include <stddef.h>

struct cpu {
    char*    buffer;
    size_t   capacity;
    size_t   pc;
    stack_t* cpu_stack;
    double   regs[REGS_COUNT];
};

void RunVm   (cpu* cpu_data);

void CmdHlt  (bool* is_run);
void CmdPush (cpu* cpu_data, ErrorsCode* err);
void CmdAdd  (cpu* cpu_data, ErrorsCode* err);
void CmdSub  (cpu* cpu_data, ErrorsCode* err);
void CmdDiv  (cpu* cpu_data, ErrorsCode* err);
void CmdMul  (cpu* cpu_data, ErrorsCode* err);
void CmdOut  (cpu* cpu_data, ErrorsCode* err);

void CmdPushReg (cpu* cpu_data, ErrorsCode* err);
void CmdPopReg  (cpu* cpu_data, ErrorsCode* err);

int ReadCorrectReg (cpu* cpu_data);
