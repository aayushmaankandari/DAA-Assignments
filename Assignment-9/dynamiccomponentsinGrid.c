#include <stdio.h>
#include <stdlib.h>

int *parent, *size, *active;
int rows, cols;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

int unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
        return 0;

    if (size[a] < size[b]) {
        int temp = a;
        a = b;
        b = temp;
    }

    parent[b] = a;
    size[a] += size[b];

    return 1;
}

int main(void) {
    int q;

    printf("Enter rows, columns and number of operations: ");
    if (scanf("%d %d %d", &rows, &cols, &q) != 3 ||
        rows <= 0 || cols <= 0 || q < 0 ||
        (long long)rows * cols > 10000000)
        return 1;

    int total = rows * cols;

    parent = malloc(total * sizeof(int));
    size = malloc(total * sizeof(int));
    active = calloc(total, sizeof(int));

    if (!parent || !size || !active)
        return 1;

    for (int i = 0; i < total; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    int islands = 0;

    printf("Enter cell coordinates (row column), 0-based:\n");

    for (int t = 0; t < q; t++) {
        int r, c;

        if (scanf("%d %d", &r, &c) != 2 ||
            r < 0 || r >= rows || c < 0 || c >= cols) {
            printf("Invalid cell.\n");
            continue;
        }

        int id = r * cols + c;

        if (!active[id]) {
            active[id] = 1;
            islands++;

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr < 0 || nr >= rows ||
                    nc < 0 || nc >= cols)
                    continue;

                int nid = nr * cols + nc;

                if (active[nid])
                    islands -= unite(id, nid);
            }
        }

        printf("Number of connected components: %d\n", islands);
    }

    free(parent);
    free(size);
    free(active);

    return 0;
}