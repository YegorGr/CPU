#include "stack.h"
#include "vm.h"
#include "commands.h"

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>  
#include <stdint.h>

int RunVm (cpu* cpu_data)
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
            return -1;
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

        case SQRT:
            CmdSqrt(cpu_data, &err);
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
        
        case JMP:
            CmdJmp(cpu_data);
            break;
               
        case JA: case JEA: case JB: case JEB: case JE: case JNE:
        {
            uint16_t pc_jmp = 0;
            if (ReadAddress(cpu_data, &pc_jmp) != 0)
                return -1;

            double b = StackPop(cpu_data->cpu_stack, &err);
            if (err != IS_OK) 
            {
                StackDump(cpu_data->cpu_stack, err); 
                return -1; 
            };

            double a = StackPop(cpu_data->cpu_stack, &err);
            if (err != IS_OK)
            {
                StackDump(cpu_data->cpu_stack, err);
                return -1;
            }
            
            if (JumpCondition(command, a, b))
                cpu_data->pc = pc_jmp;
            
            break;
        }

        case IN:
        {
            double value = NAN;
            if (scanf("%lf", &value) != 1)
            {
                fprintf(stderr, "IN: bad input\n");
                return -1;
            }

            err = StackPush(cpu_data->cpu_stack, value);
            if (err != IS_OK) 
            {
                StackDump(cpu_data->cpu_stack, err); 
                return -1; 
            }
            break;
        }

        case CALL:
            CmdCall(cpu_data, &err);
            break;

        case RET:


        default:
        {
            fprintf(stderr, "Incorrect command!");
            StackDump(cpu_data->cpu_stack, err);
            abort();
        }
        }

        if (is_run == false || err != IS_OK)
            return -1;

    }

    return 0;
}

void CmdHlt (bool* is_run)
{
    *is_run = false;
}

int CmdPush (cpu* cpu_data, ErrorsCode* err)
{
    double value = NAN;

    if (cpu_data->pc + sizeof(double) > cpu_data->capacity)
    {
        fprintf(stderr, "Uncorrect size of buffer! Error to push");
        return -1;
    }

    memcpy(&value, &cpu_data->buffer[cpu_data->pc], sizeof(double));

    *err = StackPush(cpu_data->cpu_stack, value);

    cpu_data->pc += sizeof(double);

    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    return 0;
}

int CmdAdd (cpu* cpu_data, ErrorsCode* err)
{
    stackelem_t value_2 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    stackelem_t value_1 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    stackelem_t value_3 = value_1 + value_2;

    *err = StackPush(cpu_data->cpu_stack, value_3);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    return 0;
}

int CmdSub (cpu* cpu_data, ErrorsCode* err)
{
    stackelem_t value_2 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    stackelem_t value_1 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    stackelem_t value_3 = value_1 - value_2;

    *err = StackPush(cpu_data->cpu_stack, value_3);

    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    return 0;
}

int CmdDiv (cpu* cpu_data, ErrorsCode* err)
{
    stackelem_t value_2 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    stackelem_t value_1 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    stackelem_t value_3 = value_1 / value_2;

    *err = StackPush(cpu_data->cpu_stack, value_3);

    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    return 0;
}

int CmdMul (cpu* cpu_data, ErrorsCode* err)
{
    stackelem_t value_2 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    stackelem_t value_1 = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    stackelem_t value_3 = value_1 * value_2;

    *err = StackPush(cpu_data->cpu_stack, value_3);

    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    return 0;
}

int CmdOut (cpu* cpu_data, ErrorsCode* err)
{
    double value = StackPop(cpu_data->cpu_stack, err);

    if (*err != IS_OK)
    {
        fprintf(stderr, "Error to out value: %s\n", GetErrorStr(*err));
        return -1;
    }

    printf("%lg\n", value);

    return 0;
}

int CmdPushReg (cpu* cpu_data, ErrorsCode* err)
{
    int reg = ReadCorrectReg(cpu_data);

    *err = StackPush(cpu_data->cpu_stack, cpu_data->regs[reg]);

    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    return 0;
}

int CmdPopReg (cpu* cpu_data, ErrorsCode* err)
{
    int reg = ReadCorrectReg(cpu_data);

    stackelem_t value = StackPop(cpu_data->cpu_stack, err);

    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    cpu_data->regs[reg] = value;

    return 0;
}

int CmdCall (cpu* cpu_data, ErrorsCode* err)
{
    uint16_t pc_jmp = 0;

    *err = StackPush(cpu_data->cpu_return, *((double*)(cpu_data->buffer + cpu_data->pc + sizeof(uint16_t))));

    if (*err != IS_OK)
    {
        fprintf(stderr, "Error to Push! #[&d]", *err);
        return -1;
    }

    ReadAddress(cpu_data, &pc_jmp);
    cpu_data->pc = pc_jmp;

    if (ReadAddress != 0)
    {
        fprintf(stderr, "Error to read address");
        return -1;
    }

    return 0;
}

int CmdRet (cpu* cpu_data, ErrorsCode* err)
{
    uint16_t address = 0;
    address = (uint16_t) StackPop(cpu_data->cpu_return, err);

    if (*err != IS_OK)
    {
        fprintf(stderr, "Error to Pop address #[%d]", *err);
        return -1;
    }

    cpu_data->pc = (size_t) address;

    return 0;
}

int CmdJmp (cpu* cpu_data)
{
    uint16_t pc_jmp = 0; 

    if (ReadAddress(cpu_data, &pc_jmp) != 0)
    {
        fprintf(stderr, "Error to read address");
        return -1;
    }

    cpu_data->pc = pc_jmp;
}

int ReadCorrectReg (cpu* cpu_data)
{
    if (cpu_data->pc + 1 > cpu_data->capacity)
    {
        fprintf(stderr, "Array out!");
        return -1;
    }

    int reg = (char) cpu_data->buffer[cpu_data->pc];
    cpu_data->pc++;

    if (reg >= REGS_COUNT)
    {
        fprintf(stderr, "Unccorect register: [%d] -> there are only [%d]\n", reg, REGS_COUNT);
        return -1;
    }
    
    return reg;
}

int CheckHeader (FileInfo* data)
{
    if (data->real_size < SIGNATURESIZE)
    {
        fprintf(stderr, "File is too short: %d bytes, header needs %d\n", data->size_array, SIGNATURESIZE);
        return -1; 
    }

    if (memcmp(data->buffer, SIGNATURE, SIGNATURESIZE) != 0)
    {
        fprintf(stderr, "Uncorrect signature");
        return -1;
    }
}

int ReadAddress (cpu* cpu_data, uint16_t* pc_jmp)
{
    assert(cpu_data != NULL);
    assert(pc_jmp   != NULL);

    if (cpu_data->pc > cpu_data->capacity || cpu_data->capacity - cpu_data->pc < sizeof(uint16_t))    
        return -1;

    uint16_t address = 0;
    memcpy(&address, &cpu_data->buffer[cpu_data->pc], sizeof(uint16_t));
    cpu_data->pc += sizeof(uint16_t);

    if (address < SIGNATURESIZE || (size_t) (address - SIGNATURESIZE) >= cpu_data->capacity)
    {
        fprintf(stderr, "Jump: bad address [%c] code capacity [%zu])\n", address, cpu_data->capacity);
        return -1;
    }

    *pc_jmp = (size_t) (address - SIGNATURESIZE);

    return 0;
}

int JumpCondition (Commands cmd, double a, double b)
{
    double diff = a - b;

    switch (cmd)
    {
        case JA:  return diff       >   EPSILON;
        case JB:  return diff       <  -EPSILON;  
        case JE:  return fabs(diff) <=  EPSILON;
        case JNE: return fabs(diff) >   EPSILON;
        case JEA: return diff       >= -EPSILON;  
        case JEB: return diff       <=  EPSILON;

        default:  return 0;
    }
}

int CmdSqrt (cpu* cpu_data, ErrorsCode* err)
{
    stackelem_t value = StackPop(cpu_data->cpu_stack, err);
    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    value = sqrt(value);

    *err = StackPush(cpu_data->cpu_stack, value);

    if (*err != IS_OK)
    {
        StackDump(cpu_data->cpu_stack, *err);
        return -1;
    }

    return 0;   
}