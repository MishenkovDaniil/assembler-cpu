#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "..\..\Stack\stack\stack.h"

int main (int argc, const char *argv[])
{
    if (argc != 2)
    {
        printf ("ERROR: enter input file and nothing more");
    }

    FILE *input_file = fopen (argv[1], "rb");
    assert (input_file);



    return 0;
}
