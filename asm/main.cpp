#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "..\..\standart_functions\io\io.h"
#include "asm.h"


int main (int argc, const char *argv[])
{
    if (argc != 3)
    {
        printf ("Enter the name of input and output files to assembly and nothing more");

        return 0;
    }

    const int FILE_ID = 0x00005A4D;
    const int VERSION = 1;
    const int MAX_OP_LEN = 2;

    int nlines = 0;
    int verbose = 1;    //debug

    FILE *asm_file = fopen (argv[1], "rb");
    FILE *out_file = fopen (argv[2], "wb");

    assert (asm_file);
    assert (out_file);

    int txt_size = get_file_size (argv[1]);

    char *text = (char *)calloc (txt_size + 2, sizeof (char));
    assert (text);

    nlines = read_in_buf (asm_file, text, &nlines, txt_size, verbose);

    int *op_code = (int *)calloc (MAX_OP_LEN * nlines, sizeof (int));    //2!!!
    assert (op_code);

    Label label = {};

    init_code (text, op_code, &label);
    int number = init_code (text, op_code, &label);

    print_op_code (out_file, op_code, number, FILE_ID, VERSION);

    free (text);
    free (op_code);

    fclose (asm_file);
    fclose (out_file);

    return 0;
}
