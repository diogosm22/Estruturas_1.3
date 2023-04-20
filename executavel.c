/* EM FALTA

Geolocalização / Associacao do cod do meio ao NIF / Ver saldo consoante o login realizado / 
Listagem dos meios disponiveis(removendo os que ja estao alugados)
Aperfeicoamente do ficheiro em termos de imports
Guardians foram utilizados neste ficheiro principal e programa não está devidamente estruturado atravez de imports devido a problemas
na compilação com o vscode ( a melhorar)

Alguns dados já vão inseridos, consultar TXT´s


Nota: Gestor apenas pode ser registado atravez do txt diretamente(lista nao ligada), de forma a apenas o admin registar gestores
Gestor padrao: username:1
			   password:1

Programa apenas aceita inputs do utilizador de NUMEROS INTEIROS !!!


*/

/*											DIOGO MACEDO A20392 EEC 1º ANO 												*/


#ifndef ficheiroClientes_c
#define ficheiroClientes_c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ficheiroClientes.c"

//#include "associarteste.c"


char usernameL1[20], passwordL1[20]; //variaveis utilizadas para gravar dados do Log in do Cliente, e futuramente utilizadas para 
									 //obter o saldo de cliente que efetuou o log in



/////////////////////////////////////////////////////////////// Estruturas ///////////////////////////////////////////////////////////7
struct Gestor{
	char username[20];
	char password[20];
	char nome[40];
    int NIF[9];
    float saldo;
    char morada; 
} Gestor;

typedef struct registo{
	int codigo; 
 	char tipo[50];
 	float bateria;
 	float autonomia;
 	char localizacao[50];
	int estado;
 	struct registo* seguinte;
} Meio;

Meio* inserirMeio(Meio* inicio, int cod, char tipo[], float bat, float aut, char localizacao[], int estado); // Inser��o de um novo registo
void listarMeios(Meio* inicio); // listar na consola o conte�do da lista ligada
int existeMeio(Meio* inicio, int codigo); // Determinar exist�ncia do 'codigo' na lista ligada 'inicio'
Meio* removerMeio(Meio* inicio, int cod); // Remover um meio a partir do seu c�digo
int guardarMeios(Meio* inicio);
Meio* lerMeios();

///////////////////////////////////////////////////////////////////////LISTAGENS/////////////////////////////////////////////////////

void apresentarMeioDecrescente() // funcao void utilizada para facilitar a chamada no menu
{
	Meio*meios=NULL;
	meios=lerMeios();
	listarAutonomiaDecrescente(meios);
}

void apresentarMeiosDisponivel() // funcao void utilizada para facilitar a chamada no menu
{
	Meio*meios=NULL;
	meios=lerMeios();
	listar_Meios_Disponiveis(meios);
}

void apresentarMeiosOcupados() // funcao void utilizada para facilitar a chamada no menu
{
	Meio*meios=NULL;
	meios=lerMeios();
	listar_Meios_Ocupados(meios);
}

void apresentarMeiosLocalizacao() // funcao void utilizada para facilitar a chamada no menu
{
	Meio*meios=NULL;
	meios=lerMeios();
	listarMeiosLocalizacao(meios);
}

void listarMeiosLocalizacao(Meio* inicio) //listagem de meios por localizacao especifica
{
    char localizacao[50];
    printf("Insira a localizacao desejada: ");
    scanf("%s", localizacao);
    Meio* local = inicio;
    int count = 0;
    while (local != NULL) {
        if (strcmp(local->localizacao, localizacao) == 0) {
            printf("\n\nEstado: %d\nCodigo: %d\nTipo: %s\nBateria: %.2f\nAutonomia: %.2f\nLocalizacao: %s\n\n",local->estado, local->codigo, local->tipo, local->bateria, local->autonomia, local->localizacao);
            count++;
        }
        local = local->seguinte;
    }
    if (count == 0) {
        printf("Nenhum registo encontrado para a localizacao inserida.\n");
    }
}

void listarAutonomiaDecrescente(Meio *lista) //listagem de meios por ordem decrescente de autonomia
{
  Meio *atual = lista;
  Meio *maiorAutonomia = lista;

  while(atual != NULL)
  {
    if(atual->autonomia > maiorAutonomia->autonomia) /// verificar isto
    {
      maiorAutonomia = atual;
    }
    atual = atual->seguinte;
  }

  // Imprimir os valores da estrutura
  Meio *temp = lista;
  while(temp != NULL)
  {
    printf("Estado: %d\nCodigo: %d\nTipo: %s \nBateria: %.2f %\nAutonomia: %.2f min\nLocalizacao: %s\n\n", maiorAutonomia->estado, maiorAutonomia->codigo, maiorAutonomia->tipo, maiorAutonomia->bateria, maiorAutonomia->autonomia, maiorAutonomia->localizacao);

    // Remover o meio de mobilidade com maior autonomia da lista
    Meio *anterior = NULL;
    Meio *proximo = lista;

    while(proximo != maiorAutonomia)
    {
      anterior = proximo;
      proximo = proximo->seguinte;
    }

    if(anterior == NULL)
    {
      lista = proximo->seguinte;
    }
    else
    {
      anterior->seguinte = proximo->seguinte;
    }

    free(maiorAutonomia);
    maiorAutonomia = lista;

    // Procurar pelo novo meio com maior autonomia
    atual = lista;
    while(atual != NULL)
    {
      if(atual->autonomia > maiorAutonomia->autonomia)
      {
        maiorAutonomia = atual;
      }
      atual = atual->seguinte;
    }

    temp = lista;
  }
}

void listarMeios(Meio * inicio) //listagem de meios por ordem de alteracao
{
	while (inicio != NULL)
	{
		printf("Estado: %d ; Codigo: %d ; Tipo: %s ; Bateria: %.2f % ; Autonomia: %.2f min; Localizacao: %s ;\n",inicio->estado,inicio->codigo,inicio->tipo, inicio->bateria, inicio->autonomia, inicio->localizacao);
		inicio = inicio->seguinte;
	}
}

void listar_Meios_Disponiveis(Meio * inicio) // listagem de meios sem associacao
{
	Meio* local = inicio;
	while (local != NULL)
 	{
		if(local->estado == 1)
		{
			printf("Estado: %d ; Codigo: %d ; Tipo: %s ; Bateria: %.2f%% ; Autonomia: %.2f min; Localizacao: %s ;\n",local->estado,local->codigo,local->tipo, local->bateria, local->autonomia, local->localizacao);		
		}
		local = local->seguinte;
 	}
}

void listar_Meios_Ocupados(Meio * inicio) // listagem de meios associados
{
	Meio* local = inicio;
	while (local != NULL)
 	{
		if(local->estado == 2)
		{
			printf("Estado: %d ; Codigo: %d ; Tipo: %s ; Bateria: %.2f%% ; Autonomia: %.2f min; Localizacao: %s ;\n",local->estado,local->codigo,local->tipo, local->bateria, local->autonomia, local->localizacao);		
		}
		local = local->seguinte;
 	}
}

//////////////////////////////////////////////////////////////// Saldo Cliente //////////////////////////////////////////////////////////

void adicionarSaldo(Cliente* inicio, char username[]) //Adicionar saldo cliente (deteta o username automaticamente)
{
    float valor;
    printf("Valor a adicionar: ");
    scanf("%f", &valor);

    while (inicio != NULL) 
    {
        if (strcmp(inicio->username, username) == 0) 
        {
            inicio->saldo += valor;
            return;
        }
        inicio = inicio->seguinte;
    }
    printf("Utilizador nao encontrado\n");
}

void printSaldo(Cliente* inicio, char username[]) //Apresenta o Saldo (deteta o username automaticamente)
{
    while (inicio != NULL) 
    {
        if (strcmp(inicio->username, username) == 0) 
        {
            printf("Saldo: %.2f\n", inicio->saldo);
            return;
        }
        inicio = inicio->seguinte;
    }
    printf("Utilizador nao encontrado\n");
}


/////////////////////////////////////////////////////////////// VERIFICACOES DE REPETICOES //////////////////////////////////////

int check_Username_C(char username[])//verificar a existencia do username ( para evitar usernames repetidos)
{
	FILE *txtCliente;
	char line[40];
	char *tokenU1; 
	
	txtCliente = fopen("DadosCliente.txt", "r");
	while(fgets(line, sizeof(line), txtCliente))
	{
		tokenU1 = strtok(line, ";"); //Divide a string (linha) em "tokens", esses separados por um espaço(" ").
		if(strcmp(tokenU1, username) == 0)
		{
			fclose(txtCliente);
			return 1;
		}
	}
	fclose(txtCliente);
	return 0;
}

int check_NIF_C(int NIF) // verificar a existencia de NIF ( para evitar NIF repetidos)
{
	FILE *txtCliente;
	char line[40];
	char *tokenNIF;
	int file_int;
	txtCliente = fopen("DadosCliente.txt", "r");
	while(fgets(line, sizeof(line), txtCliente))
	{
		tokenNIF = strtok(line, ";");
		sscanf(tokenNIF, "%d", &file_int);
		if(file_int == NIF)
		{
			fclose(txtCliente);
			return 1;
		}
	}
	fclose(txtCliente);
	return 0;
}


/////////////////////////////////////////////////////////////////// LOGIN/REGISTAR //////////////////////////////////////////

void Login_Gestor() // nao existe registo de gestor, por isso tem apenas a parte do login
{
	FILE *txtGestor;
	char usernameL2[20], passwordL2[20];
	char line[40];
	int loginValid2 = 0;
	int resultado2;
	char *tokenG1;
	txtGestor = fopen("DadosGestor.txt", "r");
	printf("Username: ");
	scanf("%s", usernameL2);
	printf("Password: ");
	scanf("%s", passwordL2);
	while(fgets(line, sizeof(line), txtGestor))
	{
		tokenG1 = strtok(line, " ");
		if(strcmp(tokenG1, usernameL2) == 0)
		{
			if(strcmp(tokenG1,passwordL2)==0)
			{
				fclose(txtGestor);
				resultado2 = 1;
				break;
			}

		}
	}

	if(resultado2 == 1)
	{
		printf("\n\nLogin efetuado com sucesso!\n");
		fclose(txtGestor);
		Menu_Opcoes_Gestor();
	}

	else if (loginValid2 !=1 )
	{
		printf("\n\nNome de utilizador ou palavra passe incorretos!\n");
		fclose(txtGestor);
		return Login_Gestor();
	}
}

int opregistarclienteC()// Menu de escolhas ( Login/Registar ) para clientes
{
	int op;
	printf("\n\nMenu Cliente\n");
	printf("1. Login\n");
	printf("2. Registar\n");
	printf("9. Voltar\n");
	printf("0. Sair\n");
	printf("\nOpcao: ");
	scanf("%d", &op);
	return(op);
	printf("\n\n");
}

int menu_do_cliente() // Registo/Login de Clientes
{
	Cliente* clienteC = NULL; // Lista ligada vazia 
	int op, NIF, NIFexiste, usernameExiste, resultado1;
	int loginValid1 = 0;
	char username[20], password[20], line[40];
	char *tokenC1;
	float saldo;
	FILE *txtCliente;
	do
	{
		op=opregistarclienteC();
		switch (op)
		{
			case 1:
				txtCliente = fopen("DadosCliente.txt", "r");
				printf("Username: ");
				scanf("%s", usernameL1);
				printf("Password: ");
				scanf("%s", passwordL1);
				while(fgets(line, sizeof(line), txtCliente))
				{
					tokenC1 = strtok(line, ";"); // vai linha a linha ao ficheiro txt, divide cada frase separada por ; e compara
					if(strcmp(tokenC1, usernameL1) == 0)
					{
						if(strcmp(tokenC1,passwordL1)==0)
						{
							fclose(txtCliente);
							resultado1 = 1;
							break;
						}
					}
				}
				if(resultado1 == 1)
				{
					printf("\n\nLogin efetuado com sucesso!\n");
					fclose(txtCliente);
					Menu_Opcoes_Cliente();
				}
				else if (loginValid1 !=1 )
				{
					printf("\n\nNome de utilizador ou palavra passe incorretos!\n");
					fclose(txtCliente);
					return menu_do_cliente();
				};
				break;

			case 2:
				printf("\nUsername: ");
				scanf("%s",username);
				usernameExiste = check_Username_C(username);
				if(usernameExiste == 1)
				{
					printf("\n\nNome de utilizador indisponivel\n\n");
					return menu_do_cliente();
				}

				else
				{
					scanf("%*c"); 
					printf("Password: ");
					scanf("%s", password);
					scanf("%*c");
					printf("NIF: ");
					scanf("%d",&NIF);
					NIFexiste = check_NIF_C(NIF);
					if(NIFexiste == 1)
					{
						printf("\n\nNIF ja se encontra atribuido.\n\n");
						return menu_do_cliente();	
					}
					else
					{
						printf("Saldo: ");
						scanf("%f",&saldo);
						clienteC = lerCliente();			
						clienteC = inserirCliente(clienteC,username,password,NIF,saldo);
						clienteC = guardarCliente(clienteC);
						printf("\n\nCliente Registado!\n"); //onde regista o cliente
						break;
					}
				}

			case 9:
				mainMenu();
				break;
			case 0:
				exit(1);
				break;
			default:
				printf("\n\nOpcao invalida\n\n");
				return menu_do_cliente();
				break;
		}
	}
	while(op!=0);
	return (0);
}

/////////////////////////////////////////////////////////////////// Funcoes principais /////////////////////////////////////////////////

int guardarMeios(Meio* inicio)//funcao usada para guardar os meios em txt
{FILE* fp;
    fp = fopen("meios.txt", "w");
    if (fp != NULL) {
        Meio* aux = inicio;
        while (aux != NULL) {
            fprintf(fp, "%d;%.2f;%.2f;%s;%s;%d;\n", aux->codigo, aux->bateria, aux->autonomia, aux->tipo, aux->localizacao, aux->estado);
            aux = aux->seguinte;
        }
        fclose(fp);
        return 1;
    } else {
        return 0;
    }
}

Meio* lerMeios() // funcao usada para ler meios ( manter meios atualizados)
{ FILE* fp;
    int cod;
    float bat, aut;
    char tipo[50], localizacao[50];
	int estado;
    Meio* aux = NULL;
    fp = fopen("meios.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%d;%f;%f;%[^;];%[^;];%d;\n", &cod, &bat, &aut, tipo, localizacao, &estado) == 6) //confirma se existem os 5 meios
		{
            aux = inserirMeio(aux, cod, tipo, bat, aut, localizacao, estado);
        }
        fclose(fp);
    }
    return aux;
}

Meio* inserirMeio(Meio * inicio, int cod, char tipo[], float bat, float aut,char localizacao[],int estado)// funcao usada para inserir novos meios
{if (!existeMeio(inicio, cod))
 {Meio * novo = malloc(sizeof(struct registo));
  if (novo != NULL)
  {novo->codigo = cod;
   strcpy(novo->tipo,tipo);
   novo->bateria = bat;
   novo->autonomia = aut;
   strcpy(novo->localizacao,localizacao);
   novo->estado = estado;
   novo->seguinte = inicio;
   return(novo);
  }
 } else return(inicio);
}

int existeMeio(Meio* inicio, int cod)// Funcao usada para verificar se ja existia esse meio ao inserir um novo
{while(inicio!=NULL)
  {if (inicio->codigo == cod) return(1);
   inicio = inicio->seguinte;
  }
 return(0);
}

Meio* removerMeio(Meio* inicio, int cod) //remover um meio atraves do seu codigo
{
 Meio *anterior=inicio, *atual=inicio, *aux;

 if (atual==NULL) return(NULL);
 else if (atual->codigo == cod) // remo��o do 1� registo
 {aux = atual->seguinte;
  free(atual);
  return(aux);
 }
 else
 {while ((atual!=NULL)&&(atual->codigo!=cod)) 
  {anterior = atual;
   atual = atual->seguinte;
  }
  if (atual==NULL) return(inicio);
  else
  {anterior->seguinte = atual->seguinte;
   free(atual);
   return(inicio);
  }
 }
}

/////////////////////////////////////////////////////////////// MENUS /////////////////////////////////////////////////

int mainMenu()// Menu principal
{
	char optionCG;
	printf("\nCliente ou Gestor?\n");
	printf("1. Cliente\n");
	printf("2. Gestor\n");
	printf("0. Sair\n");
	printf("\nOpcao: ");
	scanf("%d", &optionCG);
	switch (optionCG)
	{
		case 1:
			menu_do_cliente();
			break;
		case 2:
			menu_do_gestor();
			break;
		case 0:
			exit(1);
			break;
		default:
			printf("\n\nOpcao invalida\n\n");
			return mainMenu();
			break;
	}
}

void menu_do_gestor() // Menu Login do gestor
{
	int optionG;
	printf("\nGestor\n");
	printf("1. Login\n");
	printf("9. Voltar\n");
	printf("0. Sair\n");
	printf("\nOpcao: ");
	scanf("%d", &optionG);
	switch (optionG)
	{
		case 1:
			Login_Gestor();
			break;
		case 9:
			mainMenu();
			break;
		case 0:
			exit(1);
			break;
		default:
			printf("\n\nOpcao invalida\n");
			menu_do_gestor();
			break;
	}
}

void Menu_Opcoes_Gestor() // Menu das opcoes do gestor
{
	int optionMG;
	printf("\nMenu Gestor!\n");
	printf("1. Gerir Meios\n");
	printf("2. Consultar Dados Clientes\n");
	printf("3. Gerir dados Clientes\n");
	printf("4. Gerir Associacoes\n");
	printf("0. Sair\n");
	printf("9. Voltar\n\n");
	printf("Opcao: ");
	scanf("%d", &optionMG);
	printf("\n\n");

	switch (optionMG)
	{
		case 1:
            Menu_Gerenciar_Meios2();
			break;

		case 2:
			Consultar_Dados_Clientes();
			break;
		case 3:
			Menu_Modificar_ClientesG();
			break;

		case 4:
			//realizar_associacao();
			printf("Indisponivel");
			break;	
			
		case 0:
			exit(1);
			break;

		case 9:
			return Menu_Opcoes_Gestor();

		default:
			printf("\n\nOpcao invalida\n\n");
			return Menu_Opcoes_Gestor();
	
	}

}

int Menu_Gerenciar_Meios1() //Menu das opcoes do gestor em relacao a meios de mobilidade
{
	int op;
	printf("\n\nMenu Gestor\n\n");
	printf("1. Inserir meio\n");
	printf("2. Listar meios por ordem de atualizacao\n");
	printf("3. Visualizar meios disponiveis ");
	printf("4. Visualizar meios ocupados ");
	printf("5. Visualizar meios por ordem decrescente de autonomia");
	printf("6. Pesquisar meio por localizacao\n");
	printf("7. Remover meio\n");
	printf("0. Sair\n");
	printf("9. Voltar\n\n");
	printf("Opcao:");
	scanf("%d",&op);
	printf("\n\n");
	return(op);
}

int Menu_Gerenciar_Meios2() //Gerir Meios de mobilidade 
{
	Meio* meios = NULL; 
	Meio* inicio = NULL ;
	int op, cod, estado;
	float bat, aut;
	char tipo[50],localizacao[50];
 	do
	{
		op = Menu_Gerenciar_Meios1();
		switch(op)
		{
			case 1: 
				estado=1;
				meios = lerMeios();
				printf("Codigo?\n");
				scanf("%d",&cod);
				printf("Tipo\n");
				scanf("%s",tipo);
				scanf("%*c"); 
				printf("Nivel da bateria?\n");
				scanf("%f",&bat);
				printf("Autonomia\n");
				scanf("%f",&aut);
				printf("Localizacao:\n");
				scanf("%s",localizacao);
				scanf("%*c");
				meios = inserirMeio(meios,cod,tipo,bat,aut,localizacao,estado);
				guardarMeios(meios);
				break;
			case 2: 
				meios = lerMeios();
				listarMeios(meios);
				break; //listagem por ordem de criação para o gestor

			case 3:
				apresentarMeiosDisponivel();
				break;

			case 4:
				apresentarMeiosOcupados();
				break;

			case 5:
				apresentarMeioDecrescente();
				break;

			case 6:
				apresentarMeiosLocalizacao(meios);
				break;

			case 7: 
				meios = lerMeios();
				printf("Codigo do meio de mobilidade a remover?\n");
				scanf("%d",&cod);
				meios = removerMeio(meios, cod);
				guardarMeios(meios);
				break;
			case 9: 
				Menu_Opcoes_Gestor(); 
				break;
		}
	} while (op!=0);


	return(0);
}

void Menu_Opcoes_Cliente() // Menu das opcoes do cliente
{
	Cliente* clienteC = NULL;
    Meio* meios = NULL;
	int NIF, codigo;
	int optionMC;
	printf("\nBem vindo!\n");	
	printf("1. Visualizar meios de mobilidade disponiveis\n");
	printf("2. Pesquisar meio por localizacao\n");
	printf("3. Alugar\n");
	printf("4. Visualizar meios disponiveis\n");
	printf("5. Visualizar meios ocupados\n");
	printf("6. Consultar Saldo\n");
	printf("7. Adicionar Saldo\n");
	printf("8. Visualizar todos os meios de mobilidade\n");
	printf("0. Sair\n\n");
	printf("Opcao: ");
	scanf("%d", &optionMC);
	printf("\n\n");

	switch (optionMC)
	{
		case 1:
			printf("Em atualizacao");
			return Menu_Opcoes_Cliente();
			
		case 2:
			apresentarMeiosLocalizacao(meios);
			return Menu_Opcoes_Cliente();
		
		case 3:
   			printf("Indisponivel");
			//realizar_associacao();
			return Menu_Opcoes_Cliente();

		case 4:		
			apresentarMeiosDisponivel(meios);
			return Menu_Opcoes_Cliente();
			
		case 5:	//return Menu_Opcoes_Cliente();
			apresentarMeiosOcupados(meios);
			return Menu_Opcoes_Cliente();

		case 6:
			clienteC = lerCliente();
			printSaldo(clienteC, usernameL1);
			return Menu_Opcoes_Cliente();
			
		case 7:
			clienteC = lerCliente();
			adicionarSaldo(clienteC, usernameL1);
			clienteC = guardarCliente(clienteC);
			return Menu_Opcoes_Cliente();
			
		case 8:
			apresentarMeioDecrescente(meios);
			return Menu_Opcoes_Cliente();
			
		case 0:
			exit(1);
			break;
	
		default:
			printf("\n\nOpcao invalida\n\n");
			return Menu_Opcoes_Cliente();
	}
}

int main()
{
    mainMenu();
}

#endif //Guardian