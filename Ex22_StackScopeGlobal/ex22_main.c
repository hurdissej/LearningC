#include "ex22.c"
#include "../dbg.h"

const char *MY_NAME = "Elliot Hurdiss";

void scope_demo(int count)
{
    log_info("Count is: %d", count);

    if(count > 10){
        int count = 100;
        log_info("Count in this scope is %d", count);
    }
    log_info("Count is at exit: %d", count);

    count = 3000;

    log_info("Count after assign: %d", count);
}

int main(int argc, char *argv[])
{
    log_info("My name: %s, age: %d", MY_NAME, get_age());

    set_age(100);

    log_info("My age is now : %d", get_age());

    // YOU HAVE BEEN HACKED MUAHAHAH!
    int *hackyPointer = &THE_AGE;
    *hackyPointer = 55;

    log_info("My age is now : %d", get_age());

    log_info("THE_SIZE is: %d", THE_SIZE);
    print_size();

    THE_SIZE = 9;

    log_info("THE_SIZE is: %d", THE_SIZE);
    print_size();

    log_info("Ratio at first: %f", update_ratio(2.0));
    log_info("Ratio again: %f", update_ratio(10.0));
    log_info("Ratio once more: %f", update_ratio(300.0));

    int count = 4;
    scope_demo(count);
    scope_demo(count * 20);

    log_info("Count after calling scope_demo: %d", count);

    return 0; 
}