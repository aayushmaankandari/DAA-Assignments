#include <stdio.h>

void findMinMax(int arr[], int l, int r, int *min, int *max) {
    if (l == r) { *min = *max = arr[l]; return; }
    if (r == l + 1) {
        if (arr[l] < arr[r]) { *min = arr[l]; *max = arr[r]; }
        else { *min = arr[r]; *max = arr[l]; }
        return;
    }
    int mid = (l + r) / 2;
    int min1, max1, min2, max2;
    findMinMax(arr, l, mid, &min1, &max1);
    findMinMax(arr, mid + 1, r, &min2, &max2);
    *min = (min1 < min2) ? min1 : min2;
    *max = (max1 > max2) ? max1 : max2;
}

int main() {
    int arr[] = {6,5,9,2,4};
    int n = sizeof(arr)/sizeof(arr[0]);
    int min, max;
    findMinMax(arr, 0, n-1, &min, &max);
    printf("Min = %d, Max = %d\n", min, max);
    return 0;
}
