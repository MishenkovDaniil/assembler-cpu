#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "cpu.h"


char *check_code_file (char *text, int *num, const char *id, const char *version)
{
    assert (text);
    assert (id && version);

    int  i    = 0;
    int count = 0;

    char *file_id = nullptr;
    char *file_version = nullptr;

    while (*(text + i) != '\0' && count < 3)
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
                    return CPU_INCORRECT_NUM;
                }
            }

            text += i + 1;
            i = 0;

            if (++count == 3)
            {
                return text;
            }
        }

        else
        {
            i++;
        }
    }

    return text;
}

void fill_code (char *text, int *op_code, int number)
{
    assert (text);
    assert (op_code && number);

    int ip = 0;
    int temp = 0;
    int index = 0;

    while (index < number)
    {
        sscanf (text + ip, "%d %n", &op_code[index], &temp);

        printf ("[%d]\n", op_code[index]);

        ip += temp;
        temp = 0;

        index++;
    }
}
