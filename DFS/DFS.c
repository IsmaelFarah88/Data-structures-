#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int adjMatrix[MAX][MAX];
bool visited[MAX];
int numVertices;

void dfs(int vertex) {
    printf("%d ", vertex);
    visited[vertex] = true;

    for (int i = 0; i < numVertices; i++) {
        if (adjMatrix[vertex][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    int numEdges, u, v;

    scanf("%d %d", &numVertices, &numEdges);

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            adjMatrix[i][j] = 0;
        }
        visited[i] = false;
    }

    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d", &u, &v);
        adjMatrix[u][v] = 1;
    }

    dfs(0);

    return 0;
}
