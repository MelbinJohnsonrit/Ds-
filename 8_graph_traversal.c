#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adj_list[MAX];
bool visited[MAX];
int vertex_count = 0;

Node* create_node(int vertex) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->vertex = vertex;
    new_node->next = NULL;
    return new_node;
}

void add_vertex() {
    if (vertex_count < MAX) {
        adj_list[vertex_count] = NULL;
        printf("Vertex %d added.\n", vertex_count);
        vertex_count++;
    } else {
        printf("Maximum number of vertices reached.\n");
    }
}

/*void add_edge(int start, int end) {
    if (start >= vertex_count || end >= vertex_count) {
        printf("Invalid Vertex.\n");
        return;
    }

    Node* new_node = create_node(end);
    new_node->next = adj_list[start];
    adj_list[start] = new_node;

    new_node = create_node(start);
    new_node->next = adj_list[end];
    adj_list[end] = new_node;

    printf("Edge added between %d and %d.\n", start, end);
}*/

void add_edge(int start, int end) {
    if (start >= vertex_count || end >= vertex_count) {
        printf("Invalid Vertex.\n");
        return;
    }

    Node* new_node = create_node(end);
    new_node->next = adj_list[start];
    adj_list[start] = new_node;

    printf("Edge added from %d to %d.\n", start, end);
}


void bfs(int start) {
    for (int i = 0; i < vertex_count; i++) {
        visited[i] = false;
    }

    int queue[MAX], front = 0, rear = 0;
    visited[start] = true;
    queue[rear++] = start;
    printf("BFS: ");

    while (front < rear) {
        int vertex = queue[front++];
        printf("%d ", vertex);
        Node* adj = adj_list[vertex];
        while (adj != NULL) {
            if (!visited[adj->vertex]) {
                visited[adj->vertex] = true;
                queue[rear++] = adj->vertex;
            }
            adj = adj->next;
        }
    }
    printf("\n");
}

void dfs_helper(int vertex) {
    visited[vertex] = true;
    printf("%d ", vertex);
    Node* adj = adj_list[vertex];
    while (adj != NULL) {
        if (!visited[adj->vertex]) {
            dfs_helper(adj->vertex);
        }
        adj = adj->next;
    }
}

void dfs(int start) {
    for (int i = 0; i < vertex_count; i++) {
        visited[i] = false;
    }

    printf("DFS: ");
    dfs_helper(start);
    printf("\n");
}

void topological_sort_helper(int vertex, int stack[], int* top) {
    visited[vertex] = true;
    Node* adj = adj_list[vertex];
    while (adj != NULL) {
        if (!visited[adj->vertex]) {
            topological_sort_helper(adj->vertex, stack, top);
        }
        adj = adj->next;
    }
    stack[(*top)++] = vertex;
}

void topological_sort() {
    for (int i = 0; i < vertex_count; i++) {
        visited[i] = false;
    }

    int stack[MAX], top = 0;
    for (int i = 0; i < vertex_count; i++) {
        if (!visited[i]) {
            topological_sort_helper(i, stack, &top);
        }
    }

    printf("Topological Sort: ");
    while (top > 0) {
        printf("%d ", stack[--top]);
    }
    printf("\n");
}

int main() {
    int choice, start, end, vertex;

    do {
        printf("\n1. Add Vertex\n2. Add Edge\n3. BFS\n4. DFS\n5. Topological Sort\n6. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_vertex();
                break;
            case 2:
                printf("Enter start and end vertex: ");
                scanf("%d %d", &start, &end);
                add_edge(start, end);
                break;
            case 3:
                printf("Enter starting vertex for BFS: ");
                scanf("%d", &vertex);
                bfs(vertex);
                break;
            case 4:
                printf("Enter starting vertex for DFS: ");
                scanf("%d", &vertex);
                dfs(vertex);
                break;
            case 5:
                topological_sort();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
