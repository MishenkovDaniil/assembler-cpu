#ifndef ASM_H
#define ASM_H

const int MAXSIZE = 32;
static const int MAXLEN = 20;

static const int UNDEFINED = -1;

static const int LABEL_NAME = 0;

struct Label
{
    int value[MAXSIZE] = {};
    char name[MAXSIZE][MAXLEN] = {};
    int status[MAXSIZE] = {};
};

int isspace_s (char *arr);
int is_label_name (Label *label, const char *jmp_name);
int init_code (char *text, int *op_code, Label *label);
void print_op_code (FILE *out_file, int *op_code, int number, const int file_id, const int version);
void assemble_pop_arg (char **text, int *op_code, int *ip, Label *label, int *label_index, int *err);
void assemble_push_arg (char **text, int *op_code, int *ip, Label *label, int *label_index, int *err);
void assemble_jmp_arg (char **text, int *op_code, int *ip, Label *label, int *label_index, int *err);
int assemble_label_arg (char *cmd, int *ip, Label *label, int *label_index, int *err);

#endif /* ASM_H */
