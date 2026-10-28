#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF (LLONG_MAX / 4)

typedef struct Node {
    int v, parity;
    long long d;
    struct Node *next;
} Node;

typedef struct {
    Node *front, *back;
} Deque;

void push_front(Deque *dq, int v, int p, long long d) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    node->v = v;
    node->parity = p;
    node->d = d;
    node->next = dq->front;
    dq->front = node;

    if (dq->back == NULL)
        dq->back = node;
}

void push_back(Deque *dq, int v, int p, long long d) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    node->v = v;
    node->parity = p;
    node->d = d;
    node->next = NULL;

    if (dq->back == NULL) {
        dq->front = dq->back = node;
    } else {
        dq->back->next = node;
        dq->back = node;
    }
}

int pop_front(Deque *dq, int *v, int *p, long long *d) {
    if (dq->front == NULL)
        return 0;

    Node *temp = dq->front;
    *v = temp->v;
    *p = temp->parity;
    *d = temp->d;

    dq->front = dq->front->next;

    if (dq->front == NULL)
        dq->back = NULL;

    free(temp);
    return 1;
}

typedef struct Edge {
    int to, weight;
    struct Edge *next;
} Edge;

void addEdge(Edge **adj, int u, int v, int w) {
    Edge *e = malloc(sizeof(Edge));
    if (!e) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    e->to = v;
    e->weight = w;
    e->next = adj[u];
    adj[u] = e;
}

int main(void) {
    int V, E, S;
    long long C;

    /*
       Input:
       V E S C
       E lines: u v w

       Vertices are numbered 1 to V.
       Edges are directed, and w is either 0 or 1.
    */

    if (scanf("%d %d %d %lld", &V, &E, &S, &C) != 4)
        return 1;

    if (V <= 0 || E < 0 || S < 1 || S > V || C < 0)
        return 1;

    Edge **adj = calloc(V + 1, sizeof(Edge *));
    long long (*dist)[2] = malloc((V + 1) * sizeof(*dist));

    if (!adj || !dist) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < E; i++) {
        int u, v, w;

        if (scanf("%d %d %d", &u, &v, &w) != 3 ||
            u < 1 || u > V || v < 1 || v > V ||
            (w != 0 && w != 1)) {
            fprintf(stderr, "Invalid edge input\n");
            return 1;
        }

        addEdge(adj, u, v, w);
    }

    for (int v = 1; v <= V; v++) {
        dist[v][0] = INF;
        dist[v][1] = INF;
    }

    Deque dq = {NULL, NULL};

    /* Initially, zero weight-1 edges have been traversed. */
    dist[S][0] = 0;
    push_front(&dq, S, 0, 0);

    int u, parity;
    long long d;

    while (pop_front(&dq, &u, &parity, &d)) {
        /* Ignore outdated deque entries. */
        if (d != dist[u][parity])
            continue;

        for (Edge *e = adj[u]; e != NULL; e = e->next) {
            int v = e->to;
            int w = e->weight;

            int newParity = parity ^ w;
            long long newDist = d + w;

            if (newDist < dist[v][newParity]) {
                dist[v][newParity] = newDist;

                if (w == 0)
                    push_front(&dq, v, newParity, newDist);
                else
                    push_back(&dq, v, newParity, newDist);
            }
        }
    }

    printf("Vertex\tMinimum Cost\n");

    for (int v = 1; v <= V; v++) {
        long long answer = INF;

        if (dist[v][0] != INF)
            answer = dist[v][0];

        if (dist[v][1] != INF &&
            dist[v][1] + C < answer)
            answer = dist[v][1] + C;

        if (answer == INF)
            printf("%d\tUnreachable\n", v);
        else
            printf("%d\t%lld\n", v, answer);
    }

    while (pop_front(&dq, &u, &parity, &d))
        ;

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

    return 0;
}