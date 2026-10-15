#include "commands.h"
#include <stdio.h>
#include <string.h>

const CommandInfo COMMANDS_TABLE[] = {
    {"HLT",   HLT,   ARG_NONE  },
    {"PUSH",  PUSH,  ARG_NUMBER},
    {"ADD",   ADD,   ARG_NONE  },
    {"SUB",   SUB,   ARG_NONE  },
    {"DIV",   DIV,   ARG_NONE  },
    {"MUL",   MUL,   ARG_NONE  },
    {"OUT",   OUT,   ARG_NONE  },
    {"PUSHR", PUSHR, ARG_REG   },
    {"POPR",  POPR,  ARG_REG   },
};

const char* REGISTER_TABLE[REGS_COUNT] = {"AX", "BX", "CX", "DX"}; // connect with enum, else crush !

#define COMMANDS_COUNT (sizeof(COMMANDS_TABLE) / sizeof(COMMANDS_TABLE[0]))

const CommandInfo* CommandToNum (char* name)
{
    for (size_t i = 0; i < COMMANDS_COUNT; i++)
    {
        if (strcasecmp(COMMANDS_TABLE[i].name, name) == 0)
            return &COMMANDS_TABLE[i];
    }

    return NULL;
}

const CommandInfo* NumToCommand (Commands number)
{
    for (size_t i = 0; i < COMMANDS_COUNT; i++)
    {
        if (COMMANDS_TABLE[i].code == number)
            return &COMMANDS_TABLE[i];
    }

    return NULL;
}

int RegisterToNum (char* name)
{
    for (int i = 0; i < REGS_COUNT; i++)
    {
        if (strcasecmp(REGISTER_TABLE[i], name) == 0)
            return i;
    }

    return -1;
}

const char* NumToRegister (int number)
{
    if (number < 0 || number >= REGS_COUNT)
        return NULL;
    
    return REGISTER_TABLE[number];
}
