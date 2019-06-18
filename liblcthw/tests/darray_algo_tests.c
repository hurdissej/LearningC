#include "minunit.h"
#include "perf_test_runner.c"
#include <lcthw/algorithms/darray_algos.h>

int testcmp(char **a, char **b)
{
    return strcmp(a, b);
}

DArray *create_words()
{
    DArray *result = DArray_create(0,5);
    char *words[] = { "asdaf", "wewar", "1324", "asdaf", "oioj" };
    int i = 0;

    for(i = 0; i < 5; i++)
    {
        DArray_push(result, words[i]);
    }

    return result;
}

int is_sorted(DArray * array)
{
    int i = 0;

    for(i = 0; i < DArray_count(array) - 1; i++)
    {
        if(strcmp(DArray_get(array, i), DArray_get(array, i + 1)) > 0)
        {
            return 0;
        }
    }

    return 1;
}

char *run_sort_test(int (*func)(DArray *, DArray_compare), const char *name)
{
    DArray *words = create_words();
    mu_assert(!is_sorted(words), "Words should not start sorted");

    debug("--- Testing %s sorting algorithm\n", name);
    int rc = func(words, (DArray_compare)testcmp);
    
    mu_assert(rc == 0, "Sort failed");
    mu_assert(is_sorted(words), "Didn't sort correctly");

    DArray_destroy(words);

    return NULL;
}

char *test_qsort()
{
    return run_sort_test(DArray_qsort, "qsort");
}

char *test_mergesort()
{
    return run_sort_test(DArray_mergesort, "mergesort");
}

char *test_heapsort()
{
    return run_sort_test(DArray_heapsort, "heapsort");
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_mergesort);
    //mu_run_test(test_heapsort);
    mu_run_test(test_qsort);
    

    //Perf tests
    RunPerformanceTest(test_mergesort, "Merge sort");
    RunPerformanceTest(test_qsort, "Quick sort");
    return NULL;
}

RUN_TESTS(all_tests);