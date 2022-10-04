#ifndef ASM_H
#define ASM_H

int init_code (char *text, int *op_code);
void print_text (FILE *out_file, int *op_code, int num, const char *id, const char *version);

#endif /* ASM_H */
