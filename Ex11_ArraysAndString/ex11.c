#include <stdio.h>

int main()
{
    int numbers[4] = { 0 };
    char name[4] = {'a'};

    printf("numbers %d %d %d \n",
    numbers[0], numbers[1], numbers[2]
    );

    printf("name each: %c %c %c \n",
    name[0], name[1], name[2]
    );

    printf("name: %s \n", name);

    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;

    char *name2 = "EJH";

    printf("numbers %d %d %d \n",
    numbers[0], numbers[1], numbers[2]
    );

    printf("name2 each: %i %c %d \n",
    name2[0], name2[1], name2[2]
    );

    printf("name: %s \n", name);

    char *another = "Zed";

    printf("another: %s\n", another);
}