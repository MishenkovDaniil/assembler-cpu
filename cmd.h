DEF_CMD (HLT,  0, 0, push, {stack_dtor (&STACK);
                            stack_dtor (&FUNC);
                            IP = number;})
DEF_CMD (PUSH, 1, 1, push, {arg = process_push_arg (cmd, cpu);
                            stack_push (&STACK, arg);})
DEF_CMD (POP,  2, 1, push,  {arg = stack_pop (&STACK);
                            process_pop_arg (cmd, cpu, arg);})
DEF_CMD (SUB,  3, 0, push, {val_1  = stack_pop (&STACK);
                            stack_push (&STACK, POP - val_1);})
DEF_CMD (ADD,  4, 0, push, {stack_push (&STACK, POP + POP);})
DEF_CMD (MULT, 5, 0, push, {stack_push (&STACK, (int)((int)POP * (int)POP));})
DEF_CMD (DIV,  6, 0, push, {val_1 = (int)POP;
                            PUSH ((int)((int)POP / val_1));})
DEF_CMD (OUT,  7, 0, push, {val_1 = POP;
                            fprintf (stderr, "\nresult is [%d]\n", val_1);})
DEF_CMD (DUP,  8, 0, push, {val_1 = POP;
                            PUSH (val_1);
                            PUSH (val_1);})
DEF_CMD (CALL, 9, 1, jmp, {process_call_arg (&FUNC, CPU);})//
DEF_CMD (RET, 10, 0, push, {int a = stack_pop (&FUNC);
                            cpu->ip = a;
                            fprintf (stderr, "ip is [%d] in return\n", cpu->ip);})//
DEF_CMD (JMP, 11, 1, jmp, {IP = CODE[IP];})
DEF_JMP (JB,  12, 1, jmp, <)
DEF_JMP (JBE, 13, 1, jmp, <=)
DEF_JMP (JA,  19, 1, jmp, >)
DEF_JMP (JAE, 16, 1, jmp, >=)
DEF_JMP (JE,  15, 1, jmp, ==)
DEF_JMP (JNE, 17, 1, jmp, !=)
DEF_JMP (JT,  18, 1, jmp, ==)
DEF_CMD (IN,  14, 0, push, {int a = 0;
                            scanf ("%d", &a);
                            PUSH (a);})
