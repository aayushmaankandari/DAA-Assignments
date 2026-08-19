#include <stdio.h>
#include <stdlib.h>

// Interval structure
typedef struct {
    int start;
    int end;
} Interval;

// Comparison function for qsort (sort by start time)
int cmp(const void *a, const void *b) {
    Interval *i1 = (Interval*)a;
    Interval *i2 = (Interval*)b;
    return i1->start - i2->start;
}

void mergeIntervals(Interval arr[], int n) {
    // Sort intervals by start time
    qsort(arr, n, sizeof(Interval), cmp);

    int index = 0; // index of last merged interval

    for (int i = 1; i < n; i++) {
        if (arr[index].end >= arr[i].start) {
            // Overlapping → merge
            if (arr[index].end < arr[i].end)
                arr[index].end = arr[i].end;
        } else {
            // No overlap → move to next
            index++;
            arr[index] = arr[i];
        }
    }

    // Print merged intervals
    printf("Merged intervals:\n");
    for (int i = 0; i <= index; i++) {
        printf("[%d, %d]\n", arr[i].start, arr[i].end);
    }
}

int main() {
    Interval arr[] = {{1,3}, {2,6}, {8,10}, {15,18}, {17,20}};
    int n = sizeof(arr) / sizeof(arr[0]);

    mergeIntervals(arr, n);

    return 0;
}
