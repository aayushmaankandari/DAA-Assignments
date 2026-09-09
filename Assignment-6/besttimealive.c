#include <stdio.h>

int main() {
    int n;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    int birth[n], death[n];

    for (int i = 0; i < n; i++) {
        printf("Enter birth and death year of scientist %d: ",
               i + 1);
        scanf("%d %d", &birth[i], &death[i]);
    }

    int bestYear = birth[0];
    int maxAlive = 0;

    for (int year = birth[0]; year <= death[0]; year++) {
        int alive = 0;

        for (int i = 0; i < n; i++) {
            if (birth[i] <= year && year <= death[i])
                alive++;
        }

        if (alive > maxAlive) {
            maxAlive = alive;
            bestYear = year;
        }
    }

    // Check remaining years
    int minYear = birth[0], maxYear = death[0];

    for (int i = 1; i < n; i++) {
        if (birth[i] < minYear)
            minYear = birth[i];

        if (death[i] > maxYear)
            maxYear = death[i];
    }

    maxAlive = 0;

    for (int year = minYear; year <= maxYear; year++) {
        int alive = 0;

        for (int i = 0; i < n; i++) {
            if (birth[i] <= year && year <= death[i])
                alive++;
        }

        if (alive > maxAlive) {
            maxAlive = alive;
            bestYear = year;
        }
    }

    printf("\nBest year to be alive = %d\n", bestYear);
    printf("Maximum scientists alive = %d\n", maxAlive);

    return 0;
}