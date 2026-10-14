#pragma once

enum Commands {
    HLT  = 0,
    PUSH = 1,
    ADD  = 2,
    SUB  = 3,
    DIV  = 4,
    MUL  = 5,
    OUT  = 6,
};

enum ArgType {
    ARG_NONE   = 0,
    ARG_NUMBER = 1,
    ARG_REG    = 2,
    ARG_MARK   = 3,
};

struct CommandInfo{
    const char* name;
    Commands    number;
    ArgType     arg;
};

const CommandInfo* CommandToNum (char* name);
const CommandInfo* NumToCommand (Commands num);
