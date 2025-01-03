graph.txt 
9
0 4 0 0 0 0 0 8 0
4 0 8 0 0 0 0 11 0
0 8 0 7 0 4 0 0 2
0 0 7 0 9 14 0 0 0
0 0 0 9 0 10 0 0 0
0 0 4 14 10 0 2 0 0
0 0 0 0 0 2 0 1 6
8 11 0 0 0 0 1 0 7
0 0 2 0 0 0 6 7 0
24mca38@softlab-ThinkCentre-M92p:~/dslab$ cat 11_kruskals.c
#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 999

int parent[MAX];

typedef struct {
    int u, v, weight;
} Edge;

Edge edges[MAX];
int edgeCount = 0;

int find(int i) {
    if (parent[i] == -1) {
        return i;
    }
    return find(parent[i]);
}

void unionSets(int u, int v) {
    parent[v] = u;
}

int compare(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

int main() {
    FILE *file;
    int n, i, j, mincost = 0;

    // Open the file containing the graph
    file = fopen("graph.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    // Read the number of vertices
    fscanf(file, "%d", &n);

    // Initialize parent array
    for (i = 0; i < n; i++) {
        parent[i] = -1; // Initialize parent array to -1
    }

    // Read the cost adjacency matrix and create edge list
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int weight;
            fscanf(file, "%d", &weight);
            if (weight != 0 && i < j) { // Avoid duplicate edges
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].weight = weight;
                edgeCount++;
            }
        }
    }
    fclose(file); // Close the file after reading

    // Sort edges based on weight
    qsort(edges, edgeCount, sizeof(edges[0]), compare);

    printf("The edges of the Minimum Cost Spanning Tree are:\n");
    for (i = 0; i < edgeCount; i++) {
        int u = find(edges[i].u);
        int v = find(edges[i].v);

        if (u != v) { // If they are in different sets
            printf("%d edge (%d,%d) = %d\n", i + 1, edges[i].u, edges[i].v, edges[i].weight);
            mincost += edges[i].weight;
            unionSets(u, v);
        }
    }

    printf("\nMinimum cost = %d\n", mincost);
    return 0;
}
