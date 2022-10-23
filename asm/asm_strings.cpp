#include <ctype.h>
#include <string.h>

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

int is_comment (char *cmd, char **text)
{
    int return_value = 0;

    if (strstr (cmd, "//"))
    {
        *text = strchr (*text, '\n');
        skip_spaces (text);

        return_value = 1;
    }
    if (strstr (cmd, "/*"))
    {
        *text = strstr (*text, "*/");
        if (*text)
        {
            *text += 2;

            skip_spaces (text);

            return_value = 1;
        }
        else
        {
            return -1;      //make error
        }
    }

    return return_value;
}
