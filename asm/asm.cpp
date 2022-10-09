#include <stdio.h>
#include <string.h>

#include "..\calc.h"
#include "asm.h"
#include "../../Onegin/str.h"

int init_code (char *text, int *op_code, Label *label)
{
    int number = 0;
    int index = 0;

    while (*(text + number + 1) != '\0')
    {
        int temp = 0;
        char cmd[100] = {};
        int label_index = 0;
        int temp_label_index = 0;

        sscanf (text + number, "%s%n", cmd, &temp);

        number += temp;
        //number--;
        temp = 0;

        if (stricmp (cmd, "push") == 0)
        {
            op_code[index++] = CMD_PUSH;

            int val = 0;

            sscanf (text + number, "%d %n", &val, &temp);

            op_code[index++] = val;

            number += temp;
            //number--;

            temp = 0;
        }
        else if (stricmp (cmd, "sub") == 0)
        {
            op_code[index++] = CMD_SUB;
        }
        else if (stricmp (cmd, "add") == 0)
        {
            op_code[index++] = CMD_ADD;
        }
        else if (stricmp (cmd, "mult") == 0)
        {
            op_code[index++] = CMD_MULT;
        }
        else if (stricmp (cmd, "div") == 0)
        {
            op_code[index++] = CMD_DIV;
        }
        else if (stricmp (cmd, "out") == 0)
        {
            op_code[index++] = CMD_OUT;
        }
        else if (stricmp (cmd, "hlt") == 0)
        {
            op_code[index++] = CMD_HLT;
            break;
        }
        else if (stricmp (cmd, "jmp") == 0)
        {
            op_code[index++] = CMD_JMP;

            char jmp_name[100] = {};
            sscanf (text + number, "%s%n", jmp_name, &temp);

            number += temp;
            temp = 0;

            temp_label_index = is_label_name (label, jmp_name);
            fprintf (stderr, "label 0 = [%s]\n", label->name[0]);
            printf ("jmp_name = [%s]\t temp_label_index  = %d\n\n\n", jmp_name, temp_label_index);

            if (temp_label_index > 0 && label->value[--temp_label_index] != -1)
            {
                op_code[index++] = label->value[temp_label_index];
            }
            else if (!(temp_label_index))
            {
                char temp[100] = {};
                my_strcpy (temp, jmp_name);

                label->name[label_index] = temp;

                op_code[index++] = -1;  //
            }
        }
        else if (strchr (cmd, ':'))
        {
            char *pname = strchr (cmd, ':');
            *pname = '\0';

            printf ("cmd_label = [%s]\n", cmd);

            temp_label_index = is_label_name (label, cmd);

            printf ("temp_label = [%d]\n", temp_label_index);

            if (!(temp_label_index))
            {
                char temp[100] = {};
                my_strcpy (temp, cmd);

                label->name[label_index] = temp;

                printf ("label_name = [%s]\tlabel_index = [%d]\n", label->name[label_index], label_index);

                label->value[label_index++] = index;

                printf ("value_label = [%d]\n", label->value[label_index - 1]);
                printf ("label_index = [%d]\n", label_index);
            }
            else if (label->value[label_index++] == -1)
            {
                label->value[label_index++] = index + 1;
            }
            else
                ;
            *pname = ':';
            printf ("bubububuub[%s]\n", label->name[0]);
        }
        else
        {
            printf ("ERROR: incorrect input info");

            return index;
        }
    }

    return index;
}

int is_label_name (Label *label, const char *jmp_name)
{
    for (int i = 0; i < MAXSIZE && label->name[i] != nullptr; i++)
    {
        if (!(strcmp (label->name[i], jmp_name)))
        {
            return i + 1;
        }
        else
            ;
    }

    return 0;
}

void print_op_code (FILE *out_file, int *op_code, int number, const char *const file_id, const int version)
{
    struct Head head = {};

    strcpy (head.file_id, file_id);
    head.file_version = version;
    head.number = number;

    fwrite (&head, sizeof (struct Head), 1, out_file);
    fwrite (op_code, sizeof (int), number, out_file);
}
