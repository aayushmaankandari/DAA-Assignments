#include <stdio.h>
#include <limits.h>

void printParenthesis(int i, int j, int n, int split[n][n]) {
    if (i == j) {
        printf("A%d", i);
        return;
    }

    printf("(");

    printParenthesis(i, split[i][j], n, split);
    printParenthesis(split[i][j] + 1, j, n, split);

    printf(")");
}

int main() {
    int n;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int p[n + 1];

    printf("Enter dimensions:\n");
    for (int i = 0; i <= n; i++)
        scanf("%d", &p[i]);

    int dp[n + 1][n + 1];
    int split[n + 1][n + 1];

    for (int i = 1; i <= n; i++)
        dp[i][i] = 0;

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;

            dp[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int cost = dp[i][k]
                         + dp[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum scalar multiplications = %d\n",
           dp[1][n]);

    printf("Optimal parenthesization = ");
    printParenthesis(1, n, n + 1, split);
    printf("\n");

    return 0;
}