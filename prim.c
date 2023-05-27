#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 6 // número de vértices do grafo

// Function to find the vertex with the minimum distance
int minDistance(int dist[], int visited[]) {
    int min = INT_MAX, min_index;

    for (int i = 0; i < MAX; i++) {
        if (visited[i] == 0 && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }

    return min_index;
}

// Function to display all distances from a given vertex
void todas_distancias_um_ponto(int dist[]) {
    printf("Localizacao \t Distancia da sua localizacao \n");
    for (int i = 0; i < MAX; i++) {
        printf("     %d \t\t\t  %d m\n", i+1, dist[i]);
    }
}

// Dijkstra's algorithm to find the shortest distances from a given starting vertex
void dijkstra(int graph[MAX][MAX], int start, int max_distance) {
    int dist[MAX];
    int visited[MAX];

    // Initialize distances and visited array
    for (int i = 0; i < MAX; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[start-1] = 0; // Set distance of the starting vertex as 0

    for (int i = 0; i < MAX-1; i++) {
        int u = minDistance(dist, visited);
        visited[u] = 1; // Mark the vertex as visited

        // Update distances of the adjacent vertices
        for (int v = 0; v < MAX; v++) {
            if (graph[u][v] != 0 && visited[v] == 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Display only vertices within the given max_distance
    printf("Localizações com meios disponíveis a menos de %d metros:\n", max_distance);
    for (int i = 0; i < MAX; i++) {
        if (dist[i] <= max_distance) {
            printf("%d ", i+1);
        }
    }
    printf("\n");
}

void distancias() {
    int graph[MAX][MAX] = {
        {0, 0, 0, 0, 900, 0},
        {200, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 400, 0},
        {0, 0, 600, 0, 0, 1200},
        {900, 500, 400, 700, 0, 0},
        {0, 0, 0, 1200, 0, 0}
    };

    int start, max_distance;

    // Get input from the user
    printf("Introduza o vertice inicial (1-6): ");
    scanf("%d", &start);
    printf("Introduza a distancia maxima: ");
    scanf("%d", &max_distance);

    // Call Dijkstra's algorithm to find the distances
    dijkstra(graph, start, max_distance);
}

int main() {
    distancias();
    return 0;
}








/*#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 6 // número de vértices do grafo

int minDistance(int dist[], int visited[]) {
    int min = INT_MAX, min_index;

    for (int i = 0; i < MAX; i++) {
        if (visited[i] == 0 && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }

    return min_index;
}

void todas_distancias_um_ponto(int dist[]) {
    printf("Localizacao \t Distancia da sua localizacao \n");
    for (int i = 0; i < MAX; i++) {
        printf("     %d \t\t\t  %d m\n", i+1, dist[i]);
    }
}

void dijkstra(int graph[MAX][MAX], int start) {
    int dist[MAX];
    int visited[MAX];

    for (int i = 0; i < MAX; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[start-1] = 0;

    for (int i = 0; i < MAX-1; i++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;

        for (int v = 0; v < MAX; v++) {
            if (graph[u][v] != 0 && visited[v] == 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    todas_distancias_um_ponto(dist);
}

void distancias() {
    int graph[MAX][MAX] = {
        {0, 0, 0, 0, 900, 0},
        {200, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 400, 0},
        {0, 0, 600, 0, 0, 1200},
        {900, 500, 400, 700, 0, 0},
        {0, 0, 0, 1200, 0, 0}
    };

    int start;
    printf("Introduza o vertice inicial (1-6): ");
    scanf("%d", &start);
    dijkstra(graph, start);

    return 0;
}

int main()
{
    distancias();
}*/