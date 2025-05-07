#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 100

int graph[MAX][MAX];   // adjacency matrix
int visited[MAX];      // shared visited array for DFS
int V;                 // number of vertices

// Parallel BFS
void parallelBFS(int start) {
    int queue[MAX], front = 0, rear = 0;
    int localVisited[MAX] = {0};  // used locally to avoid race

    localVisited[start] = 1;
    queue[rear++] = start;

    printf("Parallel BFS starting from node %d: ", start);

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        #pragma omp parallel for
        for (int i = 0; i < V; i++) {
            if (graph[current][i] && !localVisited[i]) {
                #pragma omp critical
                {
                    if (!localVisited[i]) {
                        localVisited[i] = 1;
                        queue[rear++] = i;
                    }
                }
            }
        }
    }

    printf("\n");
}

// Parallel DFS utility
void parallelDFSUtil(int node) {
    #pragma omp critical
    {
        printf("%d ", node);
    }
    visited[node] = 1;

    #pragma omp parallel for
    for (int i = 0; i < V; i++) {
        if (graph[node][i] && !visited[i]) {
            #pragma omp task
            parallelDFSUtil(i);
        }
    }
}

// Parallel DFS
void parallelDFS(int start) {
    for (int i = 0; i < V; i++)
        visited[i] = 0;

    printf("Parallel DFS starting from node %d: ", start);

    #pragma omp parallel
    {
        #pragma omp single
        {
            parallelDFSUtil(start);
        }
    }

    printf("\n");
}

int main() {
    V = 6; // Number of vertices

    // Sample undirected graph using adjacency matrix
    graph[0][1] = graph[1][0] = 1;
    graph[0][2] = graph[2][0] = 1;
    graph[1][3] = graph[3][1] = 1;
    graph[1][4] = graph[4][1] = 1;
    graph[2][5] = graph[5][2] = 1;

    parallelBFS(0);
    parallelDFS(0);

    return 0;
}
//gcc 01_BFS_DFS.c
//.\a.exe