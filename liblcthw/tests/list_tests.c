#include "minunit.h"
#include <lcthw/datastructures/list.h>
#include "perf_test_runner.c"
#include <assert.h>

char *test1 = "testData1";
char *test2 = "testData2";
char *test3 = "testData3";

char * test_create()
{
    List *list = List_create();
    mu_assert(list != NULL, "Failed to initialise");

    List_destroy(list);
    return NULL;
}

char * test_pushpop()
{
    List *list = List_create();
    List_push(list, test1);
    mu_assert(list->last->value == test1, "Wrong last value - 1");

    List_push(list, test2);
    mu_assert(list->last->value == test2, "Wrong last value - 2");

    List_push(list, test3);
    mu_assert(list->last->value == test3, "Wrong last value - 3");

    char * val = List_pop(list);
    mu_assert(val == test3, "Wrong popped value");
    mu_assert(list->count == 2, "Should be two left");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong popped value");
    mu_assert(list->last->value == test1, "incorrect last value");
    mu_assert(list->count == 1, "Should be one left");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong popped value");
    mu_assert(list->count == 0, "Should be none left");

    List_clear_destroy(list);
   return NULL;
}

char *test_shift()
{
    List *list = List_create();

    mu_assert(list->count == 0, "Should start with an empty list")

    List_unshift(list, test1);
    List_unshift(list, test2);
    List_unshift(list, test3);

    mu_assert(list->first->value == test3, "first value should be Test3");
    mu_assert(list->last->value == test1, "last value should be Test1");
    mu_assert(list->count == 3, "List should have 3 values");

    char * val = List_shift(list);
    mu_assert(val == test3, "shifted value should be test 1");
    mu_assert(list->first->value == test2, "First value should be test2");
    mu_assert(list->last->value == test1, "Last value should be test3");

    val = List_shift(list);
    mu_assert(val == test2, "shifted value should be test 2");
    mu_assert(list->first->value == test1, "Final value should be test3");

    val = List_shift(list);
    mu_assert(val == test1, "shifted value should be test 3");

    mu_assert(list->count == 0, "List should be empty");
    List_clear_destroy(list);
    return NULL;
}

char *perf_push_pop()
{
    List *list = List_create();

    int i  = 0;
    for(i = 0; i < 100000; i++)
    {
        List_push(list, test1);
    }

    for(i = 99999; i >=0; i--)
    {
        
        char *val = List_pop(list);
        mu_assert(val != NULL, "Shouldn't be null");
        mu_assert(val == test1, "Wrong value");
    }
    List_destroy(list);
    return NULL;
}


char *all_tests()
{
    mu_suite_start();
    mu_run_test(test_create)
    mu_run_test(test_pushpop);
    mu_run_test(test_shift);
    
    //Performance test
    RunPerformanceTest(perf_push_pop, "List push/pop");


    return NULL;
}

RUN_TESTS(all_tests);