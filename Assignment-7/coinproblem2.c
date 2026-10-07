#include <stdio.h>

int countWays(int coins[], int n, int V) {
    int dp[V + 1];

    // Initialize dp array
    for (int i = 0; i <= V; i++) {
        dp[i] = 0;
    }
    dp[0] = 1; // Base case: one way to make 0

    // For each coin, update ways
    for (int j = 0; j < n; j++) {
        for (int i = coins[j]; i <= V; i++) {
            dp[i] += dp[i - coins[j]];
        }
    }

    return dp[V];
}

int main() {
    int coins[] = {1, 2, 5}; // coin denominations
    int n = sizeof(coins) / sizeof(coins[0]);
    int V = 5; // target amount

    int result = countWays(coins, n, V);
    printf("Total number of ways to make %d = %d\n", V, result);

    return 0;
}
