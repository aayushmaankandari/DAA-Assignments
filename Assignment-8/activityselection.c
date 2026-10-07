#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start, end;
} Activity;

int cmp(const void *a, const void *b) {
    return ((Activity*)a)->end - ((Activity*)b)->end;
}

void activitySelection(Activity arr[], int n) {
    qsort(arr, n, sizeof(Activity), cmp);
    int lastEnd = -1;
    printf("Selected activities:\n");
    for (int i = 0; i < n; i++) {
        if (arr[i].start >= lastEnd) {
            printf("[%d,%d] ", arr[i].start, arr[i].end);
            lastEnd = arr[i].end;
        }
    }
    printf("\n");
}

int main() {
    Activity arr[] = {{1,2},{3,4},{0,6},{5,7},{8,9},{5,9}};
    int n = 6;
    activitySelection(arr, n);
    return 0;
}
