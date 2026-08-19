#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Binary search function
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) return 1;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1; // if(arr[mid]>key)
    }
    return 0;
}

int main() {
    int A[] = {1, 4, 7, 10};
    int B[] = {2, 5, 8, 11};
    int n = sizeof(A) / sizeof(A[0]);
    int m = sizeof(B) / sizeof(B[0]);
    int x = 15;  // target sum

    // Sort array B
    qsort(B, m, sizeof(int), cmp);

    int found = 0;
    for (int i = 0; i < n; i++) {
        int complement = x - A[i];
        if (binarySearch(B, m, complement)) {
            printf("Pair found: (%d, %d)\n", A[i], complement);
            found = 1;
            // break;  // stop after finding one pair
        }
    }

    if (!found) {
        printf("No pair found with sum %d\n", x);
    }

    return 0;
}
