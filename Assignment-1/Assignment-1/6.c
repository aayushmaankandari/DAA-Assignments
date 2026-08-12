#include <stdio.h>

int elementUnique(int arr[], int n)
{
    int i, j;

    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(arr[i] == arr[j])
            {
                return 0;   // Duplicate found
            }
        }
    }

    return 1;   // All elements are unique
}

int main()
{
    int n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter array elements:\n");

    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    if(elementUnique(arr, n))
        printf("\nAll elements are unique.\n");
    else
        printf("\nDuplicate elements found.\n");

    return 0;
}