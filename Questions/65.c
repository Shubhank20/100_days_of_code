// Problem: Using DFS and parent tracking, detect if undirected graph has a cycle.

// Output:
// - YES or NO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int adj[MAX] [MAX];
int visited[MAX];
int V;

int dfs(int node, int parent) {
    visited[node] = 1;

    for (int i = 0; i < V; i++) {
        if (adj[node] [i]) {
            if (!visited[i]) {
                if (dfs(i, node))
                    return 1;
            } else if (i != parent) {
                return 1; // Cycle found
            }
        }
    }
    return 0;
}

int isCycle() {
    memset(visited, 0, sizeof(visited));

    // Check all components
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs(i, -1))
                return 1;
        }
    }
    return 0;
}

int main() {
    int E;
    scanf("%d %d", &V, &E);

    memset(adj, 0, sizeof(adj));

    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u] [v] = 1;
        adj[v] [u] = 1; // Undirected graph
    }

    if (isCycle())
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}