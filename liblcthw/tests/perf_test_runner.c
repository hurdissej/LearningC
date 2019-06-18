#include <stdlib.h>
#include <time.h>


typedef char *benchmark ();

double DoWork(benchmark test)
{  
    clock_t start, end;
    double cpu_time_used;
     
    start = clock();
     
    test();

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

void PrintTable(char * name, double average)
{
    printf("-----------------------------\n");
    printf("Perf test resuts\n");
    printf("Function: %s\n", name);
    printf("Time Taken (ms): %f\n", average * 1000);
    printf("-----------------------------\n");
    
}

void RunPerformanceTest(benchmark *test, char *name)
{
    printf("Running test warm ups\n");
    double warmup = 0;
    for(int i = 0; i < 5; i++)
    {
        warmup += DoWork(test);
    }

    double totalTime = 0;
    printf("Beginning test run\n");
    for(int i = 0; i < 30; i++)
    {
        double time = DoWork(test);
        totalTime += time;
    }
    printf("Test run finished\n");
    double average = totalTime/ 30;


    PrintTable(name, average);
    
}