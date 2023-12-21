#include <stdio.h>
#include <string.h>

const char *match(const char *s, char ch)
{
    while (*s != '\0')
    {
        if (*s == ch)
        {
            return s; // Found the character, return its position
        }
        s++; // Move to the next character in the string
    }

    return NULL; // Character not found, return NULL
}