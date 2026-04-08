// Problem: Print topological ordering of a Directed Acyclic Graph (DAG) using DFS.
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Adjacency list node
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

// Graph
typedef struct {
    int numVertices;
    Node** adjLists;
} Graph;

// Stack
int stack[MAX];
int stackTop = -1;

void push(int val) { stack[++stackTop] = val; }
int pop()          { return stack[stackTop--]; }
int isStackEmpty() { return stackTop == -1; }

// Create node
Node* createNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Create graph
Graph* createGraph(int V) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->numVertices = V;
    g->adjLists = (Node**)malloc(V * sizeof(Node*));
    for (int i = 0; i < V; i++)
        g->adjLists[i] = NULL;
    return g;
}

// Add directed edge
void addEdge(Graph* g, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = g->adjLists[src];
    g->adjLists[src] = newNode;
}

// DFS helper — pushes node to stack after visiting all neighbors
void dfs(Graph* g, int vertex, int* visited) {
    visited[vertex] = 1;

    Node* temp = g->adjLists[vertex];
    while (temp) {
        if (!visited[temp->dest])
            dfs(g, temp->dest, visited);
        temp = temp->next;
    }

    push(vertex); // Push AFTER all descendants are processed
}

// Topological Sort
void topologicalSort(Graph* g) {
    int* visited = (int*)calloc(g->numVertices, sizeof(int));

    for (int i = 0; i < g->numVertices; i++)
        if (!visited[i])
            dfs(g, i, visited);

    printf("Topological Order: ");
    while (!isStackEmpty())
        printf("%d ", pop());
    printf("\n");

    free(visited);
}

int main() {
    // Example: 6 nodes, edges representing dependencies
    // 5->2, 5->0, 4->0, 4->1, 2->3, 3->1
    Graph* g = createGraph(6);
    addEdge(g, 5, 2);
    addEdge(g, 5, 0);
    addEdge(g, 4, 0);
    addEdge(g, 4, 1);
    addEdge(g, 2, 3);
    addEdge(g, 3, 1);

    topologicalSort(g);

    return 0;
}