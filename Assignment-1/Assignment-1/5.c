#include <stdio.h>

int findPartitionPoint(int arr[], int n)
{
    int low = 0;
    int high = n - 1;
    int ans = -1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == 1)
        {
            ans = mid;
            high = mid - 1;   // Search left part
        }
        else
        {
            low = mid + 1;    // Search right part
        }
    }

    return ans;
}

int main()
{
    int n;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements (0s followed by 1s):\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int index = findPartitionPoint(arr, n);

    if (index == -1)
        printf("No partition point found (No 1 present).\n");
    else
        printf("Partition Point (First 1) = Index %d\n", index);

    return 0;
}