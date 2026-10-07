#include <stdio.h>
#include <limits.h>
int minCoins(int coins[], int n, int V)
{
    int dp[V + 1];
    for (int i = 0; i <= V; i++)
    {
        dp[i] = INT_MAX;
    }
    dp[0] = 0;
    for (int i = 0; i <= V; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX)
            {
                if (dp[i - coins[j]] + 1 < dp[i])
                {
                    dp[i] = dp[i - coins[j]] + 1;
                }
                else
                {
                    dp[i] = dp[i];
                }
            }
        }
    }
    return (dp[V] == INT_MAX) ? -1 : dp[V];
}

int main()
{
    int coins[] = {1,2,3,4,5,6,7,8,9, 10};
    int n = sizeof(coins) / sizeof(coins[0]);
    int V = 823;
    int result = minCoins(coins, n, V);
    if (result == -1)
    {
        printf("Not possible to make amount %d \n", V);
    }
    else
    {
        printf("Minimum coins needed for %d = %d \n", V, result);
    }

    return 0;
}