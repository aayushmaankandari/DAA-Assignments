#include <stdio.h>
#include <stdlib.h>

int *parent, *size;
int n;

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

int main(void) {
    int m;

    printf("Enter number of vertices and edges: ");
    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m < 0)
        return 1;

    parent = malloc(2 * n * sizeof(int));
    size = malloc(2 * n * sizeof(int));

    if (!parent || !size)
        return 1;

    for (int i = 0; i < 2 * n; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    int bipartite = 1;

    printf("Enter edges (u v), vertices 0 to %d:\n", n - 1);

    for (int i = 0; i < m; i++) {
        int u, v;

        if (scanf("%d %d", &u, &v) != 2 ||
            u < 0 || u >= n || v < 0 || v >= n) {
            printf("Invalid edge.\n");
            free(parent);
            free(size);
            return 1;
        }

        if (bipartite) {
            if (find(u) == find(v)) {
                bipartite = 0;
            } else {
                unite(u, v + n);
                unite(u + n, v);
            }
        }

        printf("After edge %d: %s\n", i + 1,
               bipartite ? "Bipartite" : "Not bipartite");
    }

    free(parent);
    free(size);
    return 0;
}