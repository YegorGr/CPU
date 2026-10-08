#include "Stack.h"
#include "VM.h"

#include <stdio.h> 
#include <stdlib.h>

void RunCpu (cpu_data* cpu_data)
{
    bool is_run = true;
    ErrorsCode err = IS_OK;

    while (is_run == true && cpu_data->pc < cpu_data->capacity)
    {
        Commands command = (Commands) cpu_data->data[cpu_data->pc];

        switch (command)
        {
        case HLT:
            is_run = false;
            break;
        
        case PUSH:
        {
            ++cpu_data->pc;
            err = StackPush(cpu_data->data_solved, cpu_data->data[cpu_data->pc]);
            break;
        }
        
        case ADD:
        {
            stackelem_t value_2 = StackPop(cpu_data->data_solved, &err);
            stackelem_t value_1 = StackPop(cpu_data->data_solved, &err);

            stackelem_t value_3 = value_1 + value_2;
            err = StackPush(cpu_data->data_solved, value_3);
            break;
        }

        case SUB:
        {
            stackelem_t value_2 = StackPop(cpu_data->data_solved, &err);
            stackelem_t value_1 = StackPop(cpu_data->data_solved, &err);

            stackelem_t value_3 = value_1 - value_2;
            err = StackPush(cpu_data->data_solved, value_3);
            break;
        }   
        
        case DIV:
        {
            stackelem_t value_2 = StackPop(cpu_data->data_solved, &err);
            stackelem_t value_1 = StackPop(cpu_data->data_solved, &err);

            stackelem_t value_3 = value_1 / value_2;
            err = StackPush(cpu_data->data_solved, value_3);
            break;   
        }

        case MUL:
        {
            stackelem_t value_2 = StackPop(cpu_data->data_solved, &err);
            stackelem_t value_1 = StackPop(cpu_data->data_solved, &err);

            stackelem_t value_3 = value_1 * value_2;
            err = StackPush(cpu_data->data_solved, value_3);
            break;
        }

        case OUT:
        {
            StackDump(cpu_data->data_solved, err);
            break;
        }

        default:
        {
            fprintf(stderr, "Incorrect command!");
            StackDump(cpu_data->data_solved, err);
            abort();
        }

        if (cpu_data->pc < cpu_data->capacity)
                ++cpu_data->pc;

        }
    }
}


