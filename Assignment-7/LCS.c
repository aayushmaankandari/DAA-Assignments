#include <stdio.h>
#include <string.h>

// Function to find LCS length
int LCS(char X[], char Y[])
{
    int m = strlen(X);
    int n = strlen(Y);

    int dp[m + 1][n + 1];

    // Fill dp table
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else if (dp[i - 1][j] > dp[i][j - 1])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = dp[i][j - 1];
        }
    }

    return dp[m][n]; // ✅ return after table is fully filled
}

int main()
{
    char X[] = "ABCBDAB";
    char Y[] = "BDCAB";

    int result = LCS(X, Y);
    printf("Length of LCS = %d\n", result);

    return 0;
}
