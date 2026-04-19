// Problem Statement
// Using BFS or DFS, check if the entire graph is connected.

// Input Format
// n m
// edges

// Output Format
// CONNECTED
// NOT CONNECTED

// Sample Input
// 4 2
// 1 2
// 3 4

// Sample Output
// NOT CONNECTED
#include <stdio.h>
#include <stdlib.h>

// Define the maximum number of nodes based on typical competitive programming constraints
// Adjust MAX_N if necessary for larger inputs
#define MAX_N 1000

// Structure for the adjacency list node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Global variables for simplicity
Node* adj[MAX_N];
int visited[MAX_N];
int n, m;

// Function to add an edge to the undirected graph
void addEdge(int u, int v) {
    // Add edge from u to v
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = adj[u];
    adj[u] = newNode;

    // Add edge from v to u (since the graph is undirected)
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = u;
    newNode->next = adj[v];
    adj[v] = newNode;
}

// BFS Algorithm
void bfs(int startNode) {
    // Create a queue for BFS
    int queue[MAX_N];
    int front = 0;
    int rear = 0;

    // Mark the start node as visited and enqueue it
    visited[startNode] = 1;
    queue[rear++] = startNode;

    while (front < rear) {
        // Dequeue a vertex from queue
        int current = queue[front++];

        // Get all adjacent vertices of the dequeued vertex s
        Node* temp = adj[current];
        while (temp != NULL) {
            int adjVertex = temp->vertex;

            // If an adjacent has not been visited, mark it visited and enqueue it
            if (visited[adjVertex] == 0) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
}

int main() {
    // Read number of nodes (n) and edges (m)
    if (scanf("%d %d", &n, &m) != 2) {
        return 1;
    }

    // Initialize adjacency list and visited array
    for (int i = 1; i <= n; i++) {
        adj[i] = NULL;
        visited[i] = 0;
    }

    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    // Perform BFS starting from node 1
    // Note: We handle the case where n=0 or isolated nodes might exist, 
    // but starting from 1 covers connectivity from the first component.
    if (n > 0) {
        bfs(1);
    }

    // Check if all nodes are visited
    int isConnected = 1;
    for (int i = 1; i <= n; i++) {
        if (visited[i] == 0) {
            isConnected = 0;
            break;
        }
    }

    // Output the result
    if (isConnected) {
        printf("CONNECTED\n");
    } else {
        printf("NOT CONNECTED\n");
    }

    // Cleanup allocated memory (Good practice)
    for (int i = 1; i <= n; i++) {
        Node* temp = adj[i];
        while (temp != NULL) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }

    return 0;
}