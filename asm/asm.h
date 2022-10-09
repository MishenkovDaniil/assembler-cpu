#ifndef ASM_H
#define ASM_H

const int MAXSIZE = 5;

struct Label
{
    int value[MAXSIZE] = {};
    const char *name[MAXSIZE] = {};
};

int is_label_name (Label *label, const char *jmp_name);
int init_code (char *text, int *op_code, Label *label);
void print_op_code (FILE *out_file, int *op_code, int number, const char *const file_id, const int version);


#endif /* ASM_H */
