#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;
    char **current_arg = argv;
    for(current_arg = argv; (current_arg - argv) < argc; current_arg++)
    {
        printf("arg %d: %s \n", i, *(current_arg + i));
    }
    
    return 0;

}