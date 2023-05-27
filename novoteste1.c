#include <stdio.h>
#include <time.h>

void printHorasAtuais() {
    time_t tempoAtual;
    struct tm *infoTempo;
    char buffer[80];

    time(&tempoAtual);
    infoTempo = localtime(&tempoAtual);

    strftime(buffer, sizeof(buffer), "%H:%M:%S", infoTempo);
    printf("Horas atuais: %s\n", buffer);
}

int main() {
    printHorasAtuais();
    return 0;
}