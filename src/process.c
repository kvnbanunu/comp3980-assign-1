/*
 * Kevin Nguyen
 * A00955925
 */

#include "../include/process.h"

char process(char cr, char (*filter_func)(char))
{
    return filter_func(cr);
}

char upper_filter(char c)
{
    if(c >= 'a' && c <= 'z')
    {
        return (char)(c - (char)('a' - 'A'));
    }
    return c;
}

char lower_filter(char c)
{
    if(c >= 'A' && c <= 'Z')
    {
        return (char)(c + (char)('a' - 'A'));
    }
    return c;
}

char null_filter(char c)
{
    return c;
}
