#ifndef CALC_H
#define CALC_H

enum op_codes
{
    CMD_PUSH = 1,
    CMD_SUB  = 2,
    CMD_ADD  = 3,
    CMD_MULT = 4,
    CMD_DIV  = 5,
    CMD_OUT  = 6,
    CMD_HLT  = 7
};

struct Head
{
    char *file_id      = nullptr;
    char *file_version = nullptr;
    char *number       = nullptr;
};

#endif /* CALC_H */

