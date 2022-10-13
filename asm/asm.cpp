#include <stdio.h>
#include <string.h>

#include "..\calc.h"
#include "asm.h"
#include "../../Onegin/str.h"

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


        if (stricmp (cmd, "push") == 0)
        {
            op_code[ip++] = CMD_PUSH;
            assemble_push_arg (&text, op_code, &ip);
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
        else if (stricmp (cmd, "jmp") == 0)
        {
            op_code[ip++] = CMD_JMP;
            assemble_jmp (&text, op_code, &ip, label, &label_index);
        }
        else if (stricmp (cmd, "jb") == 0)
        {
            op_code[ip++] = CMD_JB;
            assemble_jmp (&text, op_code, &ip, label, &label_index);
        }
        else if (stricmp (cmd, "jbe") == 0)
        {
            op_code[ip++] = CMD_JBE;
            assemble_jmp (&text, op_code, &ip, label, &label_index);
        }
        else if (stricmp (cmd, "ja") == 0)
        {
            op_code[ip++] = CMD_JA;
            assemble_jmp (&text, op_code, &ip, label, &label_index);
        }
        else if (stricmp (cmd, "jae") == 0)
        {
            op_code[ip++] = CMD_JAE;
            assemble_jmp (&text, op_code, &ip, label, &label_index);
        }
        else if (stricmp (cmd, "je") == 0)
        {
            op_code[ip++] = CMD_JE;
            assemble_jmp (&text, op_code, &ip, label, &label_index);
        }
        else if (stricmp (cmd, "jne") == 0)
        {
            op_code[ip++] = CMD_JNE;
            assemble_jmp (&text, op_code, &ip, label, &label_index);
        }
        else if (stricmp (cmd, "jt") == 0)
        {
            op_code[ip++] = CMD_JT;
            assemble_jmp (&text, op_code, &ip, label, &label_index);
        }
        else if (strchr (cmd, ':'))
        {
            assemble_label (cmd, &ip, label, &label_index);
        }
        else
        {
            error: printf ("ERROR: incorrect input info\ncommand is [%s]", cmd);

            return 0;
        }
    }

    return ip;
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

void assemble_push_arg (char **text, int *op_code, int *ip)
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

void assemble_jmp (char **text, int *op_code, int *ip, Label *label, int *label_index)
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

void assemble_label (char *cmd, int *ip, Label *label, int *label_index)
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
