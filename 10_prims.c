#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 10

int minKey(int key[], int mstSet[], int vertices) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < vertices; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    int mstweight = 0;
    printf("Edge \tWeight\n");
    for (int i = 1; i < vertices; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
	mstweight += graph[i][parent[i]];
    }
    printf("Total weight of MST: %d\n", mstweight);
}

void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    int mstSet[MAX_VERTICES];

    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;  
	parent[0] = -1;

    for (int count = 0; count < vertices - 1; count++) {
        int u = minKey(key, mstSet, vertices);

        mstSet[u] = 1;

        for (int v = 0; v < vertices; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, vertices);
}

int main() {
    int graph[MAX_VERTICES][MAX_VERTICES];
    int vertices, edges;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    if (vertices > MAX_VERTICES) {
        printf("The maximum number of vertices allowed is %d.\n", MAX_VERTICES);
        return 1;
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph[i][j] = 0;
        }
    }

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter each edge in the format (u v weight), where u and v are vertex indices (0-based):\n");
    for (int i = 0; i < edges; i++) {
        int u, v, weight;
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &u, &v, &weight);
        graph[u][v] = weight;
        graph[v][u] = weight;
    }

    printf("Calculating MST using Prim's Algorithm...\n");
    primMST(graph, vertices);

    return 0;
}
