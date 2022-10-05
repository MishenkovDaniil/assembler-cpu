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
    int val   = 0;

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
                val  = stack_pop (&stk, p);

                stack_push (&stk, stack_pop (&stk, p) - val, p);

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
                val = stack_pop (&stk, p);

                stack_push (&stk, stack_pop (&stk, p) / val, p);

                index++;
                break;
            }
            case CMD_OUT:
            {
                val = stack_pop (&stk, p);

                stack_push (&stk, val, p);

                printf ("[%d]", val);

                index++;
                break;
            }
            case CMD_HLT:
            {
                stack_dtor (&stk);

                index++;
                return 0;
            }
            default:
            {
                fprintf (stderr, "ERROR: incorrect input info\n");
                return 0;
            }
        }
    }
}
