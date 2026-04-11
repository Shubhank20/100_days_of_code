// Problem: Compute shortest path from source and detect negative weight cycles using Bellman-Ford.

// Input:
// - n vertices
// - m edges (u,v,w)

// Output:
// - Shortest distances OR NEGATIVE CYCLE
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a weighted edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a connected, directed and weighted graph
struct Graph {
    int V; // Number of vertices
    int E; // Number of edges
    struct Edge* edge; // Array of edges
};

// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// The main function that finds shortest distances from src to all
// other vertices using Bellman-Ford algorithm. It also detects negative
// weight cycle.
void BellmanFord(struct Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int dist[V];

    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times. A simple shortest
    // path from src to any other vertex can have at-most |V| - 1
    // edges
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            
            // Check for overflow before addition
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: Check for negative-weight cycles. The above step
    // guarantees shortest distances if graph doesn't contain
    // negative weight cycle. If we get a shorter path, then there
    // is a cycle.
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("NEGATIVE CYCLE\n");
            return; // Found a negative cycle, stop execution
        }
    }

    // Step 4: Print the shortest distances
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INT_MAX)
            printf("INF ");
        else
            printf("%d ", dist[i]);
    }
    printf("\n");
}

// Driver program to test above functions
int main() {
    int V, E;
    
    // Read number of vertices and edges
    // Assuming input format: V E on first line
    if (scanf("%d %d", &V, &E) != 2) {
        return 1;
    }

    struct Graph* graph = createGraph(V, E);

    // Read edges
    for (int i = 0; i < E; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph->edge[i].src = u;
        graph->edge[i].dest = v;
        graph->edge[i].weight = w;
    }

    // Assuming source is 0
    int src = 0;
    BellmanFord(graph, src);

    // Free allocated memory
    free(graph->edge);
    free(graph);

    return 0;
}