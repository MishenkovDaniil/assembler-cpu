#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "..\..\standart_functions\io\io.h"
#include "cpu.h"
#include "../calc.h"

int main (int argc, const char *argv[])
{
    if (argc != 2)
    {
        printf ("ERROR: enter input file and nothing more");
    }

    FILE *asm_file = fopen (argv[1], "rb");
    assert (asm_file);

    const int FILE_ID = 0x00005A4D;
    const int VERSION = 1;

    struct Head head = {};

    fread (&head, sizeof (head), 1, asm_file);
    printf ("%d\n%d\n%d\n", head.file_id, head.file_version, head.number);

    if (check_asm_file (&head, FILE_ID, VERSION))
    {
        return 0;
    }

    int *op_code = (int *)calloc (head.number, sizeof (int));
    assert (op_code);

    fread (op_code, sizeof (int), head.number, asm_file);
    int  i = 0;
    while (i < head.number)
    {
        printf ("%d\t", op_code[i++]);
    }
    calc (op_code, head.number);

    free (op_code);
    fclose (asm_file);

    return 0;
}
