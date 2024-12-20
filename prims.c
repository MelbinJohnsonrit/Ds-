#include <stdio.h>
#include <limits.h>
#define MAX_VERTICES 10

int minKey(int key[], int mstSet[], int vertices) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < vertices; v++) {
        if (mstSet[v] == 0 && key[v] < min) { // Only consider vertices not yet included in MST
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the constructed MST
void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    int mstweight = 0;
    printf("Edge \tWeight\n");
    for (int i = 1; i < vertices; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
        mstweight += graph[i][parent[i]]; // Calculate the total weight of the MST
    }
    printf("Total weight of MST: %d\n", mstweight);
}

// Function to construct and print the MST using Prim's algorithm
void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    int parent[MAX_VERTICES];  // Array to store the constructed MST
    int key[MAX_VERTICES];     // Key values used to pick minimum weight edge
    int mstSet[MAX_VERTICES];  // To represent the set of vertices not yet included in MST

    // Initialize all keys as infinite and mstSet[] as false
    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;  // Include the first vertex in MST
    parent[0] = -1;  // First node is always the root of MST

    for (int count = 0; count < vertices - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet, vertices);

        mstSet[u] = 1;  // Add the picked vertex to the MST Set

        // Update the key value and parent index of the adjacent vertices
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
    FILE *file;
    int graph[MAX_VERTICES][MAX_VERTICES];
    int vertices, edges;

    // Open the file containing the prims graph
    file = fopen("pgraph.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

/*    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);*/

    // Read the number of vertices
    fscanf(file, "%d", &vertices);

    if (vertices > MAX_VERTICES) {
        printf("The maximum number of vertices allowed is %d.\n", MAX_VERTICES);
        return 1;
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph[i][j] = 0;
        }
    }

 /*   printf("Enter the number of edges: ");
    scanf("%d", &edges);*/

// Read the number of edges
    fscanf(file, "%d", &edges);

    printf("Enter each edge in the format (u v weight), where u and v are vertex indices (0-based):\n");
    for (int i = 0; i < edges; i++) {
        int u, v, weight;
/*        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &u, &v, &weight);*/

    fscanf(file, "%d %d %d",&u, &v, &weight);

        graph[u][v] = weight;
        graph[v][u] = weight;
    }

    printf("Calculating MST using Prim's Algorithm...\n");
    primMST(graph, vertices);

    return 0;
}


pgraph.txt 
9
14
0 1 4
0 7 8
1 7 11
1 2 8
7 6 1
7 8 7
2 8 2
8 6 6
6 5 2
2 3 7
2 5 4
3 4 9
3 5 14
4 5 10

