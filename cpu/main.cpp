#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

#include "cpu.h"
#include "..\calc.h"

int main (int argc, const char *argv[])
{
    if (argc > 6)
    {
        printf ("ERROR: enter input file, register values and nothing more");

        return 0;
    }

    FILE *asm_file = fopen (argv[1], "rb");
    assert (asm_file);
    --argc;

    const int FILE_ID = 0x00005A4D;
    const int VERSION = 1;

    struct Head head = {};
    struct Calc cpu = {};

    int reg_number = 1;

    while (--argc > 0)
    {
        cpu.regs[reg_number] = atoi (argv[reg_number + 1]);
        reg_number++;
    }

    fread (&head, sizeof (head), 1, asm_file);

    if (check_asm_file (&head, FILE_ID, VERSION))
    {
        return 0;
    }

    cpu.op_code = (int *)calloc (head.number, sizeof (int));
    assert (cpu.op_code);

    fread (cpu.op_code, sizeof (int), head.number, asm_file);

    calc (&cpu, head.number);

    free (cpu.op_code);
    fclose (asm_file);

    return 0;
}

