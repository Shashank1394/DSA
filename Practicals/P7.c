#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

typedef struct Graph {
    int numVertices;
    int adjMatrix[MAX][MAX];
    bool visited[MAX];
    bool isDirected;
} Graph;

Graph* createGraph(int vertices, bool isDirected) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->isDirected = isDirected;

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
        graph->visited[i] = false;
    }
    return graph;
}

void addEdges(Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    if (!graph->isDirected) {
        graph->adjMatrix[dest][src] = 1;
    }
}

void DFS(Graph* graph, int vertex) {
    graph->visited[vertex] = true;
    printf("%d ", vertex);

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[vertex][i] == 1 && !graph->visited[i]) {
            DFS(graph, i);
        }
    }
}

typedef struct Queue {
    int items[MAX];
    int front, rear;
} Queue;

Queue* createQueue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

bool isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX - 1) {
        printf("Queue is full\n");
    } else {
        if (q->front == -1) q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

void BFS(Graph* graph, int startVertex) {
    Queue* q = createQueue();

    graph->visited[startVertex] = true;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !graph->visited[i]) {
                graph->visited[i] = true;
                enqueue(q, i);
            }
        }
    }
}

void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = false;
    }
}

int main() {
    int vertices, edges;
    bool isDirected;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Is the graph directed? (1 for Yes, 0 for No): ");
    scanf("%d", (int*)&isDirected);

    Graph* graph = createGraph(vertices, isDirected);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (source & destination):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdges(graph, src, dest);
    }

    printf("Depth First Search starting from vertex 0:\n");
    DFS(graph, 0);
    printf("\n");

    resetVisited(graph);

    printf("Breadth First Search starting form vertex 0:\n");
    BFS(graph, 0);
    printf("\n");

    return 0;
}