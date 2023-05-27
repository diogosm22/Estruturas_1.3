#include <stdio.h>

#define MAX 6
    int graph[MAX][MAX] = {
        {0, 0, 0, 0, 900, 0},
        {200, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 400, 0},
        {0, 0, 600, 0, 0, 1200},
        {900, 500, 400, 700, 0, 0},
        {0, 0, 0, 1200, 0, 0}
    };
    int raio;
    int suaLocalizacao;


void findConnections(int graph[MAX][MAX]) {
    int distances[MAX] = {0};
    int visited[MAX] = {0};
    int queue[MAX] = {0};
    int front = 0, rear = 0;

    int suaLocalizacao;
    do {
        printf("Introduza a sua localizacao (1-6): ");
        scanf("%d", &suaLocalizacao);
    } while (suaLocalizacao < 1 || suaLocalizacao > 6);

    int raio;
    printf("Introduza a distancia maxima que pretende percorrer (em metros): ");
    scanf("%d", &raio);

    distances[suaLocalizacao - 1] = 0;
    visited[suaLocalizacao - 1] = 1;
    queue[rear++] = suaLocalizacao - 1;

    printf("Localizacoes com meios disponiveis a pelo menos %d metros da sua localizacao (%d):\n", raio, suaLocalizacao);

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d \n", currentVertex + 1);
        for (int i = 0; i < MAX; i++) {
            int distance = distances[currentVertex] + graph[currentVertex][i];
            if (graph[currentVertex][i] != 0 && distance <= raio && !visited[i]) {
                distances[i] = distance;
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    printf("\n");
}

int main()
{
    findConnections(graph);
}