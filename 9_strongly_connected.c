#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int dest;
    struct Node* next;
} Node;

typedef struct Graph {
    int V;
    Node** adjList;
    Node** revAdjList; // For transpose graph
    bool* visited;
} Graph;

Node* createNode(int dest) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int V) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;
    graph->adjList = (Node**) malloc(V * sizeof(Node*));
    graph->revAdjList = (Node**) malloc(V * sizeof(Node*));
    graph->visited = (bool*) malloc(V * sizeof(bool));
    for (int i = 0; i < V; i++) {
        graph->adjList[i] = NULL;
        graph->revAdjList[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    Node* revNode = createNode(src);
    revNode->next = graph->revAdjList[dest];
    graph->revAdjList[dest] = revNode;
}

void dfs(Graph* graph, int v, int* stack, int* top, bool reverse) {
    graph->visited[v] = true;
    Node* adjList = reverse ? graph->revAdjList[v] : graph->adjList[v];
    for (Node* temp = adjList; temp != NULL; temp = temp->next) {
        if (!graph->visited[temp->dest]) {
            dfs(graph, temp->dest, stack, top, reverse);
        }
    }
    if (!reverse) {
        stack[++(*top)] = v;
    }
}

void printSCC(Graph* graph, int v) {
    graph->visited[v] = true;
    printf("%d ", v+1);
    for (Node* temp = graph->revAdjList[v]; temp != NULL; temp = temp->next) {
        if (!graph->visited[temp->dest]) {
            printSCC(graph, temp->dest);
        }
    }
}

void findSCCs(Graph* graph) {
    int* stack = (int*) malloc(graph->V * sizeof(int));
    int top = -1;

    // First DFS to fill stack according to finish times
    for (int i = 0; i < graph->V; i++) {
        if (!graph->visited[i]) {
            dfs(graph, i, stack, &top, false);
        }
    }

    // Reset visited array for second DFS
    for (int i = 0; i < graph->V; i++) {
        graph->visited[i] = false;
    }

    // Second DFS on transposed graph to find SCCs
    printf("Strongly Connected Components:\n");
    while (top != -1) {
        int v = stack[top--];
        if (!graph->visited[v]) {
            printSCC(graph, v);
            printf("\n");
        }
    }

    free(stack);
}

int main() {
    int V, E, src, dest;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    Graph* graph = createGraph(V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    for (int i = 0; i < E; i++) {
        printf("Enter edge %d (source destination): ", i + 1);
        if (scanf("%d %d", &src, &dest) != 2) {
            printf("Invalid input! Please enter two integers.\n");
            i--; // Decrement to retry the input for this edge
        } else {
            // Adjust for 0-based indexing
            if (src >= 1 && src <= V && dest >= 1 && dest <= V) {
                addEdge(graph, src - 1, dest - 1);
            } else {
                printf("Invalid vertex! Please enter vertices between 1 and %d.\n", V);
                i--; // Decrement to retry the input for this edge
            }
        }
    }

    findSCCs(graph);

    for (int i = 0; i < V; i++) {
        free(graph->adjList[i]);
        free(graph->revAdjList[i]);
    }
    free(graph->adjList);
    free(graph->revAdjList);
    free(graph->visited);
    free(graph);

    return 0;
}
