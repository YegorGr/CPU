#pragma once

#define SIGNATURE "DDX1"
#define SIGNATURESIZE 4

enum Commands {
    HLT   = 0,
    PUSH  = 1,
    ADD   = 2,
    SUB   = 3,
    DIV   = 4,
    MUL   = 5,
    OUT   = 6,
    PUSHR = 7,
    POPR  = 8, 
    JMP   = 9,
    JA    = 10,
    JEA   = 11, 
    JB    = 12,
    JEB   = 13,
    JE    = 14,
    JNE   = 15,
    CALL  = 16,
    RET   = 17,
    IN    = 18,
    SQRT  = 19,
};

enum ArgType {
    ARG_NONE   = 0,
    ARG_NUMBER = 1,
    ARG_REG    = 2,
    ARG_MARK   = 3,
};

enum Registers {
    REG_AX,
    REG_BX,
    REG_CX,
    REG_DDX,

    REGS_COUNT,    
};

struct CommandInfo{
    const char* name;
    Commands    code;
    ArgType     arg;
};

const CommandInfo* CommandToNum  (char* name);
const CommandInfo* NumToCommand  (Commands num);
int                RegisterToNum (char* name);
const char*        NumToRegister (int number);

