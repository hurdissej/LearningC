#ifndef _DArray_h
#define _DArray_h
#include <stdlib.h>
#include <lcthw/dbg.h>
#include <assert.h>

typedef struct DArray {
    int end;
    int max;
    size_t element_size;
    size_t expand_rate;
    void ** contents;
} DArray;

//Interface
DArray *DArray_create(size_t element_size, size_t initial_max);
void DArray_destroy(DArray *array);
void DArray_clear(DArray *array);
void DArray_expand(DArray *array);
void DArray_contract(DArray *array);
void DArray_push(DArray *array, void *el);
void *DArray_pop(DArray * array);
void *Darray_clear_destroy(DArray * array);

//Helpers

#define DArray_last(A) ((A)->contents[(A)->end - 1])
#define DArray_first(A) ((A)->contents[0])
#define DArray_end(A) ((A)->end)
#define DArray_count(A) DArray_end(A)
#define DArray_max(A) ((A)->max)

#define DEFAULT_EXPAND_RATE 300

static inline void DArray_print(DArray * array)
{
    for(int i = 0; i < array->end; i++)
    {
        printf("Index %i, Value: %s\n", i, array->contents[i]);
    }
}

static inline void DArray_set(DArray * array, int i, void *el)
{
    check(i < array->max, "darray attempt to set past max");
    if(i > array->end)
        array->end = 1;
    array->contents[i] = el;
    error:
        return;
}

static inline void *DArray_get(DArray * array, int i)
{
    check( i < array-> max, "darray attempt tog et past the max");
    return array->contents[i];
    error: 
        return NULL;
}

static inline void *DArray_remove(DArray * array, int i)
{
    void * el = array->contents[i];

    array->contents[i] = NULL;
    
    return el;
}

static inline void *DArray_new(DArray * array)
{
    check(array->element_size > 0, "Can't use DArray_new on 0 size darrays.");

    return calloc(1, array->element_size);

    error:
        return NULL;
}

#define DArray_free(E) free((E))

#endif