#include "q.hpp"
#include <cstdio>
int main()
{
    const char *name = "haha";
    {
        printf("%s\n", name);
        printf("%s\n", love::name);
        extern const char *name;
        printf("%s\n", name);
    }
    return 0;
}