// Problem Statement
// Find shortest distances from source vertex in a weighted graph with non-negative weights.

// Input Format
// n m
// u v w
// source

// Output Format
// Distances to all vertices.

// Sample Input
// 5 6
// 1 2 2
// 1 3 4
// 2 3 1
// 2 4 7
// 3 5 3
// 4 5 1
// 1

// Sample Output
// 0 2 3 9 6

// Explanation
// Shortest distances computed via priority queue.
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 1000

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} AdjList;

typedef struct {
    int vertex;
    int distance;
} HeapNode;

typedef struct {
    HeapNode* array;
    int size;
    int capacity;
} PriorityQueue;

// Function to create a new adjacency list node
Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to add an edge to the adjacency list
void addEdge(AdjList* adjList, int u, int v, int weight) {
    Node* newNode = createNode(v, weight);
    newNode->next = adjList[u].head;
    adjList[u].head = newNode;
}

// Priority Queue functions
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->array = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void swapHeapNodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue* pq, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->array[index].distance < pq->array[parent].distance) {
            swapHeapNodes(&pq->array[index], &pq->array[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapifyDown(PriorityQueue* pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->array[left].distance < pq->array[smallest].distance) {
        smallest = left;
    }
    if (right < pq->size && pq->array[right].distance < pq->array[smallest].distance) {
        smallest = right;
    }
    if (smallest != index) {
        swapHeapNodes(&pq->array[index], &pq->array[smallest]);
        heapifyDown(pq, smallest);
    }
}

void insert(PriorityQueue* pq, int vertex, int distance) {
    if (pq->size == pq->capacity) {
        return;
    }
    HeapNode newNode;
    newNode.vertex = vertex;
    newNode.distance = distance;
    pq->array[pq->size] = newNode;
    heapifyUp(pq, pq->size);
    pq->size++;
}

HeapNode extractMin(PriorityQueue* pq) {
    HeapNode minNode;
    if (pq->size == 0) {
        minNode.vertex = -1;
        minNode.distance = -1;
        return minNode;
    }
    minNode = pq->array[0];
    pq->array[0] = pq->array[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    return minNode;
}

bool isEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}

void dijkstra(AdjList* adjList, int n, int source, int* distances) {
    PriorityQueue* pq = createPriorityQueue(n * n);
    distances[source] = 0;
    insert(pq, source, 0);

    while (!isEmpty(pq)) {
        HeapNode current = extractMin(pq);
        int u = current.vertex;

        Node* temp = adjList[u].head;
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;

            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                insert(pq, v, distances[v]);
            }
            temp = temp->next;
        }
    }
    free(pq->array);
    free(pq);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    AdjList* adjList = (AdjList*)malloc((n + 1) * sizeof(AdjList));
    for (int i = 0; i <= n; i++) {
        adjList[i].head = NULL;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(adjList, u, v, w);
        // Assuming the graph is directed. If undirected, add the reverse edge as well:
        // addEdge(adjList, v, u, w);
    }

    int source;
    scanf("%d", &source);

    int* distances = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        distances[i] = INT_MAX;
    }

    dijkstra(adjList, n, source, distances);

    for (int i = 1; i <= n; i++) {
        printf("%d ", distances[i]);
    }
    printf("\n");

    // Free allocated memory
    for (int i = 1; i <= n; i++) {
        Node* temp = adjList[i].head;
        while (temp != NULL) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(adjList);
    free(distances);

    return 0;
}