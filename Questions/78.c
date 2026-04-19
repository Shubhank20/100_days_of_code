// Problem Statement
// Given weighted undirected graph, compute total weight of Minimum Spanning Tree using Prim’s algorithm.

// Input Format
// n m
// u v w
// ...

// Output Format
// Total weight of MST.

// Sample Input
// 4 5
// 1 2 3
// 1 3 5
// 2 3 1
// 2 4 4
// 3 4 2

// Sample Output
// 6

// Explanation
// One possible MST edges: (2-3), (3-4), (1-2)
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the priority queue (min-heap)
typedef struct Node {
    int vertex;
    int key;
} Node;

// Structure to represent the Min Heap
typedef struct MinHeap {
    int size;
    int capacity;
    int *pos;     // This is needed for decreaseKey() to keep track of vertex indices
    Node **array;
} MinHeap;

// Structure to represent an adjacency list node
typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode *next;
} AdjListNode;

// Structure to represent an adjacency list
typedef struct AdjList {
    AdjListNode *head;
} AdjList;

// Structure to represent a graph
typedef struct Graph {
    int V;
    AdjList *array;
} Graph;

// --- Helper Functions for Graph ---

// Create a new adjacency list node
AdjListNode *newAdjListNode(int dest, int weight) {
    AdjListNode *newNode = (AdjListNode *)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with V vertices
Graph *createGraph(int V) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList *)malloc(V * sizeof(AdjList));

    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Add an edge to an undirected graph
void addEdge(Graph *graph, int src, int dest, int weight) {
    // Add edge from src to dest
    AdjListNode *newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Add edge from dest to src (undirected)
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// --- Helper Functions for Min Heap ---

// Create a new Min Heap Node
Node *newMinHeapNode(int v, int key) {
    Node *minHeapNode = (Node *)malloc(sizeof(Node));
    minHeapNode->vertex = v;
    minHeapNode->key = key;
    return minHeapNode;
}

// Create a Min Heap
MinHeap *createMinHeap(int capacity) {
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node **)malloc(capacity * sizeof(Node *));
    return minHeap;
}

// Swap two nodes of min heap
void swapNode(Node **a, Node **b) {
    Node *t = *a;
    *a = *b;
    *b = t;
}

// Heapify a given subtree
void minHeapify(MinHeap *minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->key < minHeap->array[smallest]->key)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->key < minHeap->array[smallest]->key)
        smallest = right;

    if (smallest != idx) {
        Node *smallestNode = minHeap->array[smallest];
        Node *idxNode = minHeap->array[idx];

        // Swap positions
        minHeap->pos[smallestNode->vertex] = idx;
        minHeap->pos[idxNode->vertex] = smallest;

        // Swap nodes
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// Check if heap is empty
int isEmpty(MinHeap *minHeap) {
    return minHeap->size == 0;
}

// Extract minimum node from heap
Node *extractMin(MinHeap *minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    Node *root = minHeap->array[0];
    Node *lastNode = minHeap->array[minHeap->size - 1];

    minHeap->array[0] = lastNode;
    minHeap->pos[root->vertex] = minHeap->size - 1;
    minHeap->pos[lastNode->vertex] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Decrease key value of a given vertex v
void decreaseKey(MinHeap *minHeap, int v, int key) {
    int i = minHeap->pos[v];
    minHeap->array[i]->key = key;

    while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) {
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;
        swapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Check if a vertex v is in the min heap
int isInMinHeap(MinHeap *minHeap, int v) {
    if (minHeap->pos[v] < minHeap->size)
        return 1;
    return 0;
}

// --- Prim's Algorithm ---

void PrimMST(Graph *graph) {
    int V = graph->V;
    int *parent = (int *)malloc(V * sizeof(int)); // Array to store constructed MST
    int *key = (int *)malloc(V * sizeof(int));    // Key values used to pick minimum weight edge

    // Initialize min heap
    MinHeap *minHeap = createMinHeap(V);

    // Initialize min heap with all vertices. key value of all vertices (except 0th)
    // is initially infinite (INT_MAX).
    for (int v = 1; v < V; ++v) {
        parent[v] = -1;
        key[v] = 2147483647; // INT_MAX
        minHeap->array[v] = newMinHeapNode(v, key[v]);
        minHeap->pos[v] = v;
    }

    // Make key value of 0th vertex as 0 so that it is extracted first
    key[0] = 0;
    minHeap->array[0] = newMinHeapNode(0, key[0]);
    minHeap->pos[0] = 0;
    minHeap->size = V;

    long long totalWeight = 0; // Use long long to prevent overflow

    // In the following loop, min heap contains all nodes not yet added to MST.
    while (!isEmpty(minHeap)) {
        Node *minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex; // Store the extracted vertex number

        // Add the weight of the edge to the total weight.
        // The key of the node represents the weight of the connecting edge in the MST.
        totalWeight += key[u];

        // Traverse through all adjacent vertices of u
        AdjListNode *pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;

            // If v is not in MST and weight of (u,v) is smaller than current key of v
            if (isInMinHeap(minHeap, v) && pCrawl->weight < key[v]) {
                key[v] = pCrawl->weight;
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    printf("%lld\n", totalWeight);
}

// --- Main Function ---

int main() {
    int V, E;
    if (scanf("%d %d", &V, &E) != 2) return 0;

    Graph *graph = createGraph(V);
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        // Convert to 0-based indexing for C array handling
        addEdge(graph, u - 1, v - 1, w);
    }

    PrimMST(graph);

    return 0;
}