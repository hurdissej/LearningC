#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//Outline what a person looks like
struct Person
{
    char *name;
    int age;
    int height;
    int weight;
};

//Constructing a person
struct Person *Person_create(char *name, int age, int height, int weight)
{
    //Memory allocate a piece of memory to contain a struct
    struct Person *who = malloc(sizeof(struct Person));
    // Check that pointer is correct
    assert(who != NULL);

    //Copy the string (string duplicate) into the struct
    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    // return the person
    return who;
}

//Deallocate the memory to avoid leaks
void Person_destroy(struct Person *who)
{
    assert(who != NULL);
    //Release the string
    free(who->name);
    //Release the person
    free(who);
}

void Person_print(struct Person *who)
{
    printf("Name: %s \n", who->name);
    printf("\tAge: %d \n", who->age);
    printf("\tHeight: %d \n", who->height);
    printf("\tWeight: %d \n", who->weight);
}

int main()
{
    struct Person *robin = Person_create("Robin", 25, 71, 72);
    struct Person *elliot = Person_create("Elliot", 28, 70, 72);

    printf("Robin is at memory location %p: \n", robin);
    Person_print(robin);

    printf("Elliot is at memory location %p: \n", elliot);
    Person_print(elliot);

    robin->weight += 75;

    Person_print(robin);

    Person_destroy(robin);
    Person_destroy(elliot);

    //Initialise a person on the stack
    struct Person steph;
    steph.name = "Steph";
    steph.age = 27;
    steph.height = 48;
    steph.weight = 50;

    // Just pass the address to steph to this function
    Person_print(&steph);

    steph.age = 28;

    // Just pass the address to steph to this function
    Person_print(&steph);
}
