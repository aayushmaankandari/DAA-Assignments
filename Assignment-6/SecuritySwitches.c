#include <stdio.h>

int main() {
    int n;
    unsigned long long moves = 0;
    unsigned long long power = 1;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    power = 1ULL << (n + 1);
    moves = power / 3;

    printf("Minimum number of moves = %llu\n", moves);

    return 0;
}