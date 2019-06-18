#include "minunit.h"
#include <lcthw/datastructures/darray.h>
#include "perf_test_runner.c"

static DArray *array = NULL;
static int *val1 = NULL;
static int *val2 = NULL;

char *test_create()
{
    array = DArray_create(sizeof(int), 100);
    mu_assert(array != NULL, "DArray create failed");
    mu_assert(array->contents != NULL, "Contents not set right");
    mu_assert(array->end == 0, "End isn't set right");
    mu_assert(array->element_size == sizeof(int), "Incorrect element size");
    mu_assert(array->max == 100, "Wrong max length on initial");

    return NULL;
}

char *test_destroy()
{
    DArray_destroy(array);

    return NULL;
}

char *test_new()
{
    val1 = DArray_new(array);
    mu_assert(val1 != NULL, "Failed to make new element");


    val2 = DArray_new(array);
    mu_assert(val2 != NULL, "Failed to make new element");
    return NULL;
}

char *test_set()
{
    DArray_set(array, 0, val1);
    DArray_set(array, 1, val2);

    return NULL;
}

char *test_get()
{
    mu_assert(DArray_get(array, 0) == val1, "Wrong first");
    mu_assert(DArray_get(array, 1) == val2, "Wrong second");
    return NULL;
}

char *test_remove()
{
    int *val_check = DArray_remove(array, 0);

    mu_assert(val_check != NULL, "Should not get NULL");
    mu_assert(*val_check == *val1, "Should get the first element");

    mu_assert(DArray_get(array, 0) == NULL, "Should be gone.")
    DArray_free(val_check);

    val_check = DArray_remove(array, 1);
    mu_assert(val_check != NULL, "Should not get NULL");
    mu_assert(*val_check == *val2, "Should get the second element");

    mu_assert(DArray_get(array, 1) == NULL, "Should be gone.")
    DArray_free(val_check);

    return NULL;
}

char *test_expand_contract()
{

    int old_max = array->max;
    DArray_expand(array);
    mu_assert((unsigned int)array->max == old_max + array->expand_rate, "Wrong size after expand");

    old_max = array->max;
    DArray_contract(array);
    mu_assert((unsigned int)array->max == array->expand_rate, "Wrong size after contraction");

    DArray_contract(array);
    mu_assert((unsigned int)array->max == array->expand_rate, "Should stay at the expand rate at least");

    return NULL;
}

char *test_push_pop()
{
    array = DArray_create(sizeof(int), 100);
    int i  = 0;
    for(i = 0; i < 100000; i++)
    {
        int *val = DArray_new(array);
        *val = i;
        DArray_push(array, val);
    }
    
    for(i = 99999; i >=0; i--)
    {
        
        int *val = DArray_pop(array);
        mu_assert(val != NULL, "Shouldn't be null");
        mu_assert(*val == i, "Wrong value");
        DArray_free(val);
    }
    DArray_destroy(array);
    return NULL;
}

char *all_tests()
{
    mu_suite_start();
    mu_run_test(test_create);
    mu_run_test(test_new);
    mu_run_test(test_set);
    mu_run_test(test_get);
    mu_run_test(test_remove);
    mu_run_test(test_expand_contract);
    mu_run_test(test_destroy);
    mu_run_test(test_push_pop);

    // Perf Tests
    RunPerformanceTest(test_push_pop, "DArray - PushPop");

    return NULL;
}

RUN_TESTS(all_tests);