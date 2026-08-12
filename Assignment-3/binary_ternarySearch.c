#include <stdio.h>

int binarySearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        int mid = (l + r) / 2;
        if (arr[mid] == x) return mid;
        else if (arr[mid] < x) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

int ternarySearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;
        if (arr[mid1] == x) return mid1;
        if (arr[mid2] == x) return mid2;
        if (x < arr[mid1]) r = mid1 - 1;
        else if (x > arr[mid2]) l = mid2 + 1;
        else { l = mid1 + 1; r = mid2 - 1; }
    }
    return -1;
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr)/sizeof(arr[0]);
    int x = 3;
    printf("Binary Search index: %d\n", binarySearch(arr, 0, n-1, x));
    printf("Ternary Search index: %d\n", ternarySearch(arr, 0, n-1, x));
    return 0;
}
