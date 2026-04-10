// Problem: Given weighted graph with non-negative edges, compute shortest path from source using priority queue.
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100
#define INF INT_MAX

// Structure for an adjacency list node
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

// Structure for a heap node (priority queue)
typedef struct HeapNode {
    int vertex;
    int distance;
} HeapNode;

// Global variables for graph and priority queue
Node* graph[MAX_NODES];
HeapNode heap[MAX_NODES * MAX_NODES];
int heapSize = 0;

// --- Priority Queue (Min-Heap) Functions ---

void swapHeapNodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].distance < heap[parent].distance) {
            swapHeapNodes(&heap[index], &heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapifyDown(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heapSize && heap[left].distance < heap[smallest].distance) {
        smallest = left;
    }
    if (right < heapSize && heap[right].distance < heap[smallest].distance) {
        smallest = right;
    }

    if (smallest != index) {
        swapHeapNodes(&heap[index], &heap[smallest]);
        heapifyDown(smallest);
    }
}

void enqueue(int vertex, int distance) {
    heap[heapSize].vertex = vertex;
    heap[heapSize].distance = distance;
    heapSize++;
    heapifyUp(heapSize - 1);
}

HeapNode dequeue() {
    HeapNode minNode = heap[0];
    heap[0] = heap[heapSize - 1];
    heapSize--;
    heapifyDown(0);
    return minNode;
}

int isHeapEmpty() {
    return heapSize == 0;
}

// --- Graph Helper Functions ---

void addEdge(int u, int v, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = graph[u];
    graph[u] = newNode;
}

void dijkstra(int startNode, int numNodes) {
    int dist[MAX_NODES];
    
    // Initialize distances
    for (int i = 0; i < numNodes; i++) {
        dist[i] = INF;
    }
    dist[startNode] = 0;

    // Add start node to priority queue
    enqueue(startNode, 0);

    printf("Shortest distances from Node %d:\n", startNode);

    while (!isHeapEmpty()) {
        HeapNode current = dequeue();
        int u = current.vertex;
        int d = current.distance;

        // If we found a shorter path to u previously, skip
        if (d > dist[u]) continue;

        // Iterate through all adjacent vertices
        Node* temp = graph[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;

            // Relaxation step
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                enqueue(v, dist[v]);
            }
            temp = temp->next;
        }
    }

    // Print results
    for (int i = 0; i < numNodes; i++) {
        if (dist[i] == INF) {
            printf("Node %d: Unreachable\n", i);
        } else {
            printf("Node %d: %d\n", i, dist[i]);
        }
    }
}

// --- Main Function ---

int main() {
    int numNodes = 5;
    int source = 0;

    // Example Graph Construction
    // 0 -> 1 (10), 0 -> 4 (5)
    // 1 -> 2 (1), 1 -> 4 (2)
    // 2 -> 3 (4)
    // 3 -> 0 (7), 3 -> 2 (6)
    // 4 -> 1 (3), 4 -> 2 (9), 4 -> 3 (2)
    
    addEdge(0, 1, 10);
    addEdge(0, 4, 5);
    addEdge(1, 2, 1);
    addEdge(1, 4, 2);
    addEdge(2, 3, 4);
    addEdge(3, 0, 7);
    addEdge(3, 2, 6);
    addEdge(4, 1, 3);
    addEdge(4, 2, 9);
    addEdge(4, 3, 2);

    dijkstra(source, numNodes);

    return 0;
}