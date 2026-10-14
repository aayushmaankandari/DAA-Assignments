#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int root;
    int value;
} Item;

int *parent, *size;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
        return;

    if (size[a] < size[b]) {
        int temp = a;
        a = b;
        b = temp;
    }

    parent[b] = a;
    size[a] += size[b];
}

int compare(const void *a, const void *b) {
    const Item *x = a;
    const Item *y = b;

    if (x->root != y->root)
        return (x->root > y->root) - (x->root < y->root);

    return (x->value > y->value) - (x->value < y->value);
}

int main(void) {
    int n, m;

    printf("Enter n and m: ");
    if (scanf("%d %d", &n, &m) != 2 ||
        n <= 0 || m < 0)
        return 1;

    int *A = malloc(n * sizeof(int));
    int *answer = malloc(n * sizeof(int));
    parent = malloc(n * sizeof(int));
    size = malloc(n * sizeof(int));

    Item *positions = malloc(n * sizeof(Item));
    Item *values = malloc(n * sizeof(Item));

    if (!A || !answer || !parent || !size ||
        !positions || !values)
        return 1;

    printf("Enter array elements:\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &A[i]) != 1)
            return 1;

        parent[i] = i;
        size[i] = 1;
    }

    printf("Enter allowed swap pairs (u v), 0-based:\n");
    for (int i = 0; i < m; i++) {
        int u, v;

        if (scanf("%d %d", &u, &v) != 2 ||
            u < 0 || u >= n || v < 0 || v >= n)
            return 1;

        unite(u, v);
    }

    for (int i = 0; i < n; i++) {
        int root = find(i);

        positions[i].root = root;
        positions[i].value = i;

        values[i].root = root;
        values[i].value = A[i];
    }

    qsort(positions, n, sizeof(Item), compare);
    qsort(values, n, sizeof(Item), compare);

    for (int i = 0; i < n; i++)
        answer[positions[i].value] = values[i].value;

    printf("Lexicographically smallest permutation:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", answer[i]);

    printf("\n");

    free(A);
    free(answer);
    free(parent);
    free(size);
    free(positions);
    free(values);

    return 0;
}