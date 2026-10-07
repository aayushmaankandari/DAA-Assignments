#include <stdio.h>

// Function to find LIS length
int LIS(int arr[], int n) {
    int dp[n];
    int maxLen = 1;

    // Initialize LIS values for all indexes
    for (int i = 0; i < n; i++) {
        dp[i] = 1; // each element is LIS of length 1
    }

    // Build LIS using DP
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > maxLen) {
            maxLen = dp[i];
        }
    }

    return maxLen;
}

int main() {
    int arr[] = {10, 22, 9, 33, 21, 50, 41, 60};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = LIS(arr, n);
    printf("Length of LIS = %d\n", result);

    return 0;
}
