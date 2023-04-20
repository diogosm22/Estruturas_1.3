/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "executavel.c"

int associar_cliente_meio(int codigo, int NIF, Meio* meios, Cliente* clientes) {
    
    Meio* current_meio = meios;
    while (current_meio != NULL) {
        if (current_meio->codigo == codigo) {
            break;
        }
        current_meio = current_meio->seguinte;
    }

    // Find the client with the given NIF.
    Cliente* current_cliente = clientes;
    while (current_cliente != NULL) {
        if (current_cliente->NIF == NIF) {
            break;
        }
        current_cliente = current_cliente->seguinte;
    }

    // Check if both meio and client exist.
    if (current_meio == NULL || current_cliente == NULL) {
        printf("Nao foi possivel encontrar Meio/Cliente.\n");
        return;
    }

    // Check if the meio is already associated with a client.
    if (current_meio->estado == 2) {
        printf("Meio ja se encontra associado.\n");
        return;
    }

    // Update the meio's estado value and print a message to the console.
    current_meio->estado = 2;
    printf("Associacao entre Meio %d e Cliente %d realizada.\n", codigo, NIF);

    // Open the file for writing in append mode.
    FILE* association_file = fopen("associacoes.txt", "a");
    if (association_file == NULL) {
        printf("Erro ao abrir ficheiro.\n");
        return;
    }

    // Write the association information to the file and close the file.
    fprintf(association_file, "Meio %d associado ao Cliente %d.\n", codigo, NIF);
    fclose(association_file);
}

void pedir_associacao(Meio* meios, Cliente* clientes) 
{
	//Meio* meios = NULL;
    //Cliente* clientes = NULL;
    int codigo, NIF;
    printf("Introduza o codigo do meio que pretende alugar: ");
    scanf("%d", &codigo);
    printf("Introduza o NIF do cliente: ");
    scanf("%d", &NIF);

    int result = associar_cliente_meio(codigo, NIF, meios, clientes);
    if (result == 1) 
	{
        printf("Associacao efetuada com sucesso!\n");
    }
	else 
	{
        printf("Associacao falhou.\n");
    }
}

void realizar_associacao()
{
	Meio* meios = NULL;
    Cliente* clientes = NULL;
	meios=lerMeios();
	clientes=lerCliente();
	pedir_associacao(meios,clientes);
}

int remover_associacao(int codigo, int NIF, Meio* meios, Cliente* clientes) {
    Meio* current_meio = meios;
    while (current_meio != NULL) {
        if (current_meio->codigo == codigo) {
            break;
        }
        current_meio = current_meio->seguinte;
    }

    Cliente* current_cliente = clientes;
    while (current_cliente != NULL) {
        if (current_cliente->NIF == NIF) {
            break;
        }
        current_cliente = current_cliente->seguinte;
    }

    if (current_meio == NULL || current_cliente == NULL) {
        return 0;
    }

    if (current_meio->estado == 2) {
        current_meio->estado = 1;
        return 1;
    }

    return 0;
}*/