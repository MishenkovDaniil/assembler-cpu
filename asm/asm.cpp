#include <stdio.h>
#include <string.h>

#include "..\calc.h"
#include "asm.h"
#include "../../Onegin/str.h"

#define DEF_CMD(name, num, arg, arg_name) if (stricmp (cmd, #name) == 0)\
                                          {\
                                              op_code[ip++] = num;\
                                              if (arg)\
                                              {\
                                                  assemble_##arg_name##_arg (&text, op_code, &ip, label, &label_index);\
                                              }\
                                          }\
                                          else
int init_code (char *text, int *op_code, Label *label)
{
    int number = 0;
    int ip = 0;
    int label_index = 0;

    while (*(text + 1) != '\0')
    {
        int temp = 0;
        char cmd[100] = {};

        sscanf (text, "%s%n", cmd, &temp);
        text += temp + 1;
        temp = 0;

        if (isspace_s (cmd))
        {
            printf ("1");
            continue;
        }

        #include "../cmd.h"
        /*else*/ if (strchr (cmd, ':'))
        {
            assemble_label_arg (cmd, &ip, label, &label_index);
        }
        else
        {
            error: printf ("ERROR: incorrect input info\ncommand is [%s]", cmd);

            return 0;
        }
    }

    return ip;
}

#undef DEF_CMD

int isspace_s (char *arr)
{
    while (*arr != '\0')
    {
        if (!(isspace (*arr)))
        {
            return 0;
        }
        else
        {
            arr++;
        }
    }
    return 1;
}

int is_label_name (Label *label, const char *jmp_name)
{
    for (int i = 0; i < MAXSIZE && label->name[i] != nullptr; i++)
    {
        if (strcmp (label->name[i], jmp_name) == 0)
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

void assemble_push_arg (char **text, int *op_code, int *ip, Label *label, int *label_index)
{
    int start_ip = --(*ip);
    int temp = 0;

    if (isdigit (**text))
    {
        printf ("*text = [%c]\n", **text);
        int val = 0;

        sscanf (*text, "%d%n", &val, &temp);

        op_code[start_ip] |= ARG_IMMED;
        (*ip)++;
        op_code[*ip] = val;

        *text += temp;

        temp = 0;
    }
    if (isalpha (*((*text) + 1)))
    {
        char reg[5] = {};

        if (**(text) == '+')
        {
            (*text)++;
        }

        sscanf (*text, "%s%n\n", reg, &temp);

        printf ("%s\n", reg);

        op_code[start_ip] |= ARG_REGISTR;

        (*ip)++;

        if (stricmp (reg, "RAX") == 0)
        {
            op_code[*ip] = RAX_NUM;
        }
        else if (stricmp (reg, "RBX") == 0)
        {
            op_code[*ip] = RBX_NUM;
        }
        else if (stricmp (reg, "RCX") == 0)
        {
            op_code[*ip] = RCX_NUM;
        }
        else if (stricmp (reg, "RDX") == 0)
        {
            op_code[*ip] = RDX_NUM;
        }
        else
        {
            printf ("syntax error");
        }
    }

    (*ip)++;

    *text += temp;

    temp = 0;
}

void assemble_jmp_arg (char **text, int *op_code, int *ip, Label *label, int *label_index)
{
    char jmp_name[100] = {};
    int temp_label_index = 0;
    int temp = 0;

    sscanf (*text, "%s%n", jmp_name, &temp);

    (*text) += temp;

    temp_label_index = is_label_name (label, jmp_name);

    if (temp_label_index > 0) //&& label->value[--temp_label_index] != -1)
    {
        op_code[(*ip)++] = label->value[--temp_label_index];
    }
    else if (!(temp_label_index))
    {
        my_strcpy (label->name[*label_index], jmp_name);
        label->value[(*label_index)++] = -1;   //

        op_code[(*ip)++] = -1;  //
    }
}

void assemble_label_arg (char *cmd, int *ip, Label *label, int *label_index)
{
    int temp_label_index = 0;
    char *pname = strchr (cmd, ':');
    *pname = '\0';

    temp_label_index = is_label_name (label, cmd);

    if (!(temp_label_index))
    {
        my_strcpy (label->name[(*label_index)], cmd);

        label->value[(*label_index)++] = *ip;
    }
    else
    {
        label->value[temp_label_index] = *ip;
    }

    *pname = ':';
}
