#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

#include "cpu.h"
#include "../calc.h"

int main (int argc, const char *argv[])
{
    if (argc > 6)
    {
        printf ("ERROR: enter input file, register values and nothing more");

        return 0;
    }

    FILE *asm_file = fopen (argv[1], "rb");
    assert (asm_file);

    const int FILE_ID = 0x00005A4D;
    const int VERSION = 1;

    struct Head head = {};
    struct Calc ccalc = {};

    ccalc.regs[1] = atoi (argv[2]);
    ccalc.regs[2] = atoi (argv[3]);
    ccalc.regs[3] = atoi (argv[4]);
    ccalc.regs[4] = atoi (argv[5]);

    fread (&head, sizeof (head), 1, asm_file);

    if (check_asm_file (&head, FILE_ID, VERSION))
    {
        return 0;
    }

    ccalc.op_code = (int *)calloc (head.number, sizeof (int));
    assert (ccalc.op_code);

    fread (ccalc.op_code, sizeof (int), head.number, asm_file);

    calc (&ccalc, head.number);

    free (ccalc.op_code);
    fclose (asm_file);

    return 0;
}
