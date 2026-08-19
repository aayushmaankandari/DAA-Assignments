#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    // Example intervals
    int start[] = {1, 2, 9, 5, 5};
    int end[]   = {4, 5, 12, 9, 12};
    int n = sizeof(start) / sizeof(start[0]);

    // Sort start and end arrays
    qsort(start, n, sizeof(int), cmp);
    qsort(end, n, sizeof(int), cmp);

    int i = 0, j = 0;
    int current = 0, maxCount = 0, point = 0;

    // Traverse both arrays
    while (i < n && j < n) {
        if (start[i] <= end[j]) {
            current++;  // new interval starts
            if (current > maxCount) {
                maxCount = current;
                point = start[i];  // record the point
            }
            i++;
        } else {
            current--;  // interval ends
            j++;
        }
    }

    printf("Point with maximum overlap: %d\n", point);
    printf("Maximum number of overlapping intervals: %d\n", maxCount);

    return 0;
}
