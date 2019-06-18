#include <stdio.h>

int main()
{
    char *name = "Elliot";
    char name2[] = "Elliot";

    printf("name %s \n", name);
    printf("name2 %s \n", name2);

    printf("Size %i \n", sizeof(name));
    printf("Size2 %i \n", name2);
}