#include <iostream>			// Biblioteca de entrada e saída de dados 
#include <stdlib.h>			// Biblioteca de propósito geral
#include <locale.h>			// Biblioteca de acentuação de caracteres 
#include <map>				// Biblioteca de conjunto associativo ordenado (mapas)

using namespace std;		// comando para entrada e saída de dados 

typedef struct produtor tProdutor;   // Define um novo tipo de dado 'tProdutor' 
struct produtor {				
	string razaoSocial;
	string nomeFantasia;
	string cidade;
	string uf;
	int status;
	int CNPJ;
};

struct lote {				// Struct de armazenamento da tabela hash 
	unsigned int CNPJ;		
	int numeroLote;
	int diaProducao;
	int mesProducao;
	int anoProducao;
	char nomeProduto[30];
};

typedef struct hashLote tLote;  // Define um novo tipo de dado 'tLote'
struct hashLote {				// struct de controle da tabela hash
	int TABLE_SIZE;				// tamanho da tabela hash
	int qtd;					// quantidade de nós inseridos 
	struct lote **item;			// ponteiro que aponta para a struct de armazenamento da tabela 
};

// Assinatura funçoes C++ (PRODUTOR)
void insereProdutor(map <int, tProdutor> &prodLista);
void editarProdutor(map <int, tProdutor> &prodLista);
void buscaProdutor(map <int, tProdutor> &prodLista);

// Assinatura funçoes C   (PRODUÇÃO)
tLote* criaHash(int TABLE_SIZE);
void insereLote(tLote* ha, struct lote lote);
void buscaLote(tLote* ha, struct lote lote);
void removeLote(tLote* ha,struct lote lote);
int hashDivisao(int numeroLote, int TABLE_SIZE);
int sondagemExponencial(int pos, int i, int TABLE_SIZE);

// Assinatura de outras funcionalidades
void relatorio(tLote* ha);
void zeraLotes(tLote* ha);

// Assinatura menus
int menuPrincipal();
int menuProducao();
int menuProdutor();
int menuEditarProdutor();

// Variáveis globais
int TABLE_SIZE = 199;		   // Tamanho da tabela hash
int cod = 0;				   // Variável para controlar o número de produtores 
int pAtivo = 0, pInativo = 0;  // Variável para controlar a quantidade de produtores ativos e inativos 

int main() {
	setlocale(LC_ALL, "");			// Configuração setlocale para aceitar qualquer tipo de acentuação latino
	int opcao, op;					// Variáveis de controle do-while
	
	map<int, tProdutor> produtorMap;		// Cria a estrutura do mapa, chave=int valor=tProduto
	
	struct lote lote;					// Declara variável para guardar os dados de 'struct lote' 
	
	tLote* ha = criaHash(TABLE_SIZE);	// Cria tabela hash
	
	do{
		system("CLS");
		opcao = menuPrincipal();		// Menu principal
		
		switch(opcao){
			case 1: {// PRODUTOR	
				op = menuProdutor();	   // Imprime menu
					
				if(op == 1) {
					insereProdutor(produtorMap);	// cadastro de produtor
				}
				if(op == 2) {
					editarProdutor(produtorMap);	// edição de dados do produtor
				}		
				if(op == 3) {
					buscaProdutor(produtorMap);	// busca por produtores 
				}
				break;
			}
				
			case 2: {// PRODUÇÃO
				op = menuProducao();	// Imprime menu
			
				if(op == 1) {
					insereLote(ha, lote);	// cadastro de lote
				}
				if(op == 2) {
					buscaLote(ha, lote);	// busca por lotes
				}
				if(op == 3) {
					removeLote(ha, lote);	// exclui lote 
				}
				break;
			}
			
			case 3: {// RELATÓRIO
				relatorio(ha);			 // relatório de produção e produtores
				break;
			}
			
			case 4: {// ZERAR LOTES            		 
				zeraLotes(ha);		   // exclui todos os lotes cadastrados
				break;
			}
				
			case 5: {// SAIR
				printf("\nFinalizando...\n");
				return 0;
				break;
			}
		}
	}while(opcao != 5 || op == 0);
	
	return 0;
}


void insereProdutor(map <int, tProdutor> &produtorMap) {
	cin.ignore();			// delimitador os caracteres, para limpar a entrada de dados 
	tProdutor novo;			// novo elemento do tipo da estrutura
	
	cout << "\nCNPJ: ";
	cin >> novo.CNPJ;
	cin.ignore();
	
	cout << "Razão social: ";
	getline(cin, novo.razaoSocial);
	
	cout << "Nome fantasia: ";
	getline(cin, novo.nomeFantasia);
	
	cout << "Cidade: ";
	getline(cin, novo.cidade);
	
	cout << "UF: ";
	getline(cin, novo.uf);
	
	do{
		cout << "[1] - ATIVO\n[0] - INATIVO\nStatus: ";
		cin >> novo.status;	
	}while(novo.status < 0 || novo.status > 1);
	
	if(novo.status == 1) {		// Se for igual a 1 (ATIVO)...
		pAtivo++;				// aumenta +1 em produtores ativos
	}else {						// se não...
		pInativo++;				// aumenta +1 em produtores inativos
	}
	
	cod++;						// Aumenta +1 na quantidade de produtores
	
	produtorMap[cod] = novo;		// armazena o novo produtor no mapa
	
	cout << "\nCadastro realizado com sucesso\n\n";  
	
	system("PAUSE");
	return;
}


void editarProdutor(map <int, tProdutor> &produtorMap) {
	cin.ignore();							// delimitador os caracteres
	map <int, tProdutor>::iterator mapIterator;		// declara iterator
	
	int chave,opcao; // Variáveis de controle
	cout << "\nDigite o CNPJ do produtor que deseja fazer alteraçoes: ";
	cin >> chave;
	for(mapIterator = produtorMap.begin(); mapIterator != produtorMap.end(); mapIterator++) {	// percorre toda estrutura map, do inicio ao fim
		if(mapIterator->second.CNPJ == chave) {   // se cnpj(valor) for igual ao valor buscado 
			opcao = menuEditarProdutor(); 		  // imprime menu	   
			fflush(stdin);						  // função para limpar saida de dados
			switch (opcao) {				
				case 1: {// Alterar CNPJ
					cout << "\nNovo CNPJ: ";
					cin >> mapIterator->second.CNPJ;
					cout << "\nCadastro atualizado!\n\n";
					break;
				}
				case 2: {// Alterar razão social
					cout << "\nNova razão social: ";
					getline(cin, mapIterator->second.razaoSocial);
					cout << "\nCadastro atualizado!\n\n";
					break;
				}
				case 3: {// Alterar nome fantasia
					cout << "\nNovo nome fantasia: ";
					getline(cin, mapIterator->second.nomeFantasia);
					cout << "\nCadastro atualizado!\n\n";
					break;
				}
				case 4: {// Alterar cidade
					cout << "\nNova cidade: ";
					getline(cin, mapIterator->second.cidade);
					cout << "\nCadastro atualizado!\n\n";
					break;
				}
				case 5: {// Alterar UF
					cout << "\nNovo UF: ";
					getline(cin, mapIterator->second.uf);
					cout << "\nCadastro atualizado!\n\n";
					break;
				}
				case 6: {// Alterar status
					if(mapIterator->second.status == 1) { 	// Se produtor estiver ATIVO...
						printf("\nProdutor alterado para INATIVO!\n");
						mapIterator->second.status = 0;     // seta 0 para alterar para inativo
						pAtivo--;							// diminui -1 em produtores ativos
						pInativo++;							// aumeta +1 em produtores inativos
					}else {									// Se nao...
						printf("\nProdutor alterado para ATIVO!\n");
						mapIterator->second.status = 1;     // seta 1 para alterar para ativo
						pAtivo++;							// aumenta +1 em produtores ativos
						pInativo--;							// diminuir -1 em produtores inativos
					}
					cout << "\nCadastro atualizado!\n\n";
					break;
				}
			}
		}
	}
	system("PAUSE");
	return;
}


void buscaProdutor(map <int, tProdutor> &produtorMap) {
	cin.ignore();					// delimitador os caracteres
	map <int, tProdutor>::iterator mapIterator;   // declara iterator
	int chave; // Variável de busca
	
	cout << "\nDigite o CNPJ do produtor: ";
	cin >> chave;
	cin.ignore(); 
	
	for(mapIterator = produtorMap.begin(); mapIterator != produtorMap.end(); mapIterator++) {	// percorre toda a estrutura map
		if(mapIterator->second.CNPJ == chave) {           // se cnpj(valor) for igual ao valor buscado
			cout << "\n========================";
			cout << "\nCNPJ: " << mapIterator->second.CNPJ;
			cout << "\nRazão social: " << mapIterator->second.razaoSocial;
			cout << "\nNome fantasia: " << mapIterator->second.nomeFantasia;
			cout << "\nCidade: " << mapIterator->second.cidade;
			cout << "\nUF: " << mapIterator->second.uf;
			if(mapIterator->second.status == 1) {       // Se status estiver ativo...
				cout << "\nStatus: [ATIVO]";
			}else {										// se não...
				cout << "\nStatus: [INATIVO]";
			}
			cout << "\n========================\n\n";
		}
	}
	
	system("PAUSE");
	return;	
}


tLote* criaHash(int TABLE_SIZE) {				 // Função para criar a tabela hash		
	tLote* ha = (tLote*) malloc(sizeof(tLote));  // aloca dinamicamente a tabela hash
	if(ha != NULL) {				 		     // se conseguiu alocar dinamicamente...
		int i;
		ha->TABLE_SIZE = TABLE_SIZE; 		     // atribui o valor da constante pra dentro da variável de controle de tamanho da tabela hash
		ha->item = (struct lote**) malloc(TABLE_SIZE*sizeof(struct lote*));
		// demarcando/criando os espaços dos lotes
		// sizeof de hashLote, pois cada lote possui um tamanhoa igual, multiplicando pelo o tamanho max da tabela hash
		// ou seja, cria um vetor dinamicamente 
		if(ha->item == NULL) {		// Se não conseguiu alocar dinamicamente...
			free(ha);				// exclui a tabela criada
			return NULL;
		}
		ha->qtd = 0;				// inicia a quantidade em 0
		for(i = 0; i < ha->TABLE_SIZE; i++) {	// estrutura FOR, preenchendo todas os lotes incialmente com NULL
			ha->item[i] = NULL;		
		}
	}
	return ha;
}


void insereLote(tLote* ha, struct lote lote) {
	if(ha == NULL || ha->qtd == ha->TABLE_SIZE) {			// Se tabela hash não existe ou está cheia...
		printf("Não foi possível inserir um novo lote!\n");
		return;
	}
	
	printf("\nNumero do lote: ");
	fflush(stdin);
	scanf("%d", &lote.numeroLote);
	printf("DATA DE PRODUÇÃO\n");
	printf("Dia: ");
	fflush(stdin);
	scanf("%d", &lote.diaProducao);
	printf("Mês: ");
	fflush(stdin);
	scanf("%d", &lote.mesProducao);
	printf("Ano: ");
	fflush(stdin);
	scanf("%d", &lote.anoProducao);
	printf("Nome do produto: ");
	fflush(stdin);
	scanf("%s", &lote.nomeProduto);
	printf("CNPJ do produtor: ");
	fflush(stdin);
	scanf("%d", &lote.CNPJ);
	
	int chave = lote.numeroLote;						  // chave recebe numero do lote
	int pos = hashDivisao(chave, ha->TABLE_SIZE);         // 'pos' recebe valor hashing calculado 
	
	if(ha->item[pos] == NULL) {		         // Se não deu colisão...
		struct lote* novo;									// cria novo lote
		novo = (struct lote*) malloc(sizeof(struct lote));  // aloca dinamicamente
		
		if(novo == NULL) {      // não conseguiu alocar dincamicamente
			return;
		}
		
		*novo = lote;			// novo recebe dados do lote
		ha->item[pos] = novo;	// guarda o novo lote recém cadastrado, na posição calculada pelo hashing
		ha->qtd++;				// quantidade de lote aumenta + 1 
	}else {						// Se deu colisão...
		for(int i = 1; i < ha->TABLE_SIZE; i++) {	// Laço for, para caso precisar, percorrer toda a tabela 
			int newPos = sondagemExponencial(pos, i, ha->TABLE_SIZE); // nova posição será calculada pela sondagem exponencial
			if(ha->item[newPos] == NULL) {							  // Se não deu colisão...
				struct lote* novo;									  // cria novo lote
				novo = (struct lote*) malloc(sizeof(struct lote));	  // aloca dinamicamente
				if(novo == NULL) {				// se não conseguiu alocar dinamicamente...
					return;
				}
				*novo = lote;			 // novo recebe dados do lote
				ha->item[newPos] = novo; // guarda o novo lote recém cadastrado, na posição calculada pelo hashing
				ha->qtd++;				 // quantiadde de lote aumenta + 1
			}
		}
	}
	printf("\nLote cadastrado com sucesso!\n\n");
	system("PAUSE");
	return;
}


void buscaLote(tLote* ha, struct lote lote) {
	
	int numeroLote;     // Variável de busca
	
	if(ha == NULL) {	// Estrutura hash não existe
		return;
	}
	
	printf("\nDigite o número do lote: ");
	fflush(stdin);
	scanf("%d", &numeroLote);
	
	int pos = hashDivisao(numeroLote, ha->TABLE_SIZE);  // calcula o valor de hashing para lote que quer buscar
	
	if(ha->item[pos] == NULL) {		// Se a posição buscada seja igual a NULL...
		printf("\nNão existe nenhum lote cadastrado com esse número!\n\n");
		system("PAUSE");
		return;
	}
	
	if(ha->item[pos]->numeroLote == numeroLote) { // Se o numero do lote de item, em posição calculada por hashing for igual a numero do lote pesquisado... 
		printf("\n==============================");
		printf("\nNúmero do lote: %d\n", ha->item[pos]->numeroLote);
		printf("Data de produção: %d/%d/%d\n", ha->item[pos]->diaProducao, ha->item[pos]->mesProducao, ha->item[pos]->anoProducao);
		printf("Nome do produto: %s\n", ha->item[pos]->nomeProduto);
		printf("CNPJ do produtor: %d\n", ha->item[pos]->CNPJ);
		printf("==============================\n\n");
	} else {// Se não... Pode ter havido colisão
		for(int i = 0; i < ha->TABLE_SIZE; i++) { // Estrutura for para percorrer toda tabela
			int newPos = sondagemExponencial(pos, i, ha->TABLE_SIZE); // Recalcula hashing 	
			if(ha->item[newPos] == NULL) {     	  // Se a nova posição recalculada de item for igual a NULL...
				printf("\nNão existe nenhum lote cadastrado com esse número!\n\n");
				system("PAUSE");
				break;
			}
			if((ha->item[newPos]->numeroLote) == numeroLote) { // Se o numero do lote de item, em nova posição recalculada por hashing for igual a numero do lote pesquisado...
				printf("\n==============================");
				printf("\nNumero do lote: %d\n", ha->item[newPos]->numeroLote);
				printf("Data de produção: %d/%d/%d\n", ha->item[newPos]->diaProducao, ha->item[newPos]->mesProducao, ha->item[newPos]->anoProducao);
				printf("Nome do produto: %s\n", ha->item[newPos]->nomeProduto);
				printf("CNPJ do produtor: %d\n", ha->item[newPos]->CNPJ);
				printf("==============================\n\n");
				system("PAUSE");
				break;
			}
		}
	}	
	system("PAUSE");
	return;
}


void removeLote(tLote* ha,struct lote lote) {
	
	int numeroLote;    // Variável de busca
	
	printf("\nDigite o número do lote que deseja remover: ");
	fflush(stdin);
	scanf("%d", &numeroLote);
	
	int pos = hashDivisao(numeroLote, TABLE_SIZE);  // Calcula posição hashing 
	
	if(ha->item[pos] == NULL) {     // Se posição calculada é igual a NULL...
		printf("\nNão existe lote cadastrado com esse número!\n\n");
		system("PAUSE");
		return;	
	}
	
	if(ha->item[pos]->numeroLote == numeroLote) {	// Se número do lote de item, na posição calculada por hashing for igual a numero de lote pesquisado...
		free(ha->item[pos]);                    // libera espaço na memória
		ha->item[pos] = NULL;  					// seta NULL na posição excluida 
		ha->qtd--;								// quantidade de lotes diminui em -1
	}else { // Se não... pode ter havido colisão
		for(int i = 0; i < ha->TABLE_SIZE; i++) {
			int newPos = sondagemExponencial(pos, i, ha->TABLE_SIZE);	// Recalcula hashing
			if(ha->item[newPos] == NULL) {   // Se nova posição recalculada de item, for igual a NULL...
				printf("\nNão existe nenhum lote cadastrado com esse número!\n\n");
				system("PAUSE");
				break;
			}
			if((ha->item[newPos]->numeroLote) == numeroLote) { // Se o numero do lote de item, em nova posição recalculada por hashing for igual a numero do lote pesquisado...
				free(ha->item[newPos]);  // Libera memória
				ha->item[newPos] = NULL; // Seta NULL na posição excluida		
				ha->qtd--;				 // Quantidade de lote diminui em -1
			}
		}
	}
	printf("\nLote removido com sucesso!\n\n");
	
	system("PAUSE");
	return;
}


int hashDivisao(int numeroLote, int TABLE_SIZE) {
	return numeroLote % TABLE_SIZE; 				// Calcula o valor de hashing 
}


int sondagemExponencial(int pos, int i, int TABLE_SIZE) {
	pos = (2 * i) + (5 *i*i);                // Calcula o valor de hashing
	return (pos % 0x70000000) % TABLE_SIZE;
}


void relatorio(tLote* ha) {
	
	printf("\n* PRODUTORES *\n");
	printf("Quatidade total: %d\n", cod);
	printf("Ativos: %d\n", pAtivo);
	printf("Inativos: %d\n\n", pInativo);
	
	printf("\n* LOTES *\n");
	printf("Quantidade total: %d\n\n", ha->qtd);
	
	system("PAUSE");
	return;
}


void zeraLotes(tLote* ha) {
	if(ha != NULL) {	// Se tabela hash existir...
		int i;
		for(i=0; i< ha->TABLE_SIZE; i++) {	// Percorre todas as posiçoes da tabela
			if(ha->item[i] != NULL) {  // Se a posicao da tabela é diferente de NULL, tem algum valor...
				free(ha->item[i]);	   // Libera da memória daquela posição 
				ha->item[i] = NULL;	   // A posição liberada recebe NULL
			}	
		}
	}
	ha->qtd = 0;		// Quantidade de lotes zerado
	printf("\nTodos os lotes foram excluidos!\n\n");
	system("PAUSE");
}


int menuPrincipal() {
	
	int opcao;
	
	printf("========================\n");
	printf("= AGRO TECH PRODUCTION = \n");
	printf("======================== \n\n");
	printf(" 1 - PRODUTOR\n");
	printf(" 2 - PRODUÇÃO\n");
	printf(" 3 - RELATÓRIOS\n");
	printf(" 4 - ZERAR LOTES\n");
	printf(" 5 - SAIR\n\n");
	
	do{
		printf("Escolha uma opção: ");
		fflush(stdin);
		scanf("%d", &opcao);
		if(opcao < 1 || opcao > 5) {
			printf("Opção inválida!\n");
		}
	}while(opcao < 1 || opcao > 5);
	
	return opcao;
}


int menuProdutor() {
	
	int opcao;
	
	do{
		system("CLS");
		printf("   == PRODUTOR ==\n\n");
		printf(" 1 - CADASTRAR PRODUTOR\n");
		printf(" 2 - EDITAR PRODUTOR\n");
		printf(" 3 - BUSCAR PRODUTOR\n");
		printf(" 0 - VOLTAR\n\n");
		printf("Escolha uma opção: ");
		fflush(stdin);
		scanf("%d", &opcao);
		if(opcao < 0 || opcao > 4) {
			printf("\nOpção inválida!\n\n");
			system("PAUSE");
		}
	}while(opcao < 0 || opcao > 4);
	
	return opcao;
}


int menuProducao() {
	
	int opcao;
	
	do{
		system("CLS");
		printf("   == PRODUÇÃO ==\n\n");
		printf(" 1 - CADASTRAR LOTE\n");
		printf(" 2 - CONSULTAR LOTE\n");
		printf(" 3 - REMOVER LOTE\n");
		printf(" 0 - VOLTAR\n");
		printf("\nEscolha uma opção: ");
		fflush(stdin);
		scanf("%d", &opcao);
		if(opcao < 0 || opcao > 3) {
			printf("\nOpção inválida!\n\n");
			system("PAUSE");
		}
	}while(opcao < 0 || opcao > 3);
	
	return opcao;
}

int menuEditarProdutor() {
	
	int opcao;
	
	do{
		system("CLS");
		printf("   == ALTERAÇÃO DE DADOS ==\n\n");
		printf("* Oque deseja alterar?\n");
		printf(" 1 - Alterar CNPJ\n");
		printf(" 2 - Alterar razão social\n");
		printf(" 3 - Alterar nome fantasia\n");
		printf(" 4 - Alterar cidade\n");
		printf(" 5 - Alterar UF\n");
		printf(" 6 - Alterar status\n");
		printf(" 0 - Voltar\n\n");
		printf("Escolha uma opção: ");
		fflush(stdin);
		scanf("%d", &opcao);
		if(opcao < 0 || opcao > 6) {
			printf("\nOpção não existe!\n\n");
			system("PAUSE");
		}	
	}while(opcao < 0 || opcao > 6);
	
	return opcao;
}

