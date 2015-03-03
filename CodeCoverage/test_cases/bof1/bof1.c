#include <string.h>
#include <stdio.h>

void foo(char *bar)
{
    char c[12];

    strcpy(c, bar);  // no bounds checking
    fflush(stdout);
}

int main(int argc, char **argv)
{
    char buf[4096];

    printf("input: ");
    fgets(buf,4096,stdin);
    foo(buf);
}
