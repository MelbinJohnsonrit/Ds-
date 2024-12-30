#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int graph[MAX][MAX], visited[MAX], n;

void DFS(int v) {
    printf("%d ", v);
    visited[v] = 1;

    for (int i = 0; i < n; i++) {
        if (graph[v][i] == 1 && !visited[i]) {
            DFS(i);
        }
    }
}

int main() {
    int edges, u, v;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1; // Remove this line for directed graphs
    }

    for (int i = 0; i < n; i++) visited[i] = 0;

    printf("DFS Traversal starting from vertex 0: ");
    DFS(0);

    return 0;
}





#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int graph[MAX][MAX], visited[MAX], n;

void BFS(int start) {
    int queue[MAX], front = 0, rear = 0;
    printf("%d ", start);
    visited[start] = 1;
    queue[rear++] = start;

    while (front != rear) {
        int current = queue[front++];
        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                printf("%d ", i);
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

int main() {
    int edges, u, v;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1; // Remove this line for directed graphs
    }

    for (int i = 0; i < n; i++) visited[i] = 0;

    printf("BFS Traversal starting from vertex 0: ");
    BFS(0);

    return 0;
}






#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int graph[MAX][MAX], inDegree[MAX], n;

void topologicalSort() {
    int queue[MAX], front = 0, rear = 0, count = 0;

    // Initialize the queue with vertices having in-degree 0
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    printf("Topological Order: ");
    while (front != rear) {
        int current = queue[front++];
        printf("%d ", current);
        count++;

        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1) {
                inDegree[i]--;
                if (inDegree[i] == 0) {
                    queue[rear++] = i;
                }
            }
        }
    }

    if (count != n) {
        printf("\nGraph has a cycle. Topological sort not possible.\n");
    }
}

int main() {
    int edges, u, v;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        graph[u][v] = 1; // Directed edge from u to v
        inDegree[v]++;
    }

    topologicalSort();

    return 0;
}
