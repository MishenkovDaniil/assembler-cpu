#ifndef CALC_H
#define CALC_H

enum op_codes
{
    CMD_HLT  = 0,
    CMD_PUSH = 1,
    CMD_SUB  = 2,
    CMD_ADD  = 3,
    CMD_MULT = 4,
    CMD_DIV  = 5,
    CMD_OUT  = 6,
    CMD_JMP  = 7,
    CMD_JB   = 8,
    CMD_JBE  = 9,
    CMD_JA   = 10,
    CMD_JAE  = 11,
    CMD_JE   = 12,
    CMD_JNE  = 13,
    CMD_JT   = 14
};

struct Head
{
    char file_id [4] = {0};
    int file_version = 0;
    int number       = 0;
};

#endif /* CALC_H */

