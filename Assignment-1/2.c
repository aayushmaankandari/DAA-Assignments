#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, i;
    int fairHead = 0, biasedHead = 0;

    printf("Enter number of tosses: ");
    scanf("%d", &n);

    srand(time(NULL));

    // Fair Coin
    for(i = 0; i < n; i++)
    {
        if(rand() % 2 == 0)
            fairHead++;
    }

    // Biased Coin (70%% Head)
    for(i = 0; i < n; i++)
    {
        if(rand() % 100 < 70)
            biasedHead++;
    }

    printf("\n------ Result ------\n");

    printf("\nFair Coin:\n");
    printf("Heads = %d\n", fairHead);
    printf("Probability = %.4f\n", (float)fairHead / n);

    printf("\nBiased Coin:\n");
    printf("Heads = %d\n", biasedHead);
    printf("Probability = %.4f\n", (float)biasedHead / n);

    return 0;
}