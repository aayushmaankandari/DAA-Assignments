#include <stdio.h>

// Recursive function to find defective coin
int findDefective(int coins[], int l, int r, int normalWeight) {
    if (l == r) return l; // only one coin left

    int n = r - l + 1;
    int mid = l + n/2 - 1;   // midpoint for splitting

    int leftWeight = 0, rightWeight = 0;
    int size = n/2;          // equal group size

    // sum equal-sized groups
    for (int i = 0; i < size; i++) {
        leftWeight += coins[l + i];
        rightWeight += coins[mid + 1 + i];
    }

    if (leftWeight < rightWeight) {
        return findDefective(coins, l, l + size - 1, normalWeight);
    } else if (rightWeight < leftWeight) {
        return findDefective(coins, mid + 1, mid + size, normalWeight);
    } else {
        // groups equal → defective must be in leftover coin(s)
        if (n % 2 == 1) return r; // odd count → last coin is leftover
        else return -1;           // no defective found
    }
}

int main() {
    int coins[] = {10, 10, 9, 10, 10}; // defective at index 2
    int n = sizeof(coins)/sizeof(coins[0]);
    int normalWeight = 10; // expected weight of normal coin

    int idx = findDefective(coins, 0, n-1, normalWeight);
    if (idx != -1) printf("Defective coin at index %d (weight=%d)\n", idx, coins[idx]);
    else printf("No defective coin found\n");
    return 0;
}
