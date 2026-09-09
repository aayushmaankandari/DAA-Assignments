#include <stdio.h>

int main() {
    int n, total, moves;

    printf("Enter number of rows: ");
    scanf("%d", &n);

    total = n * (n + 1) / 2;
    moves = (total + 2) / 3;   // ceil(total/3)

    printf("Total coins = %d\n", total);
    printf("Minimum moves = %d\n", moves);

    return 0;
}