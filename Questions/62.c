// Problem: Build a graph with adjacency list representation. Use linked lists or dynamic arrays.

// Input:
// - n (vertices)
// - m (edges)
// - edges (u, v)

// Output:
// - List of adjacency lists for each vertex
#include <stdio.h>
#include <stdlib.h>

// Node for linked list
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

// Graph structure
typedef struct Graph {
    int n;
    Node** adjList;
} Graph;

// Create a new node
Node* createNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with n vertices
Graph* createGraph(int n) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->n = n;
    graph->adjList = (Node**)calloc(n, sizeof(Node*));
    return graph;
}

// Add an undirected edge (u, v)
void addEdge(Graph* graph, int u, int v) {
    // Add v to u's list
    Node* newNode = createNode(v);
    newNode->next = graph->adjList[u];
    graph->adjList[u] = newNode;

    // Add u to v's list (remove for directed graph)
    newNode = createNode(u);
    newNode->next = graph->adjList[v];
    graph->adjList[v] = newNode;
}

// Print adjacency list
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->n; i++) {
        printf("Vertex %d: ", i);
        Node* temp = graph->adjList[i];
        while (temp) {
            printf("%d -> ", temp->dest);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Free memory
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->n; i++) {
        Node* temp = graph->adjList[i];
        while (temp) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adjList);
    free(graph);
}

int main() {
    int n, m;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &m);

    Graph* graph = createGraph(n);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    printf("\nAdjacency List:\n");
    printGraph(graph);

    freeGraph(graph);
    return 0;
}