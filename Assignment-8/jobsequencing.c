#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char id;
    int deadline, profit;
} Job;

int cmp(const void *a, const void *b) {
    return ((Job*)b)->profit - ((Job*)a)->profit;
}

void jobSequencing(Job jobs[], int n) {
    qsort(jobs, n, sizeof(Job), cmp);
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) if (jobs[i].deadline > maxDeadline) maxDeadline = jobs[i].deadline;

    char result[maxDeadline];
    int slot[maxDeadline];
    for (int i = 0; i < maxDeadline; i++) slot[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (slot[j] == -1) {
                slot[j] = i;
                break;
            }
        }
    }

    printf("Scheduled jobs: ");
    for (int i = 0; i < maxDeadline; i++) {
        if (slot[i] != -1) printf("%c ", jobs[slot[i]].id);
    }
    printf("\n");
}

int main() {
    Job jobs[] = {{'a',2,100},{'b',1,19},{'c',2,27},{'d',1,25},{'e',3,15}};
    int n = 5;
    jobSequencing(jobs, n);
    return 0;
}
