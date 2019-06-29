#include <stdio.h>
#include "minunit.h"
#include <lcthw/algorithms/radix_sort.h>
#include <assert.h>


char * standard_sort()
{
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66}; 

    radsort(&arr, 8); 
    
    for(int i = 0; i < 8; i++)
    {
        printf("Post sort item %d = %d\n", i, arr[i]);
    }

    return 0; 
}

static char * all_tests()
{
    mu_suite_start();

    mu_run_test(standard_sort);

    return NULL;
}

RUN_TESTS(all_tests);