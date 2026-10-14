#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v;
} Edge;

int *parent, *size, *active;
long long *weight, *sum;
int n, m;

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

void activate(int v) {
    active[v] = 1;
    parent[v] = v;
    size[v] = 1;
    sum[v] = weight[v];
}

long long getMax(void) {
    long long best = 0;

    for (int i = 0; i < n; i++) {
        if (active[i] && find(i) == i && sum[i] > best)
            best = sum[i];
    }

    return best;
}

int main(void) {
    int q;

    printf("Enter n, m and number of deletions q: ");
    if (scanf("%d %d %d", &n, &m, &q) != 3 ||
        n <= 0 || m < 0 || q < 0 || q > n)
        return 1;

    weight = malloc(n * sizeof(long long));
    parent = malloc(n * sizeof(int));
    size = malloc(n * sizeof(int));
    sum = malloc(n * sizeof(long long));
    active = calloc(n, sizeof(int));

    Edge *edges = malloc((m > 0 ? m : 1) * sizeof(Edge));
    int *order = malloc((q > 0 ? q : 1) * sizeof(int));
    long long *ans = malloc((q > 0 ? q : 1) * sizeof(long long));

    if (!weight || !parent || !size || !sum ||
        !active || !edges || !order || !ans)
        return 1;

    printf("Enter vertex weights:\n");
    for (int i = 0; i < n; i++) {
        if (scanf("%lld", &weight[i]) != 1)
            return 1;
    }

    printf("Enter edges (u v):\n");
    for (int i = 0; i < m; i++) {
        if (scanf("%d %d", &edges[i].u, &edges[i].v) != 2 ||
            edges[i].u < 0 || edges[i].u >= n ||
            edges[i].v < 0 || edges[i].v >= n)
            return 1;
    }

    printf("Enter deletion order:\n");
    for (int i = 0; i < q; i++) {
        if (scanf("%d", &order[i]) != 1 ||
            order[i] < 0 || order[i] >= n ||
            active[order[i]] != 0)
            return 1;

        active[order[i]] = -1;
    }

    /* Activate vertices that survive every deletion. */
    for (int i = 0; i < n; i++) {
        if (active[i] == 0)
            activate(i);
    }

    /* Construct the graph after all deletions. */
    for (int i = 0; i < m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (active[u] == 1 && active[v] == 1)
            unite(u, v);
    }

    if (q > 0)
        ans[q - 1] = getMax();

    /* Restore deleted vertices in reverse order. */
    for (int i = q - 1; i > 0; i--) {
        int v = order[i];
        activate(v);

        for (int j = 0; j < m; j++) {
            int u = edges[j].u;
            int w = edges[j].v;

            if (u == v && active[w] == 1)
                unite(v, w);
            else if (w == v && active[u] == 1)
                unite(v, u);
        }

        ans[i - 1] = getMax();
    }

    printf("Maximum component weight after each deletion:\n");
    for (int i = 0; i < q; i++)
        printf("%lld\n", ans[i]);

    free(weight);
    free(parent);
    free(size);
    free(sum);
    free(active);
    free(edges);
    free(order);
    free(ans);

    return 0;
}