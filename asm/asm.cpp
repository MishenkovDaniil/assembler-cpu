#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "..\..\standart_functions\io\io.h"
#include "..\calc.h"
#include "asm.h"

int main (int argc, const char *argv[])
{
    if (argc != 3)
    {
        printf ("Enter the name of input and output files to assembly and nothing more");

        return 0;
    }

    FILE *asm_file = fopen (argv[1], "rb");
    FILE *out_file = fopen (argv[2], "wb");

    assert (asm_file);
    assert (out_file);

    int txt_size = get_file_size (argv[1]);

    char *text = (char *)calloc (txt_size + 2, 1);
    assert (text);

    int nlines = 0;
    int verbose = 1;    //debug

    nlines = read_in_buf (asm_file, text, &nlines, txt_size, verbose);

    int *op_code = (int *)calloc (2 * nlines, sizeof (int));    //2!!!
    assert (op_code);

    int number = fill_codes (text, op_code);

    print_text (out_file, op_code, number);

    //fwrite (cmd, sizeof (int), index, out_file);

    free (text);
    free (op_code);

    return 0;
}
