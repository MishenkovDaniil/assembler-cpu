#ifndef ASM_H
#define ASM_H

const int MAXSIZE = 5;
const int MAXLEN = 10;
struct Label
{
    int value[MAXSIZE] = {};
    char name[MAXSIZE][MAXLEN] = {};
};

int is_label_name (Label *label, const char *jmp_name);
int init_code (char *text, int *op_code, Label *label);
void print_op_code (FILE *out_file, int *op_code, int number, const int file_id, const int version);
void assemble_push_arg (char **text, int *op_code, int *ip);
void assemble_jmp (char **text, int *op_code, int *ip, Label *label, int *label_index);
void assemble_label (char *cmd, int *ip, Label *label, int *label_index);

#endif /* ASM_H */
