// Problem: Given a weighted graph with n vertices, implement the Floyd-Warshall algorithm to compute the shortest distances between every pair of vertices. The graph may contain positive or negative edge weights, but it does not contain any negative weight cycles.

// Input:
// - First line: integer n representing the number of vertices
// - Next n lines: n space-separated integers representing the adjacency matrix of the graph
//   (use -1 to indicate no direct edge between two vertices)

// Output:
// - Print the shortest distance matrix where the value at row i and column j represents the shortest distance from vertex i to vertex j

// Example:
// Input:
// 4
// 0 5 -1 10
// -1 0 3 -1
// -1 -1 0 1
// -1 -1 -1 0

// Output:
// 0 5 8 9
// -1 0 3 4
// -1 -1 0 1
// -1 -1 -1 0

// Explanation:
// The Floyd-Warshall algorithm works by considering each vertex as an intermediate point and updating the shortest paths between all pairs of vertices. For example, the shortest path from vertex 1 to vertex 3 is improved via vertex 2 with total cost 8. This process is repeated for all vertices, resulting in the final shortest distance matrix.
#include <stdio.h>
#include <limits.h>

// A large value to represent infinity
// We use INT_MAX / 2 to prevent integer overflow when adding two values
#define INF INT_MAX / 2

int main() {
    int n;
    
    // 1. Read the number of vertices
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    // 2. Read the adjacency matrix and initialize the distance matrix
    int dist[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int weight;
            scanf("%d", &weight);
            if (weight == -1) {
                dist[i][j] = INF;
            } else {
                dist[i][j] = weight;
            }
        }
    }

    // 3. Floyd-Warshall Algorithm
    // k is the intermediate vertex
    for (int k = 0; k < n; k++) {
        // i is the source vertex
        for (int i = 0; i < n; i++) {
            // j is the destination vertex
            for (int j = 0; j < n; j++) {
                // If path from i to k and k to j exists, check if it's shorter
                // We check against INF to avoid potential overflow if INF + INF wraps around to negative
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    // 4. Print the resulting shortest distance matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                printf("-1 ");
            } else {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}