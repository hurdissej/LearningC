#include "minunit.h"
#include <dlfcn.h>

typedef int (*lib_function) (int argc, char *argv[]);
char *lib_file = "build/libYOUR_LIBRARY.so";
void *lib = NULL;

//Run func
int check_function(const char *func_to_run, int argc, char *argv[],
        int expected)
{
    lib_function func = dlsym(lib, func_to_run);
    check(func != NULL,
            "Did not find %s function in the library %s: %s", func_to_run,
            lib_file, dlerror());

    int rc = func(argc, argv);
    check(rc == expected, "Function %s return %d",
            func_to_run, rc);

    return 1;
error:
    return 0;
}

//Open library file
char *test_dlopen()
{
    lib = dlopen(lib_file, RTLD_NOW);
    mu_assert(lib != NULL, "Failed to open the library to test.");

    return NULL;
}

//Test Functions
char *test_functions()
{
    char *arr[1] = {"logs"};
    mu_assert(check_function("main", 2, arr, 1),
            "print_a_message failed.");

    return NULL;
}

//Close library file
char *test_dlclose()
{
    int rc = dlclose(lib);
    mu_assert(rc == 0, "Failed to close lib.");

    return NULL;
}

char *all_tests()
{
    //Reset test suite
    mu_suite_start();

    //Open test file
    mu_run_test(test_dlopen);
    //Run tests
    mu_run_test(test_functions);
    //Close test file
    mu_run_test(test_dlclose);

    return NULL;
}

RUN_TESTS(all_tests);