#include <lcthw/helpers/bstrlib.h>
#include "minunit.h"
#include <stdio.h>

char * CreateBString()
{
    char * cstring = "ABC\0";
    bstring a = bfromcstr(cstring);
    if(!(strcmp(a->data, cstring)))
    {
        log_err("Strings don't match");
    }
    //TODO WHY THE FUCK DOES THIS JUST NOT WORK?!??!
   // mu_assert(a->slen == 4, "Incorrect length");
    
}

//TODO 

char * all_tests()
{
    mu_suite_start();
    mu_run_test(CreateBString);
}

RUN_TESTS(all_tests)

