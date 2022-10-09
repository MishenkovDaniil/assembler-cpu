#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "cpu.h"
#include "../calc.h"


int check_asm_file (Head *head, const char *const file_id, const int version)
{
    assert (head);
    assert (file_id);

    if (stricmp (head->file_id, file_id))
    {
        fprintf (stderr, "ERROR: file_type is incorrect for this CPU");

        return CPU_INCORRECT_ID;
    }
    if (head->file_version != version)
    {
        fprintf (stderr, "ERROR: file version is not suitable for this CPU");

        return CPU_INCORRECT_VERSION;
    }
    if (head->number < 3)
    {
        fprintf (stderr, "ERROR: number of commands is too low");

        return CPU_INCORRECT_NUM;
    }

    return 0;
}
