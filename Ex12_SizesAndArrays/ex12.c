#include <stdio.h>

int main(int argc, char *argv[])
{
        char fullName[] = {
        'E', 'L', 'L', 'I', 'O', 'T'
    };
    int areas[] = { 10, 20, 30};
    char name[] = "Elliot";

    char *names[] = {"Ejh", "ABC"};

    printf("Sizeof Names: %ld \n", sizeof(names[0]));

    printf("The size of an int: %ld \n", sizeof(int));
    printf("The size of an areas: %ld \n", sizeof(areas));
    printf("The size of an int in areas: %ld \n", sizeof(areas)/ sizeof(int));

    printf("The first area is %d and the 2nd is %d \n", areas[0], areas[1]);

    printf("The size of char: %ld \n", sizeof(char));
    printf("The size of name: %ld \n", sizeof(name));
    
    printf("The size of fullname: %ld \n", sizeof(fullName));
}