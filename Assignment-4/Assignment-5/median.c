#include <stdio.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function (like in Quicksort)
int partition(int arr[], int left, int right) {
    int pivot = arr[right];   // choose last element as pivot
    int i = left;             // index for smaller elements

    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[right]); // place pivot in correct position
    return i;
}

// Quickselect function to find k-th smallest element
int quickselect(int arr[], int left, int right, int k) {
    if (left <= right) {
        int pivotIndex = partition(arr, left, right);

        if (pivotIndex == k) return arr[pivotIndex];       // found k-th element
        else if (pivotIndex > k) return quickselect(arr, left, pivotIndex - 1, k);
        else return quickselect(arr, pivotIndex + 1, right, k);
    }
    return -1; // error case
}

// Function to find median
double findMedian(int arr[], int n) {
    if (n % 2 == 1) {
        // Odd length → middle element
        return quickselect(arr, 0, n - 1, n / 2);
    } else {
        // Even length → average of two middle elements
        int leftMid = quickselect(arr, 0, n - 1, (n / 2) - 1);
        int rightMid = quickselect(arr, 0, n - 1, n / 2);
        return (leftMid + rightMid) / 2.0;
    }
}

// Driver code
int main() {
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]);

    double median = findMedian(arr, n);
    printf("Median = %.2f\n", median);

    return 0;
}
