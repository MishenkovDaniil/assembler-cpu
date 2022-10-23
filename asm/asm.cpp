#include <stdio.h>
#include <string.h>

#include "..\calc.h"
#include "asm.h"
#include "..\..\Onegin/str.h"
#include "..\binary.h"
#include "asm_strings.h"
static const int ARR_SIZE = 100;
static const int REG_LEN  = 5;

int init_code (char *text, int *op_code, Label *label)
{
    int number = 0;
    int ip = 0;
    int label_index = 0;
    int err = 0;

    while (*(text + 1) != '\0')
    {
        int temp = 0;
        char cmd[ARR_SIZE] = {};

        sscanf (text, "%s%n", cmd, &temp);
        text += temp + 1;
        temp = 0;
        fprintf (stderr, "command is {%s}\n", cmd);

        if (is_empty_str (cmd))
        {
            continue;
        }

#define DEF_JMP(name, num, arg, arg_name,...)               \
        DEF_CMD(name, num, arg, arg_name, __VA_ARGS__)

#define DEF_CMD(name, num, arg, arg_name,...)               \
if (stricmp (cmd, #name) == 0)                              \
{                                                           \
    op_code[ip++] = num;                                    \
    if (arg)                                                \
    {                                                       \
        assemble_##arg_name##_arg                           \
        (&text, op_code, &ip, label, &label_index, &err);   \
    }                                                       \
    if (err)                                                \
    {                                                       \
        printf ("\nsyntax error\n");                        \
        break;                                              \
    }                                                       \
}                                                           \
else

#include "../cmd.h"

#undef DEF_CMD
#undef DEF_JMP

        /*else*/ if (strchr (cmd, ':'))
        {
            assemble_label_arg (cmd, &ip, label, &label_index, &err);
        }
        else
        {
            error: printf ("ERROR: incorrect input info\ncommand is [%s]\n", cmd);

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


int assemble_push_arg (char **text, int *op_code, int *ip, Label *label, int *label_index, int *err)
{
    int start_ip = *ip - 1;
    int temp = 0;
    char arg[ARR_SIZE] = {0};
    char reg[REG_LEN]  = {0};
    char sign = 1;
    int val = 0;
    char *end_cmd = nullptr;

    if (!(sscanf (*text, "%s", arg)))
    {
        fprintf (stderr, "ERROR: cannot read push argument");

        return 0;
    }

    if (*arg == '[')
    {
        int last_smbl = strlen ((const char *)arg);

        if (arg[last_smbl] == ']')
        {
            op_code[start_ip] |= ARG_MEM;
            end_cmd = *text + last_smbl;
            *(end_cmd) = '\0';

            (*text)++;
            skip_spaces (text);
        }
        else
        {
            printf ("ERROR: sintax error, '[' without ']'");
            return 0;
        }
    }
    if (**text == '-' || **text == '+')
    {
        if (**text == '-')
        {
            sign *= -1;
        }
        (*text)++;
        skip_spaces (text);
    }
    if (sscanf (*text, "%d%n", &val, &temp))
    {
        op_code[start_ip] |= ARG_IMMED;

        val *= sign;
        op_code[(*ip)++] = val;

        *text += temp;
        temp = 0;
        skip_spaces (text);

        if (**text == '+')
        {
            (*text)++;
            skip_spaces (text);

            op_code[start_ip] |= ARG_REGISTR;
        }
    }
    if ((sscanf (*text, "%s%n", reg, &temp))
        && (((op_code[start_ip] & ARG_MEM > 0) && *text < end_cmd)
        || (!(op_code[start_ip] & ARG_IMMED))))
    {
        if (!(isalpha (**text)))
        {
            fprintf (stderr, "ERROR: wrong register name");

            return 0;
        }

        op_code[start_ip] |= ARG_REGISTR;

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
            fprintf (stderr, "ERROR: sytax error, register with this name doesn't exist");
            return 0;
        }

        (*ip)++;

        *text += temp;

        if (op_code[start_ip] & ARG_MEM)
        {
            (*text)++;
        }
    }
    else if (op_code[start_ip] & ARG_REGISTR)
    {
        fprintf (stderr, "ERROR: syntax error, no register argument after '+'" );

        return 0;
    }

    if (op_code[start_ip] & ARG_MEM)
    {
        *end_cmd = ']';
    }

    return 0;
}


void assemble_jmp_arg (char **text, int *op_code, int *ip, Label *label, int *label_index, int *err)
{
    char jmp_name[ARR_SIZE] = {};
    int temp_label_index = 0;
    int temp = 0;

    sscanf (*text, "%s%n", jmp_name, &temp);

    (*text) += temp;

    temp_label_index = is_label_name (label, jmp_name);

    if (temp_label_index > 0)
    {
        printf ("goood\n");
        printf ("[%d]\n", label->value[temp_label_index - 1]);

        op_code[(*ip)++] = label->value[temp_label_index - 1];
    }
    else if (!(temp_label_index))
    {
        my_strcpy (label->name[*label_index], jmp_name);

        label->value[(*label_index)++] = UNDEFINED;
        op_code[(*ip)++] = UNDEFINED;
    }
    /*else
    {
        printf ("ERROR: label [%s] does not exist\n", jmp_name);
    }*///  if label is called twice or more it is not an error, but prints error, printing must be only in second init
}

int assemble_label_arg (char *cmd, int *ip, Label *label, int *label_index, int *err)
{
    int temp_label_index = 0;
    char *pname = strchr (cmd, ':');
    if (pname)
    {
        *pname = '\0';
    }

    temp_label_index = is_label_name (label, cmd);

    if (!(temp_label_index))
    {
        my_strcpy (label->name[(*label_index)], cmd);

        temp_label_index = *label_index;

        label->value[(*label_index)++] = *ip;

        fprintf (stderr, "label [%d]\n", label->value[(*label_index) - 1]);
    }
    else
    {
        label->value[--temp_label_index] = *ip;
        fprintf (stderr, "label is [%d]\n", label->value[temp_label_index]);

       /* if (temp_label_index > *label_index)
        {
            *label_index = temp_label_index + 1;
        }*/
    }

    if (pname)
    {
        *pname = ':';
    }

    return temp_label_index;
}

void write_opcode (FILE *out_file, int *op_code, int n_instr, const int magic_number, const int version)
{
    struct Header header = {};

    header.magic_number = magic_number;
    header.file_version = version;
    header.n_instr = n_instr;

    fwrite (&header, sizeof (struct Header), 1, out_file);
    fwrite (op_code, sizeof (int), n_instr, out_file);
}
