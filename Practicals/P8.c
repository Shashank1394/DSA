#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 50

// Graph structure
typedef struct Graph {
    int numVertices;
    int adjMatrix[MAX][MAX];
    bool visited[MAX];
    bool isDirected;
} Graph;

// Function to create the graph
Graph* createGraph(int vertices, bool isDirected) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->isDirected = isDirected;

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = (i == j) ? 0 : INT_MAX; // Initialize adjacency matrix with INF, 0 for self loops
        }
        graph->visited[i] = false; // Initialize visited array to false
    }
    return graph;
}

// Function to add edges to the graph
void addEdges(Graph* graph, int src, int dest, int weight) {
    graph->adjMatrix[src][dest] = weight; // Add edge with given weight
    if (!graph->isDirected) {
        graph->adjMatrix[dest][src] = weight; // If undirected, add the reverse edge
    }
}

// Function to find the vertex with the minimum distance
int minDistance(int dist[], bool sptSet[], int numVertices) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < numVertices; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Dijkstra's algorithm to find the shortest path from the source vertex
void dijkstra(Graph* graph, int src) {
    int dist[MAX];
    bool sptSet[MAX]; // Shortest Path Tree (SPT) set
    int parent[MAX];   // To store the shortest path

    // Initialize all distances as INF and sptSet as false
    for (int i = 0; i < graph->numVertices; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1; // No parent initially
    }

    dist[src] = 0; // Distance to source is 0

    // Find the shortest path for all vertices
    for (int count = 0; count < graph->numVertices - 1; count++) {
        int u = minDistance(dist, sptSet, graph->numVertices); // Find the vertex with the minimum distance
        sptSet[u] = true; // Add it to the SPT set

        // Update dist[] for the adjacent vertices of the chosen vertex
        for (int v = 0; v < graph->numVertices; v++) {
            if (!sptSet[v] && graph->adjMatrix[u][v] != INT_MAX && dist[u] != INT_MAX &&
                dist[u] + graph->adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->adjMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the shortest distance and path from the source to each vertex
    printf("Vertex\tDistance from Source\tPath\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d\t\t%d\t\t", i, dist[i]);
        int j = i;
        while (parent[j] != -1) {
            printf("%d <- ", j);
            j = parent[j];
        }
        printf("%d\n", src);
    }
}

int main() {
    int vertices, edges;
    bool isDirected;

    // Take user input for the number of vertices
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    // Take user input for whether the graph is directed or not
    printf("Is the graph directed? (1 for Yes, 0 for No): ");
    scanf("%d", (int*)&isDirected);

    // Create the graph with the given number of vertices and graph type (directed/undirected)
    Graph* graph = createGraph(vertices, isDirected);

    // Take user input for the number of edges
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    // Take user input for each edge (source, destination, and weight)
    printf("Enter the edges (source, destination, weight):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdges(graph, src, dest, weight);
    }

    // Perform Dijkstra's algorithm starting from vertex 0
    printf("Dijkstra's Algorithm starting from vertex 0:\n");
    dijkstra(graph, 0);

    return 0;
}
