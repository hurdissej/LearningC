#include <stdio.h>
#include <ctype.h>

void print_letters(char arg[])
{
    int i = 0;
    
    for(i = 0; arg[i] != '\0'; i++)
    {
        char ch = arg[i];
        if(isalpha(ch) || isblank(ch)){
            printf("'%c' == %d \n", ch, ch);
        };
    }
}


void print_arguments(int argc, char *argv[])
{
    int i = 0;
    for(i = 0; i< argc; i++)
    {
        print_letters(argv[i]);
    }
}

int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
}