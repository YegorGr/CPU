#pragma once

#include <stdint.h>
#include <stddef.h>

#include "stack.h"
#include "commands.h"
#include "fileinfo.h"

struct cpu {
    char*    buffer;
    size_t   capacity;
    size_t   pc;
    stack_t* cpu_stack;
    double   regs[REGS_COUNT];
};

int  RunVm   (cpu* cpu_data);

void CmdHlt  (bool* is_run);

int  CmdPush (cpu* cpu_data, ErrorsCode* err);
int  CmdAdd  (cpu* cpu_data, ErrorsCode* err);
int  CmdSub  (cpu* cpu_data, ErrorsCode* err);
int  CmdDiv  (cpu* cpu_data, ErrorsCode* err);
int  CmdMul  (cpu* cpu_data, ErrorsCode* err);
int  CmdOut  (cpu* cpu_data, ErrorsCode* err);
int  CmdSqrt (cpu* cpu_data, ErrorsCode* err);


int  CmdPushReg (cpu* cpu_data, ErrorsCode* err);
int  CmdPopReg  (cpu* cpu_data, ErrorsCode* err);

int  ReadCorrectReg (cpu* cpu_data);
int  CheckHeader    (FileInfo* data);

int  ReadAddress   (cpu* cpu_data, uint16_t* pc_jmp);
int  JumpCondition (Commands cmd, double a, double b);


