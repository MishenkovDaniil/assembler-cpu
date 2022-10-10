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
    CMD_DUP  = 7,
    CMD_JMP  = 8,
    CMD_JB   = 9,
    CMD_JBE  = 10,
    CMD_JA   = 11,
    CMD_JAE  = 12,
    CMD_JE   = 13,
    CMD_JNE  = 14,
    CMD_JT   = 15,
};

enum types
{
    ARG_IMMED = 0x20,
    ARG_REGISTR = 0x40,
    ARG_MEM = 0x80
};

enum regs
{
    RAX_NUM = 1,
    RBX_NUM = 2,
    RCX_NUM = 3,
    RDX_NUM = 4
};

struct Calc
{
    int *op_code = nullptr;

    int ip = 0;

    int regs[5] = {};
};

struct Head
{
    int file_id      = 0;
    int file_version = 0;
    int number       = 0;
};

#endif /* CALC_H */

