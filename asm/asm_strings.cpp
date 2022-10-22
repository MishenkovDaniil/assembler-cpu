#include <ctype.h>

#include "asm_strings.h"

int is_empty_str (char *arr)
{
    while (*arr != '\0')
    {
        if (!(isspace (*arr)))
        {
            return 0;
        }
        else
        {
            arr++;
        }
    }
    return 1;
}

void skip_spaces (char **text)
{
    while (isspace (**text))
    {
        (*text)++;
    }
}
