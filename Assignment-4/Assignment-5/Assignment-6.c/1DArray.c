#include <stdio.h>
#include <math.h>

// ---------- Utility ----------
void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

// ---------- (i) Maximum element — O(n) ----------
int findMax(int arr[], int n) {  
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];
    return max;
}

// ---------- (ii) First & second largest — O(n) ----------
void findTwoLargest(int arr[], int n, int *first, int *second) {
    *first = *second = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > *first) {
            *second = *first;
            *first = arr[i];
        } else if (arr[i] > *second && arr[i] != *first)
            *second = arr[i];
    }
}

// ---------- (iii) Mean — O(n) ----------
double findMean(int arr[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum / n;
}

// ---------- (iv) Median (Quickselect) — average O(n) ----------
int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) { swap(&arr[i], &arr[j]); i++; }
    }
    swap(&arr[i], &arr[right]);
    return i;
}

int quickselect(int arr[], int left, int right, int k) {
    if (left <= right) {
        int p = partition(arr, left, right);
        if (p == k) return arr[p];
        else if (p > k) return quickselect(arr, left, p - 1, k);
        else return quickselect(arr, p + 1, right, k);
    }
    return -1;
}

double findMedian(int arr[], int n) {
    int copy1[n], copy2[n];
    for (int i = 0; i < n; i++) { copy1[i] = arr[i]; copy2[i] = arr[i]; }
    if (n % 2 == 1)
        return quickselect(copy1, 0, n - 1, n / 2);
    else {
        int a = quickselect(copy1, 0, n - 1, n / 2 - 1);
        int b = quickselect(copy2, 0, n - 1, n / 2);
        return (a + b) / 2.0;
    }
}

// ---------- (v) Standard deviation — O(n) ----------
double findStdDev(int arr[], int n) {
    double mean = findMean(arr, n), sumSq = 0;
    for (int i = 0; i < n; i++)
        sumSq += (arr[i] - mean) * (arr[i] - mean);
    return sqrt(sumSq / n);
}

// ---------- (vi) Mode — O(n²) ----------
int findMode(int arr[], int n) {
    int maxCount = 0, mode = arr[0];
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++)
            if (arr[j] == arr[i]) count++;
        if (count > maxCount) { maxCount = count; mode = arr[i]; }
    }
    return mode;
}

// ---------- (vii) Remove duplicates — O(n²) ----------
int removeDuplicates(int arr[], int n) {
    int temp[n], k = 0;
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < k; j++)
            if (arr[i] == temp[j]) { found = 1; break; }
        if (!found) temp[k++] = arr[i];
    }
    for (int i = 0; i < k; i++) arr[i] = temp[i];
    return k;
}

// ---------- (viii) Reverse array — O(n) ----------
void reverseArray(int arr[], int n) {
    for (int i = 0; i < n / 2; i++)
        swap(&arr[i], &arr[n - i - 1]);
}

// ---------- (ix) Partition by pivot — O(n) ----------
void partitionByPivot(int arr[], int n, int pivot) {
    int left = 0, right = n - 1;
    while (left <= right) {
        while (arr[left] < pivot) left++;
        while (arr[right] >= pivot) right--;
        if (left < right) swap(&arr[left], &arr[right]);
    }
}

// ---------- MAIN ----------
int main() {
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Max: %d\n", findMax(arr, n));

    int first, second;
    findTwoLargest(arr, n, &first, &second);
    printf("First: %d, Second: %d\n", first, second);

    printf("Mean: %.2f\n", findMean(arr, n));
    printf("Median: %.2f\n", findMedian(arr, n));
    printf("Std Dev: %.2f\n", findStdDev(arr, n));
    printf("Mode: %d\n", findMode(arr, n));

    int newN = removeDuplicates(arr, n);
    printf("After removing duplicates: ");
    for (int i = 0; i < newN; i++) printf("%d ", arr[i]);
    printf("\n");

    reverseArray(arr, newN);
    printf("Reversed array: ");
    for (int i = 0; i < newN; i++) printf("%d ", arr[i]);
    printf("\n");

    int pivot = 7;
    partitionByPivot(arr, newN, pivot);
    printf("Partitioned around pivot %d: ", pivot);
    for (int i = 0; i < newN; i++) printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
