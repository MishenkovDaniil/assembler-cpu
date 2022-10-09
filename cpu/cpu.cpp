#include <stdio.h>
#include <assert.h>

#define STACK_DEBUG

#include "cpu.h"
#include "..\..\Stack\stack\stack.h"
#include "..\calc.h"

int calc (int *op_code, int number)
{
    assert (op_code && number);

    int index = 0;
    int val_1   = 0;
    int val_2   = 0;

    int error = 0;

    int *p = &error;

    Stack stk = {};

    int start_capacity = 2;

    stack_init (&stk, start_capacity, p);

    while (index < number)
    {
        switch (op_code[index])
        {
            case CMD_PUSH:
            {
                index++;

                stack_push (&stk, op_code[index], p);

                index++;

                break;
            }
            case CMD_SUB:
            {
                val_1  = stack_pop (&stk, p);

                stack_push (&stk, stack_pop (&stk, p) - val_1, p);

                index++;
                break;
            }
            case CMD_ADD:
            {
                stack_push (&stk, stack_pop (&stk, p) + stack_pop (&stk, p), p);

                index++;
                break;
            }
            case CMD_MULT:
            {
                stack_push (&stk, stack_pop (&stk, p) * stack_pop (&stk, p), p);

                index++;
                break;
            }
            case CMD_DIV:
            {
                val_1 = stack_pop (&stk, p);

                stack_push (&stk, stack_pop (&stk, p) / val_1, p);

                index++;
                break;
            }
            case CMD_OUT:
            {
                val_1 = stack_pop (&stk, p);

                printf ("result is [%d]\n", val_1);

                index++;
                break;
            }
            case CMD_HLT:
            {
                stack_dtor (&stk);

                index++;
                return 0;
            }
            case CMD_DUP:
            {
                val_1 = stack_pop (&stk, p);

                stack_push (&stk, val_1, p);
                stack_push (&stk, val_1, p);

                index++;
                break;
            }
            case CMD_JMP:
            {
                index = op_code[index + 1];

                break;
            }
            case CMD_JB:
            {
                val_1 = stack_pop (&stk, p);
                val_2 = stack_pop (&stk, p);

                stack_push (&stk, val_2, p);

                if (val_2 < val_1)
                {
                    index = op_code[index + 1];
                    printf ("op_code = %d\n\n", index);
                }
                else
                {
                    index += 2;
                }

                break;
            }
            case CMD_JBE:
            {
                val_1 = stack_pop (&stk, p);
                val_2 = stack_pop (&stk, p);

                stack_push (&stk, val_2, p);

                if (val_2 <= val_1)
                {
                    index = op_code[++index];
                }
                else
                {
                    index += 2;
                }

                break;
            }
            case CMD_JA:
            {
                val_1 = stack_pop (&stk, p);
                val_2 = stack_pop (&stk, p);

                if (val_2 > val_1)
                {
                    stack_push (&stk, val_2, p);

                    index = op_code[++index];
                }
                else
                {
                    index += 2;
                }

                break;
            }
            case CMD_JAE:
            {
                val_1 = stack_pop (&stk, p);
                val_2 = stack_pop (&stk, p);

                stack_push (&stk, val_2, p);

                if (val_2 >= val_1)
                {
                    index = op_code[++index];
                }
                else
                {
                    index += 2;
                }

                break;
            }
            case CMD_JE:
            {
                val_1 = stack_pop (&stk, p);
                val_2 = stack_pop (&stk, p);

                stack_push (&stk, val_2, p);

                if (val_2 == val_1)
                {
                    index = op_code[++index];
                }
                else
                {
                    index += 2;
                }

                break;
            }
            case CMD_JNE:
            {
                val_1 = stack_pop (&stk, p);
                val_2 = stack_pop (&stk, p);

                stack_push (&stk, val_2, p);

                if (val_2 != val_1)
                {
                    index = op_code[++index];
                }
                else
                {
                    index += 2;
                }

                break;
            }
            default:
            {
                fprintf (stderr, "ERROR: incorrect input info [%d][%d]\n", op_code[index], index);
                return 0;
            }
        }
    }
}
