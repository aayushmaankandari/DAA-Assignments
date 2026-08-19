#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    // Example: 5 guests
    int entry[] = {1, 2, 9, 5, 5};
    int exit[]  = {4, 5, 12, 9, 12};
    int n = sizeof(entry) / sizeof(entry[0]);

    // Sort both arrays
    qsort(entry, n, sizeof(int), cmp);
    qsort(exit, n, sizeof(int), cmp);

    int i = 0, j = 0;
    int current = 0, maxGuests = 0;

    // Traverse both arrays
    while (i < n && j < n) {
        if (entry[i] <= exit[j]) {
            current++;          // new guest arrives
            if (current > maxGuests)
                maxGuests = current;
            i++;
        } else {
            current--;          // guest leaves
            j++;
        }
    }

    printf("Maximum guests present at any time: %d\n", maxGuests);

    return 0;
}
