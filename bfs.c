#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int queue[MAX], front = -1, rear = -1;
int visited[MAX];
char vertices[MAX][10];

void enqueue(int value) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = value;
}

int dequeue() {
    if (front == -1 || front > rear) return -1;
    return queue[front++];
}

int getIndex(char name[], int n) {
    for (int i = 0; i < n; i++)
        if (strcmp(vertices[i], name) == 0) return i;
    return -1;
}

void bfs(int adj[MAX][MAX], int start, int n) {
    enqueue(start);
    visited[start] = 1;
    printf("\nBFS Traversal: ");
    while (front <= rear) {
        int current = dequeue();
        printf("%s ", vertices[current]);
        for (int i = 0; i < n; i++)
            if (adj[current][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
    }
    printf("\n");
}

int main() {
    int n, adj[MAX][MAX];
    char startName[10];

    printf("Enter Number Of Vertices: ");
    scanf("%d", &n);

    printf("Enter Vertices Names: ");
    for (int i = 0; i < n; i++)
        scanf("%s", vertices[i]);

    printf("\nEnter Adjacency Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);

    printf("\nEnter Starting Vertex Name: ");
    scanf("%s", startName);

    int startIndex = getIndex(startName, n);
    if (startIndex == -1) {
        printf("Invalid Starting Vertex!\n");
        return 0;
    }

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    bfs(adj, startIndex, n);
    return 0;
}
