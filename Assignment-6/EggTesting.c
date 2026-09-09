#include <stdio.h>
#include <limits.h>

int main() {
    int eggs, floors;

    printf("Enter number of eggs: ");
    scanf("%d", &eggs);

    printf("Enter number of floors: ");
    scanf("%d", &floors);

    int dp[eggs + 1][floors + 1];

    // 0 floors = 0 attempts
    for (int e = 1; e <= eggs; e++)
        dp[e][0] = 0;

    // 1 floor = 1 attempt
    for (int e = 1; e <= eggs; e++)
        dp[e][1] = 1;

    // With one egg, we must test every floor
    for (int f = 1; f <= floors; f++)
        dp[1][f] = f;

    for (int e = 2; e <= eggs; e++) {
        for (int f = 2; f <= floors; f++) {
            dp[e][f] = INT_MAX;

            for (int x = 1; x <= f; x++) {
                int attempts = 1 +
                    (dp[e - 1][x - 1] > dp[e][f - x]
                    ? dp[e - 1][x - 1]
                    : dp[e][f - x]);

                if (attempts < dp[e][f])
                    dp[e][f] = attempts;
            }
        }
    }

    printf("Minimum number of trials = %d\n", dp[eggs][floors]);

    return 0;
}