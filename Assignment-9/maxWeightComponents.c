#include <stdio.h>
#include <stdlib.h>

int *parent, *size;
long long *sum;
int n, K;

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
    sum[a] += sum[b];
}

long long getMax(void) {
    long long best = 0;

    for (int i = 0; i < n; i++) {
        if (find(i) == i && size[i] <= K && sum[i] > best)
            best = sum[i];
    }

    return best;
}

int main(void) {
    int m;

    printf("Enter n, m and maximum component size K: ");
    if (scanf("%d %d %d", &n, &m, &K) != 3 ||
        n <= 0 || m < 0 || K < 0)
        return 1;

    parent = malloc(n * sizeof(int));
    size = malloc(n * sizeof(int));
    sum = malloc(n * sizeof(long long));

    if (!parent || !size || !sum)
        return 1;

    printf("Enter vertex weights:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &sum[i]) != 1)
            return 1;

        parent[i] = i;
        size[i] = 1;
    }

    printf("Initial maximum weight: %lld\n", getMax());

    printf("Enter edges (u v), vertices 0 to %d:\n", n - 1);

    for (int i = 0; i < m; i++) {
        int u, v;

        if (scanf("%d %d", &u, &v) != 2 ||
            u < 0 || u >= n || v < 0 || v >= n)
            return 1;

        unite(u, v);

        printf("After edge %d: %lld\n", i + 1, getMax());
    }

    free(parent);
    free(size);
    free(sum);

    return 0;
}