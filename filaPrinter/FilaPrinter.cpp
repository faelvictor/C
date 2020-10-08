// ** RAFAEL VICTOR R. DE SOUSA ** //			
#include <stdio.h>		// Biblioteca de entrada e saida de dados	 
#include <stdlib.h> 	// Biblioteca de prop�sito geral
#include <locale.h>		// Biblioteca de acentua��o de caracters
#include <string.h>		// Biblioteca de manipula��o de string

#define TAMMAX 15		 // Tamanho m�ximo da fila 

typedef struct tipoImpressao imp;	// Definindo um novo tipo de dado e um alias para a estrutura
struct tipoImpressao{
	int ID;							// Identificador para cada arquivo
	char nomeArquivo[25];			// Nome do arquivo
	char formatoArquivo[5];			// Formato do arquivo
	int quantidadePaginas;			// Quantidade de paginas 
	struct tipoImpressao *prox;		// Ponteiro pr�ximo
};

// Assinatura das fun�oes
void enviaImpressao(imp **inicio, imp **fim);
void cancelaImpressao(imp **inicio, imp **fim);
void consomeImpressao(imp **inicio, imp **fim);
void statusFila(imp *inicio);
void zeraFila(imp **inicio, imp **fim);
int imprimeMenu();


int tam;					// Vari�vel global para controlar o tamanho maximo da fila

int main (){
	setlocale (LC_ALL, "");		// Configurando para aceitar qualquer tipo de acentua��o 
	
	imp *inicio = NULL;		// Ponteiros inicio e fim do tipo da estrutura
	imp *fim = NULL;		// inicializando a fila em NULL
	
	int opcao;				// Vari�vel local para controle do switch-case
	
	
	do{
		system("CLS");
		opcao = imprimeMenu();		// Menu principal
		
		switch(opcao){
			case 1: {
					enviaImpressao(&inicio, &fim);
					system("PAUSE");
					break;
				}
			case 2:{
					cancelaImpressao(&inicio, &fim);		
					system("PAUSE");
					break;
				}
			case 3:{
					consomeImpressao(&inicio, &fim);
					system("PAUSE");
					break;
			}
			case 4:{
					statusFila(inicio);
					system("PAUSE");
					break;
				}
			case 5:{
				zeraFila(&inicio, &fim);
				system("PAUSE");
				break;
			}
			case 6:{
				 printf("\nFinizando programa...\n\n");
				 break;
			}
		}
	}while(opcao != 6);
	
	system("PAUSE");
	return 0;
}


void enviaImpressao(imp **inicio, imp **fim){
	if(tam == TAMMAX){							 // Se fila estiver cheia...
		printf("\nFila est� cheia! Volte logo\n\n");
		return;
	}
    
	imp *novo = (imp*) malloc(sizeof(imp));		// Aloca dinamicamente o novo texto para impress�o 
	
	if(!novo){									// Se n�o conseguiu alocar dinamicamente...
        printf("Heap overflow!\n");
        return;          
    }
	
	if(novo){ 									// Se conseguiu alocar dinamicamente...
			printf("\nC�digo da impress�o: ");
			fflush(stdin);
			scanf("%d", &novo->ID);
			printf("Nome do arquivo: ");
			fflush(stdin);
			scanf("%s", novo->nomeArquivo);
			printf("Formato do arquivo (.pdf .word .txt .jpeg .png...):  ");
			fflush(stdin);
			scanf("%s", novo->formatoArquivo);
			printf("Quantidade de paginas: ");
			fflush(stdin);
			scanf("%d", &novo->quantidadePaginas);
			printf("\nArquivo inserido na fila com sucesso!\n");
		
		novo->prox = NULL;				// Ponteiro pr�ximo do novo elemento aponta para NULL, pois queremos inserir ao final da fila
	
		if(!(*inicio) && !(*fim)){		// Se a fila estiver vazia...
			*inicio = novo;				// Ponteiro inicio aponta para novo texto
			*fim = novo;				// Ponteiro fim aponta para o novo texto
		}else{							// Se a fila tiver alguem...
			(*fim)->prox = novo;
			*fim = novo;				// Fim aponta para o rec�m chegado
		}
		tam++;							// Incremento +1 no tamanho da fila
	}
	
	
	printf("\n");
	return;
}


void cancelaImpressao(imp **inicio, imp **fim){
	int codigo;								// Vari�vel local para guardar c�digo a ser removido 
	imp *ant,*atual;						// Ponteiro anterior e atual para controlar minha lista, do tipo da estrutura
	
	printf("Digite o c�digo da impress�o para remove-la da fila: ");
	fflush(stdin);
	scanf("%d",&codigo);
	
	if(*inicio == NULL){				// Se fila estiver vazia...
		printf("\nFila vazia, imposs�vel remover! \n\n");
		return;
	}else{								// Fila possui algo...
		ant = *inicio;					// Anterior aponta para inicio da fila
		atual = *inicio;				// Atual aponta para inicio da fila
		while(atual != NULL){ 			// Lar�o while para localizar o c�digo 		
			if(atual->ID == codigo){	// Se elemento for encontrado
				if(atual == *inicio){	// Se o c�digo estiver no inicio...
					*inicio = atual->prox;	// Ando com inicio para o segundo n� 
					free(atual);			// Libero mem�ria
					printf("Arquivo de c�digo %d removido com sucesso!\n\n", codigo);
					tam--;				// Diminui tamanho da fila
					break;
				}else{
					if(atual == *fim){ 	// Se o c�digo estiver no final...
						*fim = ant;		// Ponteiro fim aponta para o anterior 
					}
					ant->prox = atual->prox; // Refaz o encdeamento
					free(atual);			// Libera mem�ria 
					printf("Arquivo de c�digo %d removido com sucesso!\n\n", codigo);
					tam--;      			// Diminui tamanho da fila
					break;
				}
			}else{					  // Se eu n�o encontro o elemento...
				ant = atual;		  // Anterior recebe o atual
				atual = atual->prox;  // Atual recebe o proximo
			}
		}
	}
	
	return;
}


void consomeImpressao(imp **inicio, imp **fim){
	
	char guardaArquivo[25];			// Vari�vel para guardar nome do arquivo 
	int guardaPaginas;				// Vari�vel para guardar o n�mero de paginas
	char guardaFormato[5];			// Vari�vel para guardar o formato do arquivo
	
	if(!(*inicio) && !(*fim)){						// Se fila estiver vazia...
		printf("\nFila vazia, impossivel imprimir.\n\n");	
		
		return;
	}
	
	imp *aux = *inicio;
	
	strcpy(guardaArquivo, aux->nomeArquivo);		// Copia o nome do arquivo para imprimir
	strcpy(guardaFormato, aux->formatoArquivo);		// Copia o formato do arquivo para imprimir 
	guardaPaginas = aux->quantidadePaginas;			// Copia quantidade de p�ginas para imprimir
	
	if(*inicio == *fim){		// Se tiver apenas um elemento na fila...
		*inicio = NULL;			// Inicio aponta para null
		*fim = NULL;			// Fim aponta para null, lista agora � vazia
		free(aux);				// Libera mem�ria
		tam--;					// Tamanho da fila diminui em -1
		printf("\nImprimindo...\n");
		printf("\nArquivo: %s\n",guardaArquivo);
		printf("Formato: %s\n",guardaFormato);
		printf("P�ginas: %d\n\n", guardaPaginas);
		
		return;
	}
		
	*inicio = (*inicio)->prox; // Fazendo o inicio da fila apontar agora para o segundo n�
	free(aux);					// Libera mem�ria
	tam--;
	printf("\nImprimindo...\n");
	printf("\nArquivo: %s%s\n", guardaArquivo,guardaFormato);
	printf("Formato: %s\n", guardaFormato);
	printf("P�ginas: %d\n\n", guardaPaginas);
	
	return;
}


void statusFila(imp *inicio){
	
	int pos = 1;																// Vari�vel local para imprimir as posi�oes da fila iniciando em 1
	int guardaPaginas = inicio->quantidadePaginas - inicio->quantidadePaginas;	// Vari�vel local para imprimir a quatidade total de p�ginas
	
	
	while(inicio){													// La�o while, enquanto inicio existir...
		printf("Posi��o__: %d\n", pos);								// Imprime posi��o 
		printf("C�digo___: %d\n", inicio->ID);						// Imprime ID da impress�o 
		printf("Nome_____: %s\n", inicio->nomeArquivo);				// Imprime nome do arquivo
		printf("Formato__: %s\n", inicio->formatoArquivo);			// Imprime formato do arquivo
		printf("Paginas__: %d\n\n", inicio->quantidadePaginas);		// Imprime quantidade de paginas
		pos++;														// Incrementa +1 na posi��o da fi
		guardaPaginas = guardaPaginas + inicio->quantidadePaginas;	// Soma a quantidade de p�ginas total
		inicio = inicio->prox;										// Incremento para ir para o pr�ximo arquivo
	}
	
	printf("Numero total de p�ginas: %d\n", guardaPaginas);
	printf("Tamanho da fila: %d\n\n", tam);				// Imprime tamanho atual da fila, guardado na vari�vel global TAM
	
	
	return;
}


void zeraFila(imp **inicio, imp **fim){
	*inicio = NULL;		// Inicio da fila aponta para NULL
	*fim = NULL;		// Final da fila aponta para NULL
	tam = 0;			// Tamanho � zerado
	printf("\nFila zerada!\n\n");
	
	return;
}


int imprimeMenu(){						// Menu principal 
	int opcao;
	
	printf("============================\n");
	printf("== HR PRINTER 1100 SERIES ==\n");
	printf("============================\n\n");
	printf("  1 - Enviar impress�o\n");
	printf("  2 - Cancelar impress�o\n");
	printf("  3 - Consumir impress�o\n");
	printf("  4 - Status fila\n");
	printf("  5 - Limpar fila\n");
	printf("  6 - Sair\n\n");
	
	do{
		printf("Escolha uma op��o: ");
		fflush(stdin);
		scanf("%d", &opcao);
		if(opcao < 1 || opcao > 6){
			printf("Op��o inv�lida.\n");
		}
	}while(opcao < 1 || opcao > 6);
	
	return opcao;
}

