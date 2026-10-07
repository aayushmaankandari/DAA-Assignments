#include <stdio.h>
#include <stdlib.h>

int huTucker(int w[], int n) {
    int totalCost = 0;
    int active[n];
    for (int i = 0; i < n; i++) active[i] = 1;

    while (1) {
        int minSum = 1e9, idx = -1;
        for (int i = 0; i < n - 1; i++) {
            if (active[i] && active[i+1] && w[i] + w[i+1] < minSum) {
                minSum = w[i] + w[i+1];
                idx = i;
            }
        }
        if (idx == -1) break;
        totalCost += minSum;
        w[idx] = minSum;
        active[idx+1] = 0;
    }
    return totalCost;
}

int main() {
    int w[] = {5, 9, 12, 13, 16, 45};
    int n = 6;
    printf("Hu-Tucker total cost: %d\n", huTucker(w, n));
    return 0;
}
