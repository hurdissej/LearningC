#include <stdio.h>
#include "../dbg.h"

#define MAX_DATA 100

typedef enum EyeColor { 
    BLUE_EYES,
    GREEN_EYES,
    BROWN_EYES,
    BLACK_EYES,
    OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = 
{
    "Blue",
    "Green",
    "Brown",
    "Black",
    "Other"
};

struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
};

int main(int argc, char *argv[])
{
    struct Person you = {.age = 0};
    int i = 0;
    char *in = NULL;

    printf("What's your first name? ");
    in = fgets(you.first_name, MAX_DATA - 1, stdin);
    check(in != NULL, "Failed to read first name");

    printf("What's your last name? ");
    in = fgets(you.last_name, MAX_DATA - 1, stdin);
    check(in != NULL, "Failed to read last name");

    printf("What's your age? ");
    int rc = fscanf(stdin, "%d", &you.age);
    check(rc > 0 , "Enter a valid age");

    printf("What color are your eyes? ");
    for(i = 0; i <= OTHER_EYES; i++)
    {
        printf("%d %s \n", i+1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    rc = fscanf(stdin, "%d", &eyes);
    check(rc > 0, "You have to enter a number.");

    you.eyes = eyes - 1;
    check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Enter a valid eye color you mug!");

    printf("How much do you make an hour? ");
    rc = fscanf(stdin, "%f", &you.income);

    printf("-----RESULTS---- \n");
    printf("First Name: %s", you.first_name);
    printf("Last Name: %s", you.last_name);
    printf("age: %d \n", you.age);
    printf("Eye color: %s \n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f \n", you.income);

    return 0;

    error: return -1;
}