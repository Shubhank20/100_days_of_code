// Problem: Build a graph with n vertices and m edges using adjacency matrix representation.
// The graph may be directed or undirected.

// Input:
// - n (vertices)
// - m (edges)
// - m pairs (u, v)

// Output:
// - n x n adjacency matrix
#include <stdio.h>

int main() {
    int n, m, i, j, u, v;
    int graphType; // 1 for Undirected, 2 for Directed

    // 1. Input number of vertices and edges
    printf("Enter the number of vertices (n): ");
    scanf("%d", &n);
    printf("Enter the number of edges (m): ");
    scanf("%d", &m);

    // Input graph type
    printf("Enter Graph Type (1 for Undirected, 2 for Directed): ");
    scanf("%d", &graphType);

    // 2. Initialize the adjacency matrix with 0
    // We use n+1 to allow 1-based indexing (vertices 1 to n)
    int adj[n+1][n+1];

    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n; j++) {
            adj[i][j] = 0;
        }
    }

    // 3. Input edges and build the matrix
    printf("Enter %d edges (pairs u v):\n", m);
    for(i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        
        // Add edge from u to v
        adj[u][v] = 1;

        // If undirected, add edge from v to u as well
        if (graphType == 1) {
            adj[v][u] = 1;
        }
    }

    // 4. Output the adjacency matrix
    printf("\nAdjacency Matrix:\n");
    // Print column headers
    printf("   ");
    for(i = 1; i <= n; i++) {
        printf("%d ", i);
    }
    printf("\n");

    // Print rows
    for(i = 1; i <= n; i++) {
        printf("%d: ", i); // Print row header
        for(j = 1; j <= n; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }

    return 0;
}