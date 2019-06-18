#include <stdio.h>

int main()
{
    int distance = 100;
    float power = 2.345f;
    double super_power = 123.456;
    char initial = 'J';
    char first_name[] = "Elliot";
    char last_name[] = "Hurdiss";

    printf("You are %d miles away. \n", distance);
    printf("You have %f levels of power. \n", power);
    printf("You are %f levels of super power. \n", super_power);
    printf("My full name is %s %c %s. \n", first_name, initial, last_name);

    int bugs = 100;
    double bug_rate = 1.2;

    printf("You have %i bugs at the imaginary rate of %f \n", bugs, bug_rate);

    unsigned long universe_of_defects = 1L * 1024L * 1024L * 1024L * 1024L * 1024L * 1024L * 1024L;

    printf("The universe has %ld bugs. \n", universe_of_defects);

    double expected = 100 * 1.2;
    printf("You are expected to have %f bugs. \n", expected);

    double part_of_universe = expected / universe_of_defects;
    printf("That is only a %e portfion of the universe \n", part_of_universe);

    char null_byte = '\0';
    int care_percentage = bugs * null_byte;
    printf("Which means you should care %d%% \n", care_percentage);
}