#include "minunit.h"
#include <lcthw/datastructures/radixmap.h>
#include "perf_test_runner.c"
#include <time.h>

static int make_random(RadixMap * map)
{
    size_t i = 0;
    for(i = 0; i < map->max -1; i++)
    {
        uint32_t key = (uint32_t)(rand() | (rand() << 16));
        check(RadixMap_add(map, key, i) == 0, "Failed to add %d", key);
        debug("Element i: %ul - Key: %u, Value %u \n", i, key, i);
    }

    return i;

    error:
        return 0;
}

static int check_order(RadixMap * map)
{
    RMElement d1, d2;
    unsigned int  i = 0;
    for(i = 0; map->end > 0 && i < map->end -1; i++)
    {
        d1 = map->contents[i];
        d2 = map->contents[i + 1];

        if(d1.data.key > d2.data.key)
        {
            debug("Fail: i=%u, key: %u, value %u, key2: %d?\n",
                i, d1.data.key, d1.data.value, d2.data.key
            );

            return 0;
        }
    }

    return 1;
}

static int test_search(RadixMap * map)
{
    unsigned i = 0;
    RMElement *d = NULL;
    RMElement *found = NULL;
    for(i = map->end / 2; i < map->end; i++)
    {
        d = &map->contents[i];
        found = RadixMap_find(map, d->data.key);
        check(found != NULL, "Didnt find %u at %u", d->data.key, i);
        check(found->data.key == d->data.key, "Got the wrong result: %p:%u looking for %u at %u", found, found->data.key, d->data.key, i);
    }

    return 1;
error:
    return 0;
}

static char *radix_perfTest()
{
    size_t N = 500;
    RadixMap * map = RadixMap_create(N);
    mu_assert(map != NULL, "Failed to make the map");
    mu_assert(make_random(map), "Didn't make a random map");
    RadixMap_sort(map);
    RadixMap_destroy(map);
    return NULL;

}

static char *test_operations()
{
    size_t N = 200;
    RadixMap * map = RadixMap_create(N);
    mu_assert(map != NULL, "Failed to make the map");
    mu_assert(make_random(map), "Didn't make a random map");

    RadixMap_sort(map);

    mu_assert(check_order(map), "Failed to properly sort the RadixMap");
    mu_assert(test_search(map), "Failed the search test");
    mu_assert(check_order(map), "Didn't stay sorted after search");

    while (map->end > 0)
    {
        RMElement * el = RadixMap_find(map, map->contents[map->end/2].data.key);
        mu_assert(el != NULL, "Should get a result");

        size_t old_end = map->end;

        mu_assert(RadixMap_delete(map, el) == 0, "Didn't delete");
        mu_assert(old_end - 1 == map->end, "Wrong size after delete");

        mu_assert(check_order(map), "Didn't stay sorted after delete");
    }

    RadixMap_destroy(map);

    return NULL;
    
}

char * all_tests()
{
    mu_suite_start();
    srand(time(NULL));

    mu_run_test(test_operations);
    RunPerformanceTest(radix_perfTest, "RADIX sort");
    return NULL;
}

RUN_TESTS(all_tests);