#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main ()
{
    char *text = "1.0";
    double a = 0;
    a = atof (text);
    printf ("%lf", a);

    return 0;
}
