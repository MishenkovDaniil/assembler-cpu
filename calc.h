#ifndef CALC_H
#define CALC_H

#define DEF_CMD(name, num,...) CMD_##name = num,

enum op_codes
{
    #include "cmd.h"
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

