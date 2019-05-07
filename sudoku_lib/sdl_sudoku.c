//
// Created by TheRolf on 03/05/2019.
//

#include <stdio.h>
#include <stdlib.h>

char *convertInt(int b)
{
    char *a;
    int Count = 1, Temp = b;

    /* get number of digits */
    while (Temp > 0)
    {
        Temp /= 10;
        Count++;
    }

    /* allocate the memory */
    a = (char *)malloc(Count+1);

    /* convert to string */
    sprintf(a, "%d", b);

    return a;
}