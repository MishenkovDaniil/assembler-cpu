#include <stdio.h>
#include <string.h>

#include "..\calc.h"
#include "asm.h"
#include "../../Onegin/str.h"

int init_code (char *text, int *op_code, Label *label)
{
    int number = 0;
    int ip = 0;

    while (*(text + number + 1) != '\0')
    {
        int temp = 0;
        char cmd[100] = {};
        int label_index = 0;
        int temp_label_index = 0;

        sscanf (text + number, "%s%n", cmd, &temp);
        number += temp;
        temp = 0;

        if (stricmp (cmd, "push") == 0)
        {
            if (isalpha (*(text + number + 1)))
            {
                char reg[4] = {};

                sscanf (text + number, "%s %n", reg, &temp);
                printf ("%s", reg);

                op_code[ip++] |= CMD_PUSH | ARG_REGISTR;

                if (stricmp (reg, "RAX") == 0)
                {
                    op_code[ip++] = RAX_NUM;
                }
                else if (stricmp (reg, "RBX") == 0)
                {
                    op_code[ip++] = RBX_NUM;
                }
                else if (stricmp (reg, "RCX") == 0)
                {
                    op_code[ip++] = RCX_NUM;
                }
                else if (stricmp (reg, "RDX") == 0)
                {
                    op_code[ip++] = RDX_NUM;
                }
                else
                {
                    goto error;
                }
            }
            else
            {
                int val = 0;

                sscanf (text + number, "%d %n", &val, &temp);

                op_code[ip++] = CMD_PUSH | ARG_IMMED;
                op_code[ip++] = val;
            }

            number += temp;

            temp = 0;
        }
        else if (stricmp (cmd, "sub") == 0)
        {
            op_code[ip++] = CMD_SUB;
        }
        else if (stricmp (cmd, "add") == 0)
        {
            op_code[ip++] = CMD_ADD;
        }
        else if (stricmp (cmd, "mult") == 0)
        {
            op_code[ip++] = CMD_MULT;
        }
        else if (stricmp (cmd, "div") == 0)
        {
            op_code[ip++] = CMD_DIV;
        }
        else if (stricmp (cmd, "out") == 0)
        {
            op_code[ip++] = CMD_OUT;
        }
        else if (stricmp (cmd, "hlt") == 0)
        {
            op_code[ip++] = CMD_HLT;
            break;
        }
        else if (stricmp (cmd, "dup") == 0)
        {
            op_code[ip++] = CMD_DUP;
        }
        else if (strchr (cmd, ':'))
        {
            char *pname = strchr (cmd, ':');
            *pname = '\0';

            temp_label_index = is_label_name (label, cmd);

            if (!(temp_label_index))
            {
                char temp[100] = {};
                my_strcpy (temp, cmd);

                label->name[label_index] = temp;

                label->value[label_index++] = ip;

            }
            else if (label->value[--temp_label_index] == -1)
            {
                label->value[temp_label_index] = ip;
            }
            else
                ;
            *pname = ':';
        }
        else if (*cmd == 'j')
        {
            if (stricmp (cmd, "jmp") == 0)
            {
                op_code[ip++] = CMD_JMP;
            }
            else if (stricmp (cmd, "jb") == 0)
            {
                op_code[ip++] = CMD_JB;
            }
            else if (stricmp (cmd, "jbe") == 0)
            {
                op_code[ip++] = CMD_JBE;
            }
            else if (stricmp (cmd, "ja") == 0)
            {
                op_code[ip++] = CMD_JA;
            }
            else if (stricmp (cmd, "jae") == 0)
            {
                op_code[ip++] = CMD_JAE;
            }
            else if (stricmp (cmd, "je") == 0)
            {
                op_code[ip++] = CMD_JE;
            }
            else if (stricmp (cmd, "jne") == 0)
            {
                op_code[ip++] = CMD_JNE;
            }
            else if (stricmp (cmd, "jt") == 0)
            {
                op_code[ip++] = CMD_JT;
            }
            else
            {
                goto error;
            }

            char jmp_name[100] = {};
            sscanf (text + number, "%s%n", jmp_name, &temp);

            number += temp;
            temp = 0;

            temp_label_index = is_label_name (label, jmp_name);

            if (temp_label_index > 0 && label->value[--temp_label_index] != -1)
            {
                op_code[ip++] = label->value[temp_label_index];
            }
            else if (!(temp_label_index))
            {
                char temp[100] = {};
                my_strcpy (temp, jmp_name);

                label->name[label_index] = temp;
                label->value[label_index++] = -1;   //

                op_code[ip++] = -1;  //
            }
        }
        else
        {
            error: printf ("ERROR: incorrect input info  [%s]", cmd);

            return 0;
        }
    }

    return ip;
}

int is_label_name (Label *label, const char *jmp_name)
{
    for (int i = 0; i < MAXSIZE && label->name[i] != nullptr; i++)
    {
        if (!(strcmp (label->name[i], jmp_name)))
        {
            return i + 1;
        }
    }

    return 0;
}

void print_op_code (FILE *out_file, int *op_code, int number, const int file_id, const int version)
{
    struct Head head = {};

    head.file_id = file_id;
    head.file_version = version;
    head.number = number;

    fwrite (&head, sizeof (struct Head), 1, out_file);
    fwrite (op_code, sizeof (int), number, out_file);
}
