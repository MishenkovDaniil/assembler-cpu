#ifndef CPU_H
#define CPU_H

char *check_code_file (char *text, int *num, const char *id, const char *version);
void fill_code (char *text, int *op_code, int number);
int calc (int *op_code, int number);

static char *CPU_INCORRECT_ID      = nullptr;
static char *CPU_INCORRECT_VERSION = nullptr;
static char *CPU_INCORRECT_NUM     = nullptr;



#endif /* CPU_H */
