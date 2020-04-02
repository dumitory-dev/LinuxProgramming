#include <stddef.h>

int stringStat(char const * string, size_t multiplier, int * count)
{
    size_t len = 0;
    while (*string++)
        ++len;
    ++*count;
    return len * multiplier;    
}