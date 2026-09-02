#include <stdio.h>

// Function to reverse a subarray from index i to j
void reverse(int arr[], int i, int j) {
    while (i < j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
}

// Function to sort array using reversal procedure
void sortByReversal(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Find index of minimum element from i to n-1
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        // Reverse subarray from i to minIndex
        reverse(arr, i, minIndex);
    }
}

// Driver code
int main() {
    int arr[] = {4, 1, 3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    sortByReversal(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
