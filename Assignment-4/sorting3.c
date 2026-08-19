#include <stdio.h>

// Recursive function to check k-sum
int kSum(int arr[], int n, int k, int target, int index) {
    // Base cases
    if (k == 0 && target == 0) return 1;   // found valid subset
    if (k == 0 || index == n) return 0;    // no more elements

    // Choice 1: include arr[index]
    if (kSum(arr, n, k - 1, target - arr[index], index + 1))
        return 1;

    // Choice 2: exclude arr[index]
    return kSum(arr, n, k, target, index + 1);
}

int main() {
    int arr[] = {2, 4, 6, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;        // subset size
    int target = 18;  // target sum

    if (kSum(arr, n, k, target, 0))
        printf("Subset of size %d with sum %d exists.\n", k, target);
    else
        printf("No subset of size %d with sum %d found.\n", k, target);

    return 0;
}
