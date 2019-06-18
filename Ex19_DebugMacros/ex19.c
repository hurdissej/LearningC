#include "dbg.h"

void test_debug()
{
    debug("I have brown eyes");
    debug("I am %d years old", 30);
}

void test_log_err()
{
    log_err("'s'all broken");
}

void test_log_warn()
{
    log_warn("Warning");
}

void test_log_info()
{
    log_info("Informacion!");
}

int test_check()
{
    char *test = NULL;
    check_mem(test);

    free(test);
    return 1;

error:
    return -1;
}


int main(int argc, char *argv[])
{
    test_debug();
    test_log_info();
    test_log_warn();
    test_log_err();
    test_check();
}
