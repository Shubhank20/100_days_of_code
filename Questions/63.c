// Problem: Perform DFS starting from a given source vertex using recursion.

// Input:
// - n
// - adjacency list
// - starting vertex s

// Output:
// - DFS traversal order
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Global variables to keep track of visited status and traversal order
int visited[MAX_VERTICES];
int traversal[MAX_VERTICES];
int traversalIndex = 0;

// Adjacency list node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to add an edge to the adjacency list
void addEdge(struct Node* adj[], int u, int v) {
    // Add v to u's list
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = v;
    newNode->next = adj[u];
    adj[u] = newNode;

    // Add u to v's list (for undirected graph)
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = u;
    newNode->next = adj[v];
    adj[v] = newNode;
}

// Recursive DFS function
void DFS(struct Node* adj[], int s) {
    // Mark the current node as visited
    visited[s] = 1;
    
    // Store the node in the traversal order
    traversal[traversalIndex++] = s;

    // Recur for all the vertices adjacent to this vertex
    struct Node* temp = adj[s];
    while (temp != NULL) {
        int neighbor = temp->data;
        if (!visited[neighbor]) {
            DFS(adj, neighbor);
        }
        temp = temp->next;
    }
}

int main() {
    int n = 5; // Number of vertices (0 to 4)

    // Initialize adjacency list
    struct Node* adj[MAX_VERTICES] = {NULL};

    // Initialize visited array
    for(int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    // Create edges
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 4);

    int startVertex = 0;

    printf("Starting DFS from vertex: %d\n", startVertex);
    DFS(adj, startVertex);

    printf("DFS Traversal Order: ");
    for (int i = 0; i < traversalIndex; i++) {
        printf("%d ", traversal[i]);
    }
    printf("\n");

    return 0;
}