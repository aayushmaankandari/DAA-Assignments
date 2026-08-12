#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

long bubbleSortOptimized(int arr[], int n)
{
    long comparisons = 0;
    int swapped;

    for(int i = 0; i < n - 1; i++)
    {
        swapped = 0;

        for(int j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if(arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }

        if(swapped == 0)
            break;
    }

    return comparisons;
}

long bubbleSortNormal(int arr[], int n)
{
    long comparisons = 0;

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if(arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }

    return comparisons;
}

void copyArray(int source[], int dest[], int n)
{
    for(int i = 0; i < n; i++)
        dest[i] = source[i];
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n], arr1[n], arr2[n];

    srand(time(NULL));

    printf("\nOriginal Array:\n");

    for(int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }

    copyArray(arr, arr1, n);
    copyArray(arr, arr2, n);

    long c1 = bubbleSortOptimized(arr1, n);
    long c2 = bubbleSortNormal(arr2, n);

    printf("\n\nSorted Array (Optimized):\n");
    printArray(arr1, n);

    printf("\nSorted Array (Normal):\n");
    printArray(arr2, n);

    printf("\nOptimized Bubble Sort Comparisons = %ld", c1);
    printf("\nNormal Bubble Sort Comparisons = %ld\n", c2);

    return 0;
}