#include <lcthw/datastructures/darray.h>

DArray *DArray_create(size_t element_size, size_t initial_max)
{
    DArray *result = malloc(sizeof(DArray));
    check(initial_max > 0, "Initial max must be more than 0");
    check_mem(result);
    result->max = 100;
    result->element_size = element_size;
    result->end = 0;
    result->expand_rate = DEFAULT_EXPAND_RATE;
    result->contents = calloc(initial_max, sizeof(void*));
    check_mem(result->contents);

    return result;

    error:
    if(result)
        free(result);

    return NULL;
}

void DArray_expand(DArray *array)
{
    int new_size = array->max + array->expand_rate;

    void * contents = realloc(array->contents, new_size * sizeof(void*));
    check_mem(contents);

    array->max = new_size;
    array->contents = contents;
    return;

    error:
        memset(array->contents + array->max, 0, array->expand_rate);
        return;
}

void DArray_contract(DArray *array)
{
    int new_size = array->end < (int)array->expand_rate ? array->expand_rate : array->end;
    void * contents = realloc(array->contents, new_size * sizeof(void*));
    check_mem(contents);
    array->max = new_size;
    array->contents = contents;
    return;
    error:
        return;
}


void DArray_push(DArray *array, void *el)
{
    array->contents[array->end] = el;
    array->end++;
    
    if(array->end >= array->max)
    {
        DArray_expand(array);
    } 
}

void *DArray_pop(DArray * array)
{
    check(array->end  - 1 >= 0, "Attempt to pop from empty list");
    int * val = DArray_remove(array, array->end -1);
    array->end--;
    return val;

    error:
        return NULL;
}


void DArray_destroy(DArray *array) 
{
    if(array){
        if(array->contents)
        {
            free(array->contents);
        }
        free(array);
    }
    
}