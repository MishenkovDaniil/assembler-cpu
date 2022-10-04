#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define STACK_DEBUG

#include "..\..\Stack\stack\stack.h"
#include "..\..\standart_functions\io\io.h"

enum errors
{
    CPU_INCORRECT_ID      = nullptr,
    CPU_INCORRECT_VERSION = nullptr,
    CPU_INCORRECT_NUM     = nullptr
};


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

    int number = 0;

    if (!(check_code_file (text, &number, argv[2], argv[3]));
    {
        return 0;
    }

    int op_code [number] = {};

    fill_code (text, op_code);





    return 0;
}

char *check_code_file (char *text, int *num, const char *id, const char *version)
{
    int  i    = 0;
    int count = 0;

    const char *file_id = nullptr;
    const char *file_version = nullptr;

    while (*(text + i) && count < 3)
    {
        if (isspace(*(text + i)))
        {
            *(text + i) = '\0';

            if (count == 0)
            {
                file_id = text;
                if (stricmp (file_id, id) != 0)
                {
                    printf ("error id");//

                    return CPU_INCORRECT_ID;
                }
            }
            else if (count == 1)
            {
                file_version = text;

                if (stricmp (file_version, version) != 0)
                {
                    printf ("error version");//

                    return CPU_INCORRECT_VERSION;
                }
            }
            else
            {
                *num = atoi (text);

                if (*num < 3)
                {
                    printf ("incorrect input data"); //

                    return CPU_INCORRECT_NUM;
                }
            }

            text += i;

            count++;
        }

        i++;
    }

    return text;
}
