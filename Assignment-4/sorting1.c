#include <stdio.h>

#define RED 0
#define BLUE 1
#define YELLOW 2

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void colorSort(int arr[], int n) {
    int low = 0, mid = 0, high = n - 1;

    while (mid <= high) {
        if (arr[mid] == RED) {
            swap(&arr[low], &arr[mid]);
            low++;
            mid++;
        }
        else if (arr[mid] == BLUE) {
            mid++;
        }
        else { // arr[mid] == YELLOW
            swap(&arr[mid], &arr[high]);
            high--;
        }
    }
}

int main() {
    int arr[] = {YELLOW, RED, BLUE, RED, YELLOW, BLUE, RED};
    int n = sizeof(arr) / sizeof(arr[0]);

    colorSort(arr, n);

    for (int i = 0; i < n; i++) {
        if (arr[i] == RED) printf("RED ");
        else if (arr[i] == BLUE) printf("BLUE ");
        else printf("YELLOW ");
    }
    printf("\n");

    return 0;
}
