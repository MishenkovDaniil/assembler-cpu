#include <stdio.h>
#include <assert.h>

#define STACK_DEBUG

#define STACK stk
#define FUNC func

#define POP stack_pop (&STACK)
#define PUSH(val) stack_push (&STACK, (val))

#define CPU cpu
#define IP cpu->ip
#define CODE cpu->op_code

#include "cpu.h"
#include "..\..\Stack\stack\stack.h"
#include "..\calc.h"

void process_call_arg (Stack *func, Calc *cpu);

#define DEF_CMD(name, num, arg, arg_name, code) \
        case num:\
        {\
            code\
            break;\
        }
#define DEF_JMP(name, num, arg, arg_name, sign) \
        case num:\
        {\
            val_1 = POP;\
            val_2 = POP;\
            \
            PUSH (val_2);\
            \
            if (val_2 sign val_1)\
            {\
               IP = CODE[IP];\
            }\
            else\
            {\
                (IP)++;\
            }\
            \
            break;\
        }

int calc (Calc *cpu, const int number)
{
    assert (cpu && number);

    int val_1 = 0;
    int val_2 = 0;

    Stack stk = {};
    Stack func = {};

    int start_capacity = 2;

    stack_init (&stk, start_capacity);
    stack_init (&func, start_capacity);

    while (cpu->ip < number)
    {
        int cmd = CODE[IP++];
        int arg = 0;

        switch (cmd & CMD_MASK)
        {
            #include "../cmd.h"
            default:
            {
                fprintf (stderr, "ERROR: incorrect input info [%d][%d]\n", CODE[IP], IP);
                return 0;
            }
        }
    }
}

#undef DEF_CMD
#undef DEF_JMP

int process_push_arg (int cmd, Calc *cpu)
{
    int arg = 0;

    if (cmd & ARG_IMMED)
    {
        arg += cpu->op_code[cpu->ip++];
    }
    if (cmd & ARG_REGISTR)
    {
        arg += cpu->regs[cpu->op_code[cpu->ip++]];
    }
    if (cmd & ARG_MEM)
    {
        arg = cpu->RAM[arg];
    }

    return arg;
}

void process_pop_arg (int cmd, Calc *cpu, int arg)
{
    if (cmd & ARG_MEM)
    {
        if (cmd & ARG_IMMED && cmd & ARG_REGISTR)
        {
            cpu->RAM[cpu->op_code[cpu->ip] + cpu->regs[cpu->op_code[cpu->ip + 1]]] = arg;
            cpu->ip += 2;
        }
        else if (cmd & ARG_IMMED)
        {
            cpu->RAM[cpu->op_code[cpu->ip++]] = arg;
        }
        else if (cmd & ARG_REGISTR)
        {
            cpu->RAM[cpu->regs[cpu->op_code[cpu->ip++]]] = arg;
        }
    }
    else if (cmd & ARG_REGISTR)
    {
        cpu->regs[cpu->op_code[cpu->ip++]] = arg;
    }
}

void process_call_arg (Stack *func, Calc *cpu)
{
    int a = cpu->ip;
    stack_push (func, a + 1);

    cpu->ip = cpu->op_code[cpu->ip];
}

