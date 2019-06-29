#include <stdio.h>
#include <lcthw/algorithms/radix_sort.h>

void PrintArray(int * arr, int n)
{
    printf("Printing Array\r\n");
    for(int i = 0; i < n; i++)
    {
        printf("Element: %d, Value: %d\n", i, arr[i]);
    }
}

int GetMax(int *arr, int n)
{
    int max = arr[0];
    for(int i = 0; i< n; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
        }
    }
    printf("Max is %d \n", max);
    return max;
}

void CountSort2(int * arr, int n, int exp)
{
    int output[n]; // output array 
    int i, count[10] = {0}; 
  
    // Store count of occurrences in count[] 
    for (i = 0; i < n; i++) 
        count[ (arr[i]/exp)%10 ]++; 
  
    // Change count[i] so that count[i] now contains actual 
    //  position of this digit in output[] 
    for (i = 1; i < 10; i++) 
        count[i] += count[i - 1]; 
  
    // Build the output array 
    for (i = n - 1; i >= 0; i--) 
    { 
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
        count[ (arr[i]/exp)%10 ]--; 
    } 
  
    // Copy the output array to arr[], so that arr[] now 
    // contains sorted numbers according to current digit 
    for (i = 0; i < n; i++) 
        arr[i] = output[i]; 
}

void CountSort(int * arr, int n, int exp)
{
    int output[n]; // output array 
    int i, count[10] = {0}; 
    PrintArray(arr, n);
    
    // Store count of occurrences in count[] 
    for (i = 0; i < n; i++) 
        count[ (arr[i]/exp)%10 ]++; 


    for(i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }
    
    // Build the output array 
    for (i = n - 1; i >= 0; i--) 
    { 
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
        count[ (arr[i]/exp)%10 ]--; 
    } 
    PrintArray(count, 10);
    PrintArray(output, n);
    // Copy the output array to arr[], so that arr[] now 
    // contains sorted numbers according to current digit 
    for (i = 0; i < n; i++) 
        arr[i] = output[i]; 
    
}

void radsort(int *arr, int n)
{
    printf("Sorting \n");
    int max = GetMax(arr, n);

    for (int exp = 1; max/exp > 0; exp *= 10) 
        CountSort(arr, n, exp); 
};