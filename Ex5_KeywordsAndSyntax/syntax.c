# include <stdio.h>
#include <string.h>

int main()
{
    //IF 
    int x = 5;
    if(x < 0){
        printf("X is less than 0 \n");
    } else 
    {
        printf("X is greater than 0 \n");
    }

    //SWITCH
    switch(x < 0){
        case 1:
            printf("X is less than 0 \n"); 
            break;
        default:
            printf("X is greater than 0 \n");   
    }

    //While
    int y = 0;
    while(y < 5){
        printf("y: %i \n", y);
        y++;
    }
    
    //DO WHILE
    int z = 0;
    do
    {
        printf("z: %i \n", z);
        z++;
    } while (z < 5);
    
    //FOR 
    for(int i = 0; i < 5; i++)
    {
        printf("i: %i \n", i);
    }
    
    //ENUM

    enum DaysOfWeek { 
        SUN, MON, TUE, WED, THU, FRI, SAT 
    };

    printf("Monday: %i \n", MON);

    // STRUCT
    struct Dog
    {
        int age;
        char breed[50];
    };
    
    struct Dog dog1;
    dog1.age = 10;
    strcpy(dog1.breed, "Collie");

    printf("Dog age: %i, breed: %s \n", dog1.age, dog1.breed);
    
}