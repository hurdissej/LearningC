#include <lcthw/algorithms/darray_algos.h>
#include <stdlib.h>

int partition(DArray * array, int low, int high, DArray_compare cmp)
{
    void * partition = array->contents[high];   
    int j = low;
    for(int i = low; i < array->end; i++)
    {
        if(cmp(array->contents[i], partition) < 0)
        {
            void * temp = array->contents[j];
            array->contents[j] = array->contents[i];
            array->contents[i] = temp;
            j++;
        }
    }
    void * temp = array->contents[j];
    array->contents[j] = partition;
    array->contents[high] = temp;
    return j;
}

void quick_sort(DArray * array, int low, int high, DArray_compare cmp)
{
    if(low < high)
    {
        int pi = partition(array, low, high, cmp);

        quick_sort(array, low, pi-1, cmp);
        quick_sort(array, pi + 1, high, cmp);
    }
}

void merge(DArray * array, int start, int mid, int end, DArray_compare cmp)
{
    //create a temp array
    void *temp[end - start + 1];
    
    int i = start, j = mid+1, k = 0;

	// traverse both arrays and in each iteration add smaller of both elements in temp 
	while(i <= mid && j <= end) {
		if(strcmp(array->contents[i], array->contents[j]) < 0) 
        {
			temp[k] = array->contents[i];
			k += 1; i += 1;
		}
		else {
			temp[k] = array->contents[j];
			k += 1; j += 1;
		}
	}

    while(i <= mid) {
		temp[k] = array->contents[i];
		k += 1; i += 1;
	}

	// add elements left in the second interval 
	while(j <= end) {
		temp[k] = array->contents[j];
		k += 1; j += 1;
	}

	// copy temp to original interval
	for(i = start; i <= end; i += 1) {
		array->contents[i] = temp[i - start];
	}
}

void merge_sort(DArray * array, int start, int end, DArray_compare cmp)
{
    if(start < end)
    {
        int mid = (start + end) / 2;
        merge_sort(array, start, mid, cmp);
        merge_sort(array, mid+1, end, cmp);
        merge(array, start, mid, end, cmp);
    }
}

int DArray_mergesort(DArray * array, DArray_compare cmp)
{
    merge_sort(array, 0, array->end - 1, cmp);
    return 0;
}

int DArray_heapsort(DArray * array, DArray_compare cmp)
{
    heapsort(array->contents, DArray_count(array), sizeof(void *), cmp);
    return 0;
}

int DArray_qsort(DArray * array, DArray_compare cmp)
{
    quick_sort(array, 0, array->end -1, cmp);
    //Built in QSORT
    //qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
    return 0;
}

