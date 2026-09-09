#include <stdio.h>

int main() {
    int n;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n == 1) {
        printf("Shot at position 1\n");
        printf("Target is guaranteed to be hit.\n");
        return 0;
    }

    printf("\nShooting sequence:\n");

    if (n % 2 == 0) {
        // Left to right
        for (int i = 2; i <= n - 1; i++)
            printf("%d ", i);

        // Right to left
        for (int i = n - 1; i >= 2; i--)
            printf("%d ", i);
    }
    else {
        // Repeat internal positions twice
        for (int j = 0; j < 2; j++) {
            for (int i = 2; i <= n - 1; i++)
                printf("%d ", i);
        }
    }

    printf("\nTarget is guaranteed to be hit.\n");

    return 0;
}