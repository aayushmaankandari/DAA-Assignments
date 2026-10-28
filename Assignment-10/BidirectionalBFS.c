#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 10
#define INF 1000000000

int compareWords(const void *a, const void *b)
{
    return strcmp((const char *)a, (const char *)b);
}

int findWord(char (*words)[MAXL + 1], int N, const char *target)
{
    int low = 0, high = N - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int cmp = strcmp(words[mid], target);

        if (cmp == 0)
            return mid;

        if (cmp < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

/*
   Expands one complete BFS layer.

   Returns the shortest path length found where the two
   searches meet, or INF if they have not met yet.
*/
int expandLayer(
    char (*words)[MAXL + 1], int N,
    int *frontier, int frontierCount,
    int *nextFrontier, int *nextCount,
    int *distThis, int *distOther, int L)
{
    int best = INF;
    *nextCount = 0;

    for (int i = 0; i < frontierCount; i++)
    {
        int u = frontier[i];

        if (distOther[u] != -1 &&
            distThis[u] + distOther[u] < best)
            best = distThis[u] + distOther[u];

        char temp[MAXL + 1];
        strcpy(temp, words[u]);

        for (int pos = 0; pos < L; pos++)
        {
            char original = temp[pos];

            for (char ch = 'a'; ch <= 'z'; ch++)
            {
                if (ch == original)
                    continue;

                temp[pos] = ch;
                int v = findWord(words, N, temp);

                if (v == -1)
                    continue;

                if (distThis[v] == -1)
                {
                    distThis[v] = distThis[u] + 1;
                    nextFrontier[(*nextCount)++] = v;
                }

                if (distOther[v] != -1)
                {
                    int candidate = distThis[v] + distOther[v];

                    if (candidate < best)
                        best = candidate;
                }
            }

            temp[pos] = original;
        }
    }

    return best;
}

int main(void)
{
    int N;

    /*
       Input:
       N
       N dictionary words
       A B

       All words have equal length, at most 10.
    */

    if (scanf("%d", &N) != 1 || N <= 0)
    {
        fprintf(stderr, "Invalid dictionary size\n");
        return 1;
    }

    char (*words)[MAXL + 1] =
        malloc((N + 1) * sizeof(*words));

    if (!words)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < N; i++)
    {
        if (scanf("%10s", words[i]) != 1)
        {
            fprintf(stderr, "Invalid dictionary input\n");
            free(words);
            return 1;
        }
    }

    char A[MAXL + 1], B[MAXL + 1];

    if (scanf("%10s %10s", A, B) != 2)
    {
        fprintf(stderr, "Invalid start or target word\n");
        free(words);
        return 1;
    }

    int L = (int)strlen(A);

    if (L == 0 || L > MAXL || strlen(B) != (size_t)L)
    {
        printf("-1\n");
        free(words);
        return 0;
    }

    for (int i = 0; i < N; i++)
    {
        if (strlen(words[i]) != (size_t)L)
        {
            fprintf(stderr, "All words must have equal length\n");
            free(words);
            return 1;
        }
    }

    /* The target must belong to the dictionary. */
    qsort(words, N, sizeof(*words), compareWords);

    if (findWord(words, N, B) == -1)
    {
        printf("-1\n");
        free(words);
        return 0;
    }

    if (strcmp(A, B) == 0)
    {
        printf("0\n");
        free(words);
        return 0;
    }

    /*
       Add A if it is not already in the dictionary.
       This permits A to be an external starting word.
    */
    if (findWord(words, N, A) == -1)
    {
        strcpy(words[N], A);
        N++;

        qsort(words, N, sizeof(*words), compareWords);
    }

    int start = findWord(words, N, A);
    int target = findWord(words, N, B);

    int *distA = malloc(N * sizeof(int));
    int *distB = malloc(N * sizeof(int));

    int *frontA = malloc(N * sizeof(int));
    int *frontB = malloc(N * sizeof(int));

    int *nextA = malloc(N * sizeof(int));
    int *nextB = malloc(N * sizeof(int));

    if (!distA || !distB || !frontA || !frontB ||
        !nextA || !nextB)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(words);
        free(distA);
        free(distB);
        free(frontA);
        free(frontB);
        free(nextA);
        free(nextB);
        return 1;
    }

    for (int i = 0; i < N; i++)
    {
        distA[i] = -1;
        distB[i] = -1;
    }

    /* Initialize BFS from both ends. */
    distA[start] = 0;
    distB[target] = 0;

    frontA[0] = start;
    frontB[0] = target;

    int countA = 1;
    int countB = 1;
    int answer = INF;

    while (countA > 0 && countB > 0)
    {
        if (countA <= countB)
        {
            int nextCount;

            answer = expandLayer(
                words, N, frontA, countA, nextA, &nextCount,
                distA, distB, L);

            int *temp = frontA;
            frontA = nextA;
            nextA = temp;
            countA = nextCount;
        }
        else
        {
            int nextCount;

            answer = expandLayer(
                words, N, frontB, countB, nextB, &nextCount,
                distB, distA, L);

            int *temp = frontB;
            frontB = nextB;
            nextB = temp;
            countB = nextCount;
        }

        if (answer != INF)
            break;
    }

    printf("%d\n", answer == INF ? -1 : answer);

    free(words);
    free(distA);
    free(distB);
    free(frontA);
    free(frontB);
    free(nextA);
    free(nextB);

    return 0;
}