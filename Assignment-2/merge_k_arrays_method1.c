#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int a[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = a[l + i];

    for (int i = 0; i < n2; i++)
        R[i] = a[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (i < n1)
        a[k++] = L[i++];

    while (j < n2)
        a[k++] = R[j++];

    free(L);
    free(R);
}

int main()
{
    srand(time(NULL));

    int n = 100000;

    printf("k\tTime(ms)\n");

    for (int k = 2; k <= 10; k++)
    {
        int total = n * k;

        int *arr = (int *)malloc(total * sizeof(int));

        if (arr == NULL)
        {
            printf("Memory allocation failed!\n");
            return 1;
        }

        for (int i = 0; i < total; i++)
            arr[i] = rand();

        clock_t start = clock();

        // Repeat multiple times for accurate timing
        for (int repeat = 0; repeat < 100; repeat++)
        {
            for (int i = 1; i < k; i++)
            {
                merge(arr, 0, i * n - 1, (i + 1) * n - 1);
            }
        }

        clock_t end = clock();

        double time_taken = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;

        printf("%d\t%.4f\n", k, time_taken);

        free(arr);
    }

    return 0;
}