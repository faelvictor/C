// ** RAFAEL VICTOR R. DE SOUSA ** //
#include <stdio.h>		// Biblioteca de entrada e sa�da de dados
#include <stdlib.h>		// Biblioteca de prop�sito geral
#include <locale.h>		// Biblioteca de acentua��o de caracters

#define TAMMAX 100		// Tamanho m�ximo da fila

typedef struct Produto tProduto;	// Definindo um novo tipo de dados e um alias para a estrutura
struct Produto{
	int codigoBarras;				// C�digo de barras do produto
	int quantiadeProduto;			// Unidades de produto
	char descricaoProduto[70];		// Descri��o do produto
	float valorUnitario;			// Valor unit�rio do produto
	struct Produto *prox;			// Ponteiro proximo
};

// Assinatura das fun�oes 
void abreCaixa();
void atendeCliente(tProduto **inicio, tProduto **fim);
void cancelaItem(tProduto **inicio, tProduto **fim);
void cupom(tProduto *inicio);
void finalizaAtendimento(tProduto **inicio, tProduto **fim);
int imprimeMenu();

// Assinatura vari�veis globais
int tamFila;				 	// Vari�vel global para controle do tamanho da fila
int tamCancelados;		    	// Vari�vel global para controle do vetor dos itens cancelados
int codigosCancelados[TAMMAX];  // Vetor para guardar o c�digo de barras dos itens cancelados 
float totalPagar;		 		// Vari�vel global para total da compra 
float valorCaixa = 100;	 		// Vari�vel global iniciando em 100, para valor do caixa


int main(){
	
	setlocale (LC_ALL, "");		// Configurando para aceitar qualquer tipo de acentua��o 
	
	tProduto *inicio = NULL;	// Ponteiros inicio e topo do tipo da estrutura
	tProduto *fim = NULL;		// apontando para NULL inicialmente 
	
	int opcao;					// Vari�vel local para controle do switch-case 
	char maisUm;				// Vari�vel local para controle do do-while (case 2)
	
	do{
		system("CLS");
		opcao = imprimeMenu();	 // Menu principal
		
		switch(opcao){
			case 1: { 
				abreCaixa();
				system("PAUSE");
				break;
			}
			
			case 2: {
				do{
					atendeCliente(&inicio, &fim);
					printf("Tem mais produtos ? <S/N>: ");
					fflush(stdin);
					scanf("%c", &maisUm);
				}while(maisUm == 's' || maisUm == 'S');
				break;
			}
			
			case 3: {
				cancelaItem(&inicio, &fim);
				system("PAUSE");
				break;
			}
			
			case 4: {
				cupom(inicio);
				system("PAUSE");
				break;
			}
			
			case 5: {
				finalizaAtendimento(&inicio,&fim);
				system("PAUSE");
				break;
			}
			
			case 6: {
				printf("\nFINALIZANDO...\n\n");
				break;
			}
		}
	}while(opcao != 6);
	
	system("PAUSE");
	return 0;
}


void abreCaixa(){ 					// Abrir caixa 

	tamFila = 0;					
	printf("\nCAIXA ABERTO!\n");
	printf("Valor caixa: $%.2f\n\n", valorCaixa);
	
	return;
}


void atendeCliente (tProduto **inicio, tProduto **fim){
	
	if (tamFila == TAMMAX){									  // Se fila estiver cheia...
		printf("Pilha de produtos cheia! Aguarde...\n");
		return;
	}
	
	tProduto *novo = (tProduto*) malloc(sizeof(tProduto));	// Aloca dinamicamente um novo n� 
	
	if(!novo){							// Se n�o conseguiu alocar dinamicamente...
		printf("Heap overflow!\n\n");
		return;
	}
	
	printf("\nC�digo de barras: ");
	fflush(stdin);
	scanf("%d",&novo->codigoBarras);
	printf("Descri��o do produto: ");
	fflush(stdin);
	scanf("%s", novo->descricaoProduto);
	printf("Pre�o unit�rio: ");
	fflush(stdin);
	scanf("%f", &novo->valorUnitario);
	printf("Quantidade: ");
	fflush(stdin);
	scanf("%d", &novo->quantiadeProduto);
	
	novo->prox = NULL;			// Proximo de novo aponta para NULL, pois ele vai ser o ultimo
	
	if(!(*inicio)){				// Se a fila estiver vazia...
		*inicio = novo;			// Inicio da pilha aponta para o novo elemento
		*fim = novo;			// Fim da fila aponta para o novo elemento
	}else{
		(*fim)->prox = novo; 	// Liga o penultimo no novo elemento
		*fim = novo;			// Fim da fila aponta para o novo elemento
	}
	tamFila ++;
	
	return;
}


void cancelaItem(tProduto **inicio, tProduto **fim){
	
	int codigo;									// Vari�vel local para guardar c�digo a ser removido 
	tProduto *ant,*atual;						// Ponteiro anterior e atual para controlar minha lista, do tipo da estrutura
	
	printf("Digite o c�digo de barras do item para cancelar: ");
	fflush(stdin);
	scanf("%d",&codigo);
	
	if(*inicio == NULL){				// Se fila estiver vazia...
		printf("\nCesta vazia, imposs�vel cancelar! \n\n");
		return;
	}else{								// Fila possui algo...
		ant = *inicio;					// Anterior aponta para inicio da fila
		atual = *inicio;				// Atual aponta para inicio da fila
		while(atual != NULL){ 			// Lar�o while para localizar o c�digo 		
			if(atual->codigoBarras == codigo){	// Se elemento for encontrado
				codigosCancelados[tamCancelados] = atual->codigoBarras;	 	// Guarda o c�digo de barras que vai ser excluido
				if(atual == *inicio){			// Se o c�digo estiver no inicio...
					*inicio = atual->prox;		// Ando com inicio para o segundo n� 
					free(atual);				// Libero mem�ria
					printf("\nItem de c�digo de barras %d cancelado com sucesso!\n\n", codigo);
					tamCancelados++;			// Aumenta +1 no tamanho dos cancelados
					tamFila--;					// Diminui tamanho da fila
					break;
				}else{
					if(atual == *fim){ 	// Se o c�digo estiver no final...
						*fim = ant;		// Ponteiro fim aponta para o anterior 
					}
					ant->prox = atual->prox;// Refaz o encdeamento
					free(atual);			// Libera mem�ria 
					printf("\nItem de c�digo de barras %d cancelado com sucesso!\n\n", codigo);
					tamCancelados++;		// Aumenta +1 no tamanho dos cancelados
					tamFila--;      			// Diminui tamanho da fila
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


void cupom(tProduto *inicio){	

	float valorTotalProduto;					   					// Valor total de cada produto 
	float valorTotalCompra = valorTotalProduto - valorTotalProduto; // Valor total da compra
	float desconto;						  							// Valor do desconto
	int codSequencial = 1;				   							// Vari�vel para controlar o n�mero sequencial dos produtos
	
	while(inicio){		// Enquanto fila existir...
		printf("\n[ITEM 0%d]", codSequencial);
		printf("\nCodigo de barras.......: %d\n", inicio->codigoBarras);
		printf("Descricao do produto...: %s\n", inicio->descricaoProduto);
		printf("Preco unitario.........: $%.2f\n", inicio->valorUnitario);
		printf("Quantidade.............: %d\n", inicio->quantiadeProduto);
		valorTotalProduto = inicio->valorUnitario * inicio->quantiadeProduto;	// Calcula o valor total de cada produto
		printf("Valor total do produto.: $%.2f\n\n", valorTotalProduto);	
		valorTotalCompra = valorTotalCompra + valorTotalProduto;				// Calcula o valor total da compra
		inicio = inicio->prox;				// Anda com o ponteiro 
		codSequencial++;					// Incremento no codigo sequencial 
	}
	
	for(int i = 0; i < tamCancelados; i++){ 			// La�o for para imprimir os itens cancelados
		printf("[ITEM CANCELADO] ");
		printf("C�digo de barras: %d\n", codigosCancelados[i]);
	}
	
	printf("\n=====================================\n");
	printf(" TOTAL: $%.2f\n", valorTotalCompra);
	desconto = valorTotalCompra * 0.05;				// Calcula o valor do desconto
	printf(" VALOR DESCONTO DE 5 POR CENTO: $%.2f\n\n", desconto);
	totalPagar = valorTotalCompra - desconto;		// Aplica o desconto
	printf(" VALOR A PAGAR: $%.2f\n", totalPagar);
	printf("=====================================\n\n");
	
	return;
}


void finalizaAtendimento(tProduto **inicio, tProduto **fim){
	
	*inicio = NULL;						  // Ponteiro inicio aponta para NULL
	*fim = NULL;						  // Ponteiro topo aponta para NULL
	valorCaixa = valorCaixa + totalPagar; // Atualiza o valor do caixa
	tamFila = 0;						  // Tamanho da fila � zerado
	tamCancelados = 0;					  // Tamanho dos cancelados � zerado
	printf("\nATENDIMENTO FINALIZADO\n");
	printf("Valor do caixa atualizado para: $%.2f\n",valorCaixa);
	printf("\nPROXIMO!!!\n\n");
	
	return;
}


int imprimeMenu(){							// Menu principal

	int opcao;
	
	printf("==========================\n");
	printf("===== GROCERY STORE ======\n");
	printf("==========================\n\n");
	printf(" 1 - Abrir o caixa\n");
	printf(" 2 - Atender cliente\n");
	printf(" 3 - Cancelar item\n");
	printf(" 4 - Imprimir cupom fiscal\n");
	printf(" 5 - Finalizar atendimento\n");
	printf(" 6 - Sair\n\n");
	
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

