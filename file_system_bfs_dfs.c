#include <stdio.h>
#include <string.h>

#define MAX_NODES 50
#define NAME_LEN 100

int graph[MAX_NODES][MAX_NODES];
int visited[MAX_NODES];
int queue[MAX_NODES];
char names[MAX_NODES][NAME_LEN];
int n;

/* Breadth-First Search */
void BFS(int start, const char target[]) {
    int front = 0, rear = 0;
    int found = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("\nBFS Traversal: ");
    while (front < rear) {
        int current = queue[front++];
        printf("%s ", names[current]);

        if (strcmp(names[current], target) == 0)
            found = 1;

        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    printf("\nBFS Result: File/folder \"%s\" %s.\n",
           target, found ? "was found" : "was not found");
}

/* Depth-First Search */
void DFSUtil(int current, const char target[], int *found) {
    visited[current] = 1;
    printf("%s ", names[current]);

    if (strcmp(names[current], target) == 0)
        *found = 1;

    for (int i = 0; i < n; i++) {
        if (graph[current][i] == 1 && !visited[i])
            DFSUtil(i, target, found);
    }
}

void DFS(int start, const char target[]) {
    int found = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("\nDFS Traversal: ");
    DFSUtil(start, target, &found);

    printf("\nDFS Result: File/folder \"%s\" %s.\n",
           target, found ? "was found" : "was not found");
}

int main(void) {
    int start;
    char target[NAME_LEN];

    printf("FILE SYSTEM REPRESENTATION USING GRAPH\n");
    printf("--------------------------------------\n");

    printf("Enter number of files/folders (1-%d): ", MAX_NODES);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_NODES) {
        printf("Invalid number of nodes.\n");
        return 1;
    }

    printf("\nEnter names of files/folders (use one word per name):\n");
    for (int i = 0; i < n; i++) {
        printf("Node %d: ", i);
        scanf("%99s", names[i]);
    }

    printf("\nEnter the adjacency matrix (%d x %d; use 1 for a connection and 0 otherwise):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &graph[i][j]) != 1 ||
                (graph[i][j] != 0 && graph[i][j] != 1)) {
                printf("Invalid matrix value. Enter only 0 or 1.\n");
                return 1;
            }
        }
    }

    printf("\nEnter starting node index (0 to %d): ", n - 1);
    if (scanf("%d", &start) != 1 || start < 0 || start >= n) {
        printf("Invalid starting node.\n");
        return 1;
    }

    printf("Enter the file/folder name to search: ");
    scanf("%99s", target);

    printf("\nNode List:\n");
    for (int i = 0; i < n; i++)
        printf("%d: %s\n", i, names[i]);

    BFS(start, target);
    DFS(start, target);

    return 0;
}
