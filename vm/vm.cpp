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
        fprintf(stderr, "Uncorrect size of buffer! Error ti push");
        abort();
    }

    memcpy(&value, &cpu_data->buffer[cpu_data->pc], sizeof(double));

    *err = StackPush(cpu_data->cpu_stack, value);

    cpu_data->pc += sizeof(double);

    if (*err != IS_OK)
    {
        fprintf(stderr, "Error of push element to stack!");
        abort();
    }
}

void CmdAdd (cpu* cpu_data, ErrorsCode* err)
{
    stackelem_t value_2 = StackPop(cpu_data->cpu_stack, err);
    stackelem_t value_1 = StackPop(cpu_data->cpu_stack, err);

    stackelem_t value_3 = value_1 + value_2;

    *err = StackPush(cpu_data->cpu_stack, value_3);

    if (*err != IS_OK)
    {
        fprintf(stderr, "Error to fold the values!");
        abort();
    }
}

void CmdSub (cpu* cpu_data, ErrorsCode* err)
{
    stackelem_t value_2 = StackPop(cpu_data->cpu_stack, err);
    stackelem_t value_1 = StackPop(cpu_data->cpu_stack, err);

    stackelem_t value_3 = value_1 - value_2;

    *err = StackPush(cpu_data->cpu_stack, value_3);

    if (*err != IS_OK)
    {
        fprintf(stderr, "Error to subtract the values!");
        abort();
    }
}

void CmdDiv (cpu* cpu_data, ErrorsCode* err)
{
    stackelem_t value_2 = StackPop(cpu_data->cpu_stack, err);
    stackelem_t value_1 = StackPop(cpu_data->cpu_stack, err);

    stackelem_t value_3 = value_1 / value_2;

    *err = StackPush(cpu_data->cpu_stack, value_3);

    if (*err != IS_OK)
    {
        fprintf(stderr, "Error to divide the values!");
        abort();
    }
}

void CmdMul (cpu* cpu_data, ErrorsCode* err)
{
    stackelem_t value_2 = StackPop(cpu_data->cpu_stack, err);
    stackelem_t value_1 = StackPop(cpu_data->cpu_stack, err);

    stackelem_t value_3 = value_1 * value_2;

    *err = StackPush(cpu_data->cpu_stack, value_3);

    if (*err != IS_OK)
    {
        fprintf(stderr, "Error to multiply values!");
        abort();
    }
}

void CmdOut (cpu* cpu_data, ErrorsCode* err)
{
    double value = StackTop(cpu_data->cpu_stack, err);

    if (*err != IS_OK)
    {
        fprintf(stderr, "Error to out value: %s\n", GetErrorStr(*err));
        abort();
    }

    printf("%lg\n", value);
}


