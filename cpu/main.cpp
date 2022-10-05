#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "..\..\standart_functions\io\io.h"
#include "cpu.h"

int main (int argc, const char *argv[])
{
    if (argc != 4)
    {
        printf ("ERROR: enter input file and nothing more");
    }

    FILE *input_file = fopen (argv[1], "rb");
    assert (input_file);

    int code_size = get_file_size (argv[1]);

    char *text = (char *)calloc (code_size + 2, sizeof (char));
    assert (text);

    int nlines = 0;
    int verbose = 0;    //debug

    read_in_buf (input_file, text, &nlines, code_size, verbose);  //

    int number = 0;

    text = check_code_file (text, &number, argv[2], argv[3]);

    if (text == nullptr)
    {
        return 0;
    }

    int *op_code = (int *)calloc (number, sizeof (int));
    assert (op_code);

    fill_code (text, op_code, number);

    calc (op_code, number);

    free (text);

    return 0;
}
