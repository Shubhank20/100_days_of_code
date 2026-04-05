// Problem: Perform BFS from a given source using queue.

// Input:
// - n
// - adjacency list
// - source s

// Output:
// - BFS traversal order
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Adjacency list node
struct Node {
    int data;
    struct Node* next;
};

// Graph structure
struct Graph {
    int numVertices;
    struct Node* adjList[MAX];
    int visited[MAX];
};

// Create a new node
struct Node* createNode(int data) {
    struct Node* node = malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Add edge to adjacency list
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* node = createNode(dest);
    node->next = graph->adjList[src];
    graph->adjList[src] = node;
}

// BFS traversal
void bfs(struct Graph* graph, int source) {
    int queue[MAX];
    int front = 0, rear = 0;

    // Mark source as visited and enqueue
    graph->visited[source] = 1;
    queue[rear++] = source;

    printf("BFS Traversal: ");

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        // Visit all unvisited neighbors
        struct Node* temp = graph->adjList[current];
        while (temp) {
            if (!graph->visited[temp->data]) {
                graph->visited[temp->data] = 1;
                queue[rear++] = temp->data;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

int main() {
    int n, e, s;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = n;

    // Initialize adjacency list and visited array
    for (int i = 0; i < n; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (src dest):\n");
    for (int i = 0; i < e; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
        addEdge(graph, dest, src); // Remove for directed graph
    }

    printf("Enter source vertex: ");
    scanf("%d", &s);

    bfs(graph, s);

    return 0;
}