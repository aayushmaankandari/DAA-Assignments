#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int to;
    struct Edge *next;
} Edge;

void addEdge(Edge **adj, int u, int v) {
    Edge *e = malloc(sizeof(Edge));

    if (!e) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    e->to = v;
    e->next = adj[u];
    adj[u] = e;
}

int main(void) {
    int V, E;

    /*
       Input:
       V E
       E lines: u v
       K
       K hub vertices, in index order
       R

       The graph is undirected.
    */

    if (scanf("%d %d", &V, &E) != 2 ||
        V <= 0 || E < 0)
        return 1;

    Edge **adj = calloc(V + 1, sizeof(Edge *));

    int *dist = malloc((V + 1) * sizeof(int));
    int *owner = malloc((V + 1) * sizeof(int));

    /* BFS frontier arrays. */
    int *current = malloc((V + 1) * sizeof(int));
    int *next = malloc((V + 1) * sizeof(int));

    if (!adj || !dist || !owner || !current || !next) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < E; i++) {
        int u, v;

        if (scanf("%d %d", &u, &v) != 2 ||
            u < 1 || u > V || v < 1 || v > V) {
            fprintf(stderr, "Invalid edge input\n");
            return 1;
        }

        addEdge(adj, u, v);
        addEdge(adj, v, u);
    }

    int K;

    if (scanf("%d", &K) != 1 || K < 1 || K > V) {
        fprintf(stderr, "Invalid number of hubs\n");
        return 1;
    }

    int *hubs = malloc(K * sizeof(int));

    if (!hubs) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < K; i++) {
        if (scanf("%d", &hubs[i]) != 1 ||
            hubs[i] < 1 || hubs[i] > V) {
            fprintf(stderr, "Invalid hub vertex\n");
            return 1;
        }
    }

    int R;

    if (scanf("%d", &R) != 1 || R < 0) {
        fprintf(stderr, "Invalid radius\n");
        return 1;
    }

    for (int v = 1; v <= V; v++) {
        dist[v] = -1;
        owner[v] = -1;
    }

    int currentCount = 0;

    /* Initialize all sources in increasing hub-index order. */
    for (int i = 0; i < K; i++) {
        int h = hubs[i];
        int hubIndex = i + 1;

        if (dist[h] == -1) {
            dist[h] = 0;
            owner[h] = hubIndex;
            current[currentCount++] = h;
        } else if (hubIndex < owner[h]) {
            owner[h] = hubIndex;
        }
    }

    int level = 0;

    while (currentCount > 0 && level < R) {
        int nextCount = 0;

        for (int i = 0; i < currentCount; i++) {
            int u = current[i];

            for (Edge *e = adj[u]; e != NULL; e = e->next) {
                int v = e->to;
                int newDist = level + 1;

                if (dist[v] == -1) {
                    dist[v] = newDist;
                    owner[v] = owner[u];
                    next[nextCount++] = v;
                } else if (dist[v] == newDist &&
                           owner[u] < owner[v]) {
                    /*
                       Same minimum distance:
                       choose the smallest hub index.
                    */
                    owner[v] = owner[u];
                }
            }
        }

        int *temp = current;
        current = next;
        next = temp;

        currentCount = nextCount;
        level++;
    }

    printf("Vertex\tOwner\tDistance\n");

    for (int v = 1; v <= V; v++) {
        if (dist[v] == -1 || dist[v] > R) {
            printf("%d\t-1\t-1\n", v);
        } else {
            printf("%d\t%d\t%d\n", v, owner[v], dist[v]);
        }
    }

    for (int v = 1; v <= V; v++) {
        Edge *e = adj[v];

        while (e != NULL) {
            Edge *temp = e;
            e = e->next;
            free(temp);
        }
    }

    free(adj);
    free(dist);
    free(owner);
    free(current);
    free(next);
    free(hubs);

    return 0;
}