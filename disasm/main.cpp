#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "../../standart_functions/io/io.h"
#include "../calc.h"


int main (int argc, const char **argv)
{
    if (argc != 3)
    {
        printf ("enter file to disassembly and output file");
    }

    FILE *asm_file = fopen (argv[1], "rb");
    FILE *disasm_file = fopen (argv[2], "wb");

    assert (asm_file && disasm_file);





    int asm_size = get_file_size (argv[1]);

    char *text = (char *)calloc (asm_size + 2, sizeof (char));

    int nlines = 0;
    int verbose = 0;    //debug

    read_in_buf (asm_file, text, &nlines, asm_size, verbose);   //

    char *file_id = (char *)calloc (3, sizeof (char));
    char *file_version = (char *)calloc (4, sizeof (char));
    int number = 0;

    int ip = 0;
    sscanf (text, "%s%s%d%n", file_id, file_version, &number, &ip);

    fprintf (disasm_file, "%s\n%s\n%d\n", file_id, file_version, number);

    int *asm_code = (int *)calloc (number, sizeof (int));

    int index = 0;
    for (index = 0; index < number; index++)
    {
        int temp = 0;
        sscanf (text + ip, "%d%n", asm_code + index, &temp);
        iv p += temp;
    }

    index = 0;
    while (index < number)
    {
        switch (asm_code[index])
        {
            case CMD_PUSH:
            {
                fprintf (disasm_file, "push %d\n", asm_code[++index]);
                index++;

                break;
            }
            case CMD_SUB:
            {
                fprintf (disasm_file, "sub\n");
                index++;

                break;
            }
            case CMD_ADD:
            {
                fprintf (disasm_file, "add\n");
                index++;

                break;
            }
            case CMD_MULT:
            {
                fprintf (disasm_file, "mult\n");
                index++;

                break;
            }
            case CMD_DIV:
            {
                fprintf (disasm_file, "div\n");
                index++;

                break;
            }
            case CMD_OUT:
            {
                fprintf (disasm_file, "out\n");
                index++;

                break;
            }
            case CMD_HLT:
            {
                fprintf (disasm_file, "hlt");
                index = number;

                break;
            }
        }
    }

    free (file_id);
    free (file_version);
    free (asm_code);
}
