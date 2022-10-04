#include <stdio.h>
#include <string.h>

#include "..\calc.h"
#include "asm.h"

int init_code (char *text, int *op_code)
{
    int number = 0;
    int index = 0;

    while (*(text + number + 1) != '\0')
    {
        int temp = 0;
        char cmd[100] = {};

        sscanf (text + number, "%s %n", cmd, &temp);

        number += temp;
        number--;

        temp = 0;

        if (stricmp (cmd, "push") == 0)
        {
            op_code[index++] = CMD_PUSH;

            int val = 0;

            sscanf (text + number, "%d %n", &val, &temp);

            op_code[index++] = val;

            number += temp;
            number--;

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
        else
        {
            printf ("ERROR: incorrect input info");

            return index;
        }
    }

    return index;
}


void print_text (FILE *out_file, int *op_code, int num, const char *id, const char *version)
{
    fprintf (out_file, "%s %s %d", id, version, num);

    for (int  i = 0; i < num; i++)
    {
        fprintf (out_file, "%d ", op_code[i]);
    }
}
