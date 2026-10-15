#include "stack.h"
#include "vm.h"
#include "commands.h"

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>   

void RunVm (cpu* cpu_data)
{
    bool is_run = true;
    ErrorsCode err = IS_OK;

    while (is_run == true)
    {
        Commands command = HLT;

        if (cpu_data->pc < cpu_data->capacity)
        {
            command = (Commands) cpu_data->buffer[cpu_data->pc];
            cpu_data->pc++;
        }
        else
        {
            fprintf(stderr, "Array out!");
            abort();
        }

        switch (command)
        {
        case HLT:
            CmdHlt(&is_run);
            break;
        
        case PUSH:
            CmdPush(cpu_data, &err);
            break;
        
        case ADD:
            CmdAdd(cpu_data, &err);
            break;

        case SUB:
            CmdSub(cpu_data, &err);
            break;  
        
        case DIV:
            CmdDiv(cpu_data, &err);
            break;   

        case MUL:
            CmdMul(cpu_data, &err);
            break;

        case OUT:
            CmdOut(cpu_data, &err);
            break;

        case PUSHR:
            CmdPushReg(cpu_data, &err);
            break;

        case POPR:
            CmdPopReg(cpu_data, &err);
            break;

        default:
            fprintf(stderr, "Incorrect command!");
            StackDump(cpu_data->cpu_stack, err);
            abort();
        }
    }
}

void CmdHlt (bool* is_run)
{
    *is_run = false;
}

void CmdPush (cpu* cpu_data, ErrorsCode* err)
{
    double value = NAN;

    if (cpu_data->pc + sizeof(double) > cpu_data->capacity)
    {
        fprintf(stderr, "Uncorrect size of buffer! Error to push");
        abort();
    }

    memcpy(&value, &cpu_data->buffer[cpu_data->pc], sizeof(double));

    *err = StackPush(cpu_data->cpu_stack, value);

    cpu_data->pc += sizeof(double);

    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        abort();
    }
}

void CmdAdd (cpu* cpu_data, ErrorsCode* err)
{
    stackelem_t value_2 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        abort();
    }

    stackelem_t value_1 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        abort();
    }

    stackelem_t value_3 = value_1 + value_2;

    *err = StackPush(cpu_data->cpu_stack, value_3);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        abort();
    }
}

void CmdSub (cpu* cpu_data, ErrorsCode* err)
{
    stackelem_t value_2 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        abort();
    }

    stackelem_t value_1 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        abort();
    }

    stackelem_t value_3 = value_1 - value_2;

    *err = StackPush(cpu_data->cpu_stack, value_3);

    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        abort();
    }
}

void CmdDiv (cpu* cpu_data, ErrorsCode* err)
{
    stackelem_t value_2 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        abort();
    }

    stackelem_t value_1 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        abort();
    }

    stackelem_t value_3 = value_1 / value_2;

    *err = StackPush(cpu_data->cpu_stack, value_3);

    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        abort();
    }
}

void CmdMul (cpu* cpu_data, ErrorsCode* err)
{
    stackelem_t value_2 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        abort();
    }

    stackelem_t value_1 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        abort();
    }

    stackelem_t value_3 = value_1 * value_2;

    *err = StackPush(cpu_data->cpu_stack, value_3);

    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        abort();
    }
}

void CmdOut (cpu* cpu_data, ErrorsCode* err)
{
    double value = StackPop(cpu_data->cpu_stack, err);

    if (*err != IS_OK)
    {
        fprintf(stderr, "Error to out value: %s\n", GetErrorStr(*err));
        abort();
    }

    printf("%lg\n", value);
}

void CmdPushReg (cpu* cpu_data, ErrorsCode* err)
{
    int reg = ReadCorrectReg(cpu_data);

    *err = StackPush(cpu_data->cpu_stack, cpu_data->regs[reg]);

    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        abort();
    }
}

void CmdPopReg (cpu* cpu_data, ErrorsCode* err)
{
    int reg = ReadCorrectReg(cpu_data);

    stackelem_t value = StackPop(cpu_data->cpu_stack, err);

    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        abort();
    }

    cpu_data->regs[reg] = value;

}

int ReadCorrectReg (cpu* cpu_data)
{
    if (cpu_data->pc + 1 > cpu_data->capacity)
    {
        fprintf(stderr, "Array out!");
        abort();
    }

    int reg = (char) cpu_data->buffer[cpu_data->pc];
    cpu_data->buffer++;

    if (reg >= REGS_COUNT)
    {
        fprintf(stderr, "Unccorect register: [%d] -> there are only [%d]\n", reg, REGS_COUNT);
        abort();
    }
    
    return reg;
}