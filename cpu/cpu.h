#ifndef CPU_H
#define CPU_H

#include "../calc.h"

int check_asm_file (Head *head, const int file_id, const int version);
int calc (Calc *calc, const int number);
int process_push_arg (int cmd, Calc *cpu);
void process_pop_arg (int cmd, Calc *cpu, int arg);

static const int CMD_MASK = 0x0F;

enum code_errors
{
    CPU_INCORRECT_ID      = 0x1 << 0,
    CPU_INCORRECT_VERSION = 0x1 << 1,
    CPU_INCORRECT_NUM     = 0x1 << 2
};

#endif /* CPU_H */
