#include <stdio.h>

int main(int argc, char *argv[])
{
    int ages[] = { 25, 28, 27, 30 };
    char *names[] = {
        "Robin", "Elliot", "Steph", "Jonna"
    };

    int count = sizeof(ages)/ sizeof(int);

    int i = 0;

    for(i = 0; i < count; i++)
    {
        printf("%s is %d years old \n", names[i], ages[i]);
    }

    printf("---- \n");
    
    int *curr_age = ages;
    char **curr_name = names;

    for(i = 0; i < count; i++)
    {
        printf("%s is %d years old \n", *(curr_name + i), *(curr_age + i));
    }

    printf("---- \n");

    for(i = 0; i < count; i++)
    {
        printf("%s is %d years old \n", curr_name[i], curr_age[i]);
    }

    printf("---- \n");

    for(curr_name = names, curr_age = ages; 
        (curr_age - ages) < count; 
        curr_name++, curr_age++){
            printf("%s is %d years old \n", *curr_name, *curr_age);
        }
        
}