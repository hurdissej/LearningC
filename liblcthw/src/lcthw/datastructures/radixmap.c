#include <stdlib.h>
#include <lcthw/datastructures/radixmap.h>
#include <stdio.h>
#include <assert.h>
#include <lcthw/dbg.h>

RadixMap *RadixMap_create(size_t max)
{
    RadixMap *map = calloc(sizeof(RadixMap), 1);
    check_mem(map);

    map->contents = calloc(sizeof(RMElement), max + 1);
    map->temp = calloc(sizeof(RMElement), max + 1);
    check_mem(map->contents);
    check_mem(map->temp);

    map->max = max;
    map->end = 0;

    return map;

    error:
        return NULL;
}

void RadixMap_destroy(RadixMap * map)
{
    if(map)
    {
        free(map->contents);
        free(map->temp);
        free(map);
    }
}

#define ByteOf(x,y) (((uint8_t *)x)[(y)])

//ToDo give this a once over and give the pointers better names
/* E.g. 
Offset = 0 
4
[5, 4, 6, 9]
[]
*/
static inline void radix_sort(short offset, uint64_t max, 
                        uint64_t * source, uint64_t * dest)
{
    uint64_t count[256] = {0};
    uint64_t *cp = NULL;
    uint64_t *sp = NULL;
    uint64_t *end = NULL;
    uint64_t s = 0;
    uint64_t c = 0;

    for(sp = source, end = source + max; sp < end; sp++)
    {
        //Put the nth byte of each item in source into the count array
        /* e.g.
        sp = 5, end = 4
        */
        count[ByteOf(sp, offset)]++;
    }

    //Count looks like [0, 0, 0, 0, 1, 1, 1, 0, 0, 1]
    for(s = 0, cp = count, end = count + 256; cp < end; cp ++)
    {
        //Going through the count array
        c = * cp;
        *cp = s;
        s += c;
        //S is the total value?
    }

    //Set the values in the dest array
    for(sp = source, end = source + max; sp < end; sp ++)
    {
        //Start at the lowest values of count (i.e. those with the smallest first byte)
        cp = count + ByteOf(sp, offset);
        //Add the whole int to the destination array
        dest[*cp] = * sp;
        //Increment the cp pointer 
        ++(*cp);
    }
}

void RadixMap_sort(RadixMap * map)
{
    uint64_t *source = &map->contents[0].raw;
    uint64_t *temp= &map->temp[0].raw;
    //each int has 64 bits - 32 bits for the key (which we sort on) and 32 bits for the value
    //We are sorting 8 bits at a time
    //Which means we need 4 iterations (we could rewrite this)
    radix_sort(0, map->end, source, temp);
    radix_sort(1, map->end, temp, source);
    radix_sort(2, map->end, source, temp);
    radix_sort(3, map->end, temp, source);
}

RMElement *RadixMap_find(RadixMap * map, uint32_t to_find)
{
    int low = 0;
    int high = map->end - 1;
    RMElement * data = map->contents;

    while(low <= high)
    {
        int middle = low + (high-low) / 2;
        uint32_t key = data[middle].data.key;
        if(to_find < key)
        {
            high = middle - 1;
        } else if (to_find > key)
        {
            low = middle + 1;
        } else 
        {
            return &data[middle];
        }
    }

    return NULL;
}

int RadixMap_add(RadixMap * map, uint32_t key, uint32_t value)
{
    check(key < UINT32_MAX, "Key can't be greater than 2bn");
    RMElement elemenet = {.data = {.key = key, .value = value}};

    map->contents[map->end++] = elemenet;

    RadixMap_sort(map);

    return 0;

    error: 
        return 1;
}

int RadixMap_delete(RadixMap * map, RMElement * el)
{
    check(map->end > 0, "There is nothing to delte");
    check(el != NULL, "Can't delete a null element");

    el->data.key = UINT32_MAX;
    if(map->end > 1)
    {
        RadixMap_sort(map);
    }
    map->end--;
    return 0;
    error: 
        return 1;
}
