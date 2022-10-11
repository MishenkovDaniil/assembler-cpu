#include <stdio.h>
#include <assert.h>

#define STACK_DEBUG

#include "cpu.h"
#include "..\..\Stack\stack\stack.h"
#include "..\calc.h"

int calc (Calc *calc, const int number)
{
    assert (calc && number);

    int val_1 = 0;
    int val_2 = 0;

    Stack stk = {};

    int start_capacity = 2;

    stack_init (&stk, start_capacity);


    while (calc->ip < number)
    {
        int cmd = calc->op_code[calc->ip];
        int arg = 0;

        switch (cmd & CMD_MASK)
        {
            case CMD_PUSH:
            {
                if (cmd & ARG_IMMED)
                {
                    calc->ip++;

                    arg += calc->op_code[calc->ip];

                    calc->ip++;
                }
                if (cmd & ARG_REGISTR)
                {
                    arg += calc->regs[calc->op_code[calc->ip]];

                    calc->ip++;
                }

                stack_push (&stk, arg);

                break;
            }
            case CMD_SUB:
            {
                val_1  = stack_pop (&stk);

                stack_push (&stk, stack_pop (&stk) - val_1);

                calc->ip++;
                break;
            }
            case CMD_ADD:
            {
                stack_push (&stk, stack_pop (&stk) + stack_pop (&stk));

                calc->ip++;
                break;
            }
            case CMD_MULT:
            {
                stack_push (&stk, stack_pop (&stk) * stack_pop (&stk));

                calc->ip++;
                break;
            }
            case CMD_DIV:
            {
                val_1 = stack_pop (&stk);

                stack_push (&stk, stack_pop (&stk) / val_1);

                calc->ip++;
                break;
            }
            case CMD_OUT:
            {
                val_1 = stack_pop (&stk);

                printf ("\nresult is [%d]\n", val_1);

                calc->ip++;
                break;
            }
            case CMD_HLT:
            {
                stack_dtor (&stk);

                calc->ip++;
                return 0;
            }
            case CMD_DUP:
            {
                val_1 = stack_pop (&stk);

                stack_push (&stk, val_1);
                stack_push (&stk, val_1);

                calc->ip++;
                break;
            }
            case CMD_JMP:
            {
                calc->ip = calc->op_code[calc->ip + 1];

                break;
            }
            case CMD_JB:
            {
                val_1 = stack_pop (&stk);
                val_2 = stack_pop (&stk);

                stack_push (&stk, val_2);

                if (val_2 < val_1)
                {
                    calc->ip = calc->op_code[calc->ip + 1];
                    printf ("op_code = %d\n\n", calc->ip);
                }
                else
                {
                    calc->ip += 2;
                }

                break;
            }
            case CMD_JBE:
            {
                val_1 = stack_pop (&stk);
                val_2 = stack_pop (&stk);

                stack_push (&stk, val_2);

                if (val_2 <= val_1)
                {
                    calc->ip = calc->op_code[calc->ip + 1];
                }
                else
                {
                    calc->ip += 2;
                }

                break;
            }
            case CMD_JA:
            {
                val_1 = stack_pop (&stk);
                val_2 = stack_pop (&stk);

                if (val_2 > val_1)
                {
                    stack_push (&stk, val_2);

                    calc->ip = calc->op_code[calc->ip + 1];
                }
                else
                {
                    calc->ip += 2;
                }

                break;
            }
            case CMD_JAE:
            {
                val_1 = stack_pop (&stk);
                val_2 = stack_pop (&stk);

                stack_push (&stk, val_2);

                if (val_2 >= val_1)
                {
                    calc->ip = calc->op_code[calc->ip + 1];
                }
                else
                {
                    calc->ip += 2;
                }

                break;
            }
            case CMD_JE:
            {
                val_1 = stack_pop (&stk);
                val_2 = stack_pop (&stk);

                stack_push (&stk, val_2);

                if (val_2 == val_1)
                {
                    calc->ip = calc->op_code[calc->ip + 1];
                }
                else
                {
                    calc->ip += 2;
                }

                break;
            }
            case CMD_JNE:
            {
                val_1 = stack_pop (&stk);
                val_2 = stack_pop (&stk);

                stack_push (&stk, val_2);

                if (val_2 != val_1)
                {
                    calc->ip = calc->op_code[calc->ip + 1];
                }
                else
                {
                    calc->ip += 2;
                }

                break;
            }
            default:
            {
                fprintf (stderr, "ERROR: incorrect input info [%d][%d]\n", calc->op_code[calc->ip], calc->ip);
                return 0;
            }
        }
    }
}
