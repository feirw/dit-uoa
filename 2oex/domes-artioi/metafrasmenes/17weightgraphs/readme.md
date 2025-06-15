```c
#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

// Function to find the vertex with the minimum distance that hasn't been visited yet
int minDistance(int distance[], int visited[], int V) {
    int min = INF, minIndex = -1;
    
    for (int v = 0; v < V; v++) {
        if (!visited[v] && distance[v] <= min) {
            min = distance[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void Dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int V, int source) {
    int distance[MAX_VERTICES];   // Shortest distances from source
    int visited[MAX_VERTICES];    // Visited vertices
    int W[MAX_VERTICES];         // Set of visited vertices (W)

    // Step 1: Initialize distances and visited array
    for (int i = 0; i < V; i++) {
        distance[i] = INF;
        visited[i] = 0;
    }
    distance[source] = 0;
    
    // Step 2: Add the source vertex to W
    W[0] = source;
    visited[source] = 1;
    
    // Step 3: Start the loop to find the shortest paths
    for (int count = 0; count < V - 1; count++) {
        // Step 4: Find the vertex with the smallest distance that hasn't been visited yet
        int u = minDistance(distance, visited, V);
        
        // Mark the vertex u as visited
        visited[u] = 1;
        
        // Step 5: Update the shortest distance for all unvisited neighbors of u
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] != INF && distance[u] != INF && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }
    
    // Step 6: Output the shortest distances from the source
    printf("Shortest distances from vertex %d:\n", source);
    for (int i = 0; i < V; i++) {
        if (distance[i] == INF) {
            printf("Vertex %d is unreachable\n", i);
        } else {
            printf("Distance to vertex %d is %d\n", i, distance[i]);
        }
    }
}

int main() {
    int V, E, u, v, weight, source;
    
    // Input the number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);
    
    int graph[MAX_VERTICES][MAX_VERTICES];
    
    // Initialize the graph with INF
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = INF;
        }
    }
    
    // Input the edges and their weights
    printf("Enter the edges (u, v, weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &u, &v, &weight);
        graph[u][v] = weight;
        graph[v][u] = weight; // For undirected graphs, remove this line for directed graphs
    }
    
    // Input the source vertex
    printf("Enter the source vertex: ");
    scanf("%d", &source);
    
    // Call Dijkstra's algorithm to find the shortest path
    Dijkstra(graph, V, source);
    
    return 0;
}






void APSP(void)
{
    int i, j, k;
    int A[MAX][MAX], C[MAX][MAX];

    // Αντιγραφή της μήτρας C στην A
    for (i = 0; i <= MAX - 1; i++)
        for (j = 0; j <= MAX - 1; j++)
            A[i][j] = C[i][j];

    // Εκτέλεση του αλγορίθμου Floyd-Warshall για να βρούμε το APSP
    for (k = 0; k <= MAX - 1; k++)
        for (i = 0; i <= MAX - 1; i++)
            for (j = 0; j <= MAX - 1; j++)
                if (A[i][k] + A[k][j] < A[i][j])
                    A[i][j] = A[i][k] + A[k][j];
}



void TransitiveClosure(void)
{
    int i, j, k;
    int A[MAX][MAX], C[MAX][MAX];

    // Αντιγραφή της μήτρας C στην A
    for (i = 0; i <= MAX - 1; i++)
        for (j = 0; j <= MAX - 1; j++)
            A[i][j] = C[i][j];

    // Εκτέλεση του αλγορίθμου Warshall για υπολογισμό της μεταβατικής κλειστότητας
    for (k = 0; k <= MAX - 1; k++)
        for (i = 0; i <= MAX - 1; i++)
            for (j = 0; j <= MAX - 1; j++)
                if (!A[i][j])
                    A[i][j] = A[i][k] && A[k][j];
}



















```