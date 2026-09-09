#include <stdio.h>
#include <limits.h>

long long hanoi3[30];
long long dp[30];
int best[30];

void solve3(int n, char src, char dest, char aux) {
    if (n == 0)
        return;

    solve3(n - 1, src, aux, dest);

    printf("Move disk %d from %c to %c\n", n, src, dest);

    solve3(n - 1, aux, dest, src);
}

void solve4(int n, char src, char dest, char aux1, char aux2) {
    if (n == 0)
        return;

    int k = best[n];

    solve4(n - k, src, aux1, dest, aux2);

    solve3(k, src, dest, aux2);

    solve4(n - k, aux1, dest, src, aux2);
}

int main() {
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    hanoi3[0] = 0;

    for (int i = 1; i <= n; i++)
        hanoi3[i] = 2 * hanoi3[i - 1] + 1;

    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        dp[i] = LLONG_MAX;

        for (int k = 1; k <= i; k++) {
            long long moves = 2 * dp[i - k] + hanoi3[k];

            if (moves < dp[i]) {
                dp[i] = moves;
                best[i] = k;
            }
        }
    }

    printf("Minimum moves = %lld\n", dp[n]);

    printf("\nSequence of moves:\n");
    solve4(n, 'A', 'D', 'B', 'C');

    return 0;
}