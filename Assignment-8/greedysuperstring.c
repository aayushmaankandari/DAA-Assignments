#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Function to find maximum overlap between two strings
int overlap(char *a, char *b, char *res) {
    int max = 0;
    int lenA = strlen(a), lenB = strlen(b);

    for (int i = 1; i <= lenA && i <= lenB; i++) {
        if (strncmp(a + lenA - i, b, i) == 0) {
            max = i;
        }
    }

    strcpy(res, a);
    strcat(res, b + max);
    return max;
}

// Greedy superstring construction
char* greedySuperstring(char *arr[], int n) {
    while (n > 1) {
        int maxOverlap = -1;
        int l, r;
        char temp[MAX];

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                char merged[MAX];
                int ov = overlap(arr[i], arr[j], merged);
                if (ov > maxOverlap) {
                    maxOverlap = ov;
                    l = i; r = j;
                    strcpy(temp, merged);
                }
            }
        }

        strcpy(arr[l], temp);
        for (int i = r; i < n - 1; i++)
            arr[i] = arr[i + 1];
        n--;
    }
    return arr[0];
}

int main() {
    char *arr[] = {"catgc", "ctaagt", "gcta", "ttca", "atgcatc"};
    int n = 5;

    char *result = greedySuperstring(arr, n);
    printf("Greedy Superstring: %s\n", result);

    return 0;
}
