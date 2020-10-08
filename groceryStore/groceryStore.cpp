// ** RAFAEL VICTOR R. DE SOUSA ** //
#include <stdio.h>		// Biblioteca de entrada e saída de dados
#include <stdlib.h>		// Biblioteca de propósito geral
#include <locale.h>		// Biblioteca de acentuação de caracters

#define TAMMAX 100		// Tamanho máximo da fila

typedef struct Produto tProduto;	// Definindo um novo tipo de dados e um alias para a estrutura
struct Produto{
	int codigoBarras;				// Código de barras do produto
	int quantiadeProduto;			// Unidades de produto
	char descricaoProduto[70];		// Descrição do produto
	float valorUnitario;			// Valor unitário do produto
	struct Produto *prox;			// Ponteiro proximo
};

// Assinatura das funçoes 
void abreCaixa();
void atendeCliente(tProduto **inicio, tProduto **fim);
void cancelaItem(tProduto **inicio, tProduto **fim);
void cupom(tProduto *inicio);
void finalizaAtendimento(tProduto **inicio, tProduto **fim);
int imprimeMenu();

// Assinatura variáveis globais
int tamFila;				 	// Variável global para controle do tamanho da fila
int tamCancelados;		    	// Variável global para controle do vetor dos itens cancelados
int codigosCancelados[TAMMAX];  // Vetor para guardar o código de barras dos itens cancelados 
float totalPagar;		 		// Variável global para total da compra 
float valorCaixa = 100;	 		// Variável global iniciando em 100, para valor do caixa


int main(){
	
	setlocale (LC_ALL, "");		// Configurando para aceitar qualquer tipo de acentuação 
	
	tProduto *inicio = NULL;	// Ponteiros inicio e topo do tipo da estrutura
	tProduto *fim = NULL;		// apontando para NULL inicialmente 
	
	int opcao;					// Variável local para controle do switch-case 
	char maisUm;				// Variável local para controle do do-while (case 2)
	
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
	
	tProduto *novo = (tProduto*) malloc(sizeof(tProduto));	// Aloca dinamicamente um novo nó 
	
	if(!novo){							// Se não conseguiu alocar dinamicamente...
		printf("Heap overflow!\n\n");
		return;
	}
	
	printf("\nCódigo de barras: ");
	fflush(stdin);
	scanf("%d",&novo->codigoBarras);
	printf("Descrição do produto: ");
	fflush(stdin);
	scanf("%s", novo->descricaoProduto);
	printf("Preço unitário: ");
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
	
	int codigo;									// Variável local para guardar código a ser removido 
	tProduto *ant,*atual;						// Ponteiro anterior e atual para controlar minha lista, do tipo da estrutura
	
	printf("Digite o código de barras do item para cancelar: ");
	fflush(stdin);
	scanf("%d",&codigo);
	
	if(*inicio == NULL){				// Se fila estiver vazia...
		printf("\nCesta vazia, impossível cancelar! \n\n");
		return;
	}else{								// Fila possui algo...
		ant = *inicio;					// Anterior aponta para inicio da fila
		atual = *inicio;				// Atual aponta para inicio da fila
		while(atual != NULL){ 			// Larço while para localizar o código 		
			if(atual->codigoBarras == codigo){	// Se elemento for encontrado
				codigosCancelados[tamCancelados] = atual->codigoBarras;	 	// Guarda o código de barras que vai ser excluido
				if(atual == *inicio){			// Se o código estiver no inicio...
					*inicio = atual->prox;		// Ando com inicio para o segundo nó 
					free(atual);				// Libero memória
					printf("\nItem de código de barras %d cancelado com sucesso!\n\n", codigo);
					tamCancelados++;			// Aumenta +1 no tamanho dos cancelados
					tamFila--;					// Diminui tamanho da fila
					break;
				}else{
					if(atual == *fim){ 	// Se o código estiver no final...
						*fim = ant;		// Ponteiro fim aponta para o anterior 
					}
					ant->prox = atual->prox;// Refaz o encdeamento
					free(atual);			// Libera memória 
					printf("\nItem de código de barras %d cancelado com sucesso!\n\n", codigo);
					tamCancelados++;		// Aumenta +1 no tamanho dos cancelados
					tamFila--;      			// Diminui tamanho da fila
					break;
				}
			}else{					  // Se eu não encontro o elemento...
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
	int codSequencial = 1;				   							// Variável para controlar o número sequencial dos produtos
	
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
	
	for(int i = 0; i < tamCancelados; i++){ 			// Laço for para imprimir os itens cancelados
		printf("[ITEM CANCELADO] ");
		printf("Código de barras: %d\n", codigosCancelados[i]);
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
	tamFila = 0;						  // Tamanho da fila é zerado
	tamCancelados = 0;					  // Tamanho dos cancelados é zerado
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
		printf("Escolha uma opção: ");
		fflush(stdin);
		scanf("%d", &opcao);
		if(opcao < 1 || opcao > 6){
			printf("Opção inválida.\n");
		}
	}while(opcao < 1 || opcao > 6);
	
	return opcao;
}

