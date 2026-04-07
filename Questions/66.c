// Problem: Detect cycle in directed graph using DFS and recursion stack.

// Output:
// - YES if cycle exists
#include <stdio.h>
#include <stdlib.h>

// Node structure for adjacency list
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

// Structure to represent the graph
typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

// Color constants for the 3-color algorithm
#define WHITE 0
#define GREY  1
#define BLACK 2

// Create a new node
Node* createNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = V;
    graph->adjLists = (Node**)malloc(V * sizeof(Node*));

    for (int i = 0; i < V; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

// Add an edge (directed) from src to dest
void addEdge(Graph* graph, int src, int dest) {
    // Prepend to the linked list
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// Recursive DFS function to detect cycle
// Returns 1 if a cycle is found, 0 otherwise
int isCyclicUtil(Graph* graph, int v, int* color) {
    // Mark the current node as GREY (in recursion stack)
    color[v] = GREY;

    // Recur for all adjacent vertices
    Node* temp = graph->adjLists[v];
    while (temp != NULL) {
        int neighbor = temp->dest;

        // If neighbor is GREY, it's already in recursion stack -> Cycle found
        if (color[neighbor] == GREY) {
            return 1;
        }

        // If neighbor is WHITE, recur for it
        if (color[neighbor] == WHITE) {
            if (isCyclicUtil(graph, neighbor, color)) {
                return 1;
            }
        }
        
        // If neighbor is BLACK, do nothing (already processed)
        
        temp = temp->next;
    }

    // Mark the current node as BLACK (processing done)
    color[v] = BLACK;

    return 0;
}

// Main function to check for cycle
int isCyclic(Graph* graph) {
    // Initialize all vertices as WHITE (unvisited)
    int* color = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        color[i] = WHITE;
    }

    // Call the recursive helper function for all vertices
    for (int i = 0; i < graph->numVertices; i++) {
        if (color[i] == WHITE) {
            if (isCyclicUtil(graph, i, color)) {
                free(color);
                return 1; // Cycle detected
            }
        }
    }

    free(color);
    return 0; // No cycle
}

// Helper function to free graph memory
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp != NULL) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->adjLists);
    free(graph);
}

int main() {
    // Example Usage
    
    // Case 1: Graph with a cycle (0 -> 1 -> 2 -> 0)
    int V = 3;
    Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0);

    if (isCyclic(graph)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    freeGraph(graph);

    // Case 2: Graph without a cycle
    V = 3;
    graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    // 2 has no outgoing edges

    if (isCyclic(graph)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    freeGraph(graph);

    return 0;
}