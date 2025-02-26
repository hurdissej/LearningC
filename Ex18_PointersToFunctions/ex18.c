#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char *message)
{
    if(errno){
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    exit(1);
}

typedef int (*compare_cb) (int a, int b);

int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;

    int *target = malloc(count * sizeof(int));

    if(!target)
        die("Memory Error!");

    memcpy(target, numbers, count * sizeof(int));

    for(int i = 0; i < count; i++){
        for(int j = 0; j < count - 1; j++){
            if(cmp(target[j], target[j+1]) > 0)
            {
                temp = target[j + 1];
                target[j + 1] = target[j];
                target[j] = temp;
            }
        }
    }

    return target;
}

int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if(a == 0 || b == 0){
        return 0;
    } else {
        return a % b;
    }
}

void test_sorting(int *numbers, int count, compare_cb cmp)
{
    int *sorted = bubble_sort(numbers, count, cmp);
    if(!sorted)
    {
        die("Failed to sort as requested");
    }

    for(int i = 0; i < count; i++){
        printf("%d", sorted[i]);
    }
    printf("\n");
    free(sorted);

    unsigned char *raw_data = (unsigned char *)cmp;
    for(int i = 0; i < 25; i++)
    {
        printf("%d", raw_data[i]);
    }

    printf("\n");
}

int main(int argc, char *argv[])
{
    if(argc < 2) die ("Must specify at least two numbers to be sorted");

    int count = argc - 1;

    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(count));
    if(!numbers) die("Memory Error");

    for(int i = 0; i < count; i++)
    {
        numbers[i] = atoi(inputs[i]);
    }

    test_sorting(numbers, count, sorted_order);
    test_sorting(numbers, count, reverse_order);
    test_sorting(numbers, count, strange_order);

    free(numbers);
    return 0;
}