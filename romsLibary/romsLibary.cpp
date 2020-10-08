// RAFAEL VICTOR RODRIGUES DE SOUSA
#include <iostream>			// Biblioteca de entrada e saída de dados 
#include <stdlib.h>			// Biblioteca de propósito geral
#include <locale.h>			// Biblioteca de acentuação
#include <map>				// Biblioteca do conjunto associativo ordenado (mapas)

using namespace std;		// comando de entrada e saída de dedos

typedef struct rom tRom;	// Define um novo tipo de dado 'tRom'
struct rom{
	int ID;
	int anoLancamento;
	int qtdJogadores;
	string titulo;
	string desenvolvedora;
	string genero;
};

// Assinatura funcoes C++ 
void cadastraRom(map <int, tRom> &romMap);
void editarRom(map <int, tRom> &romMap);
void excluiRom(map<int, tRom> &romMap);
void consultarRom(map<int, tRom> &romMap);
void catalogo(map<int, tRom> &romMap);

// Assinatura funcoes C
int menuPrincipal();
int menuEditarRom();

int qtdRom;				// Variável global para controle de quantidade de ROM's

int main() {
	setlocale(LC_ALL,"");	// Configuração setlocale para aceitar qualquer tipo de acentuação latino
	
	map<int, tRom> romMap;	// Cria a estrutura mapa, chave=int  valor=tRom
	
	int opcao;				// Variável para controle de opcoes
	
	do{
		system("CLS");
		opcao = menuPrincipal();	// Menu principal
		switch(opcao){
			case 1: {// Cadastrar ROM
				cadastraRom(romMap);
				break;
			}
			
			case 2: {// Editar ROM
				editarRom(romMap);
				break;
			}
			
			case 3: {// Excluir ROM
				excluiRom(romMap);
				break;
			}
			
			case 4: {// Consultar ROM
				consultarRom(romMap);
				break;
			}
			
			case 5: {// Imprime ROM
				catalogo(romMap);
				break;
			}
			
			case 6: {// Fecha programa
				printf("\nFinalizando...\n");
				return 0;
				break;
			}
		}
	}while(opcao != 6);
	
	return 0;
}


void cadastraRom(map <int, tRom> &romMap)  {
	system("CLS");	// comando para limpar a tela
	cin.ignore();	// limpa entrada de dados
	tRom novo;		// novo elemento do tipo da estrutura
	
	bool returnID = false;				   // variável para controlar o ID repetido
	map <int, tRom>::iterator mapIterator; // declaração do iterator
	
	cout << "  == CADASTRO DE ROM ==\n\n";
	
	do{
		cout << "\nID do ROM: ";
		cin >> novo.ID;
		cin.ignore();	// limpa entrada de dados
		
		for(mapIterator = romMap.begin(); mapIterator != romMap.end(); mapIterator++) {	// percorre todo o mapa
			if(novo.ID == mapIterator->second.ID) {			// se elemento buscado já existir no mapa...
				cout << "\nEsse ID já está cadastrado!\n";
				returnID = true;							
			}else {
				returnID = false;
			}
		}
	}while(returnID == true);
	
	cout << "Titulo: ";
	getline(cin,  novo.titulo);
	
	cout << "Gênero: ";
	getline(cin, novo.genero);
	
	cout << "Nome desenvolvedora: ";
	getline(cin, novo.desenvolvedora);
	
	cout << "Ano de lançamento: ";
	cin >> novo.anoLancamento;
	
	cout << "Quantidade de jogadores: ";
	cin >> novo.qtdJogadores;
	
	qtdRom++;			    // quantidade de ROM's aumenta +1
	romMap[qtdRom] = novo;  // armazena o novo elemento no mapa
	
	cout << "\nCadastro realizado com sucesso!\n\n";
	
	system("PAUSE");
	return;
}


void editarRom(map <int, tRom> &romMap) {
	system("CLS");							// comando para limpar tela
	cin.ignore();							// limpa entrada de dados
	map <int, tRom>::iterator mapIterator;	// declara iterator
	
	cout << "  == EDITAR ROM ==\n\n";
	
	int chave,opcao; // Variáveis de busca e controle
	cout << "\nDigite o ID do ROM que deseja fazer alteraçoes: ";
	cin >> chave;
	
	for(mapIterator = romMap.begin(); mapIterator != romMap.end(); mapIterator++) {	// percorre todo o mapa
		if(mapIterator->second.ID == chave) {   // se elemento buscado existir no mapa...
			opcao = menuEditarRom(); 		  // imprime menu	   
			fflush(stdin);					  // limpa entrada de dados
			switch (opcao) {				
				case 1: {// Alterar ID do Rom
					cout << "\nNovo ID do ROM: ";
					cin >> mapIterator->second.ID;
					cout << "\nCadastro atualizado!\n\n";
					break;
				}
				case 2: {// Alterar título
					cout << "\nNovo título: ";
					getline(cin, mapIterator->second.titulo);
					cout << "\nCadastro atualizado!\n\n";
					break;
				}
				case 3: {// Alterar genero
					cout << "\nNovo gênero: ";
					getline(cin, mapIterator->second.genero);
					cout << "\nCadastro atualizado!\n\n";
					break;
				}
				case 4: {// Alterar nome da desenvolvedora
					cout << "\nNova desenvolvedora: ";
					getline(cin, mapIterator->second.desenvolvedora);
					cout << "\nCadastro atualizado!\n\n";
					break;
				}
				case 5: {// Alterar ano de lançamento
					cout << "\nNovo ano de lançamento: ";
					cin >> mapIterator->second.anoLancamento;
					cout << "\nCadastro atualizado!\n\n";
					break;
				}
				case 6: {// Alterar quantidade de jogadores
					cout << "\nNova quantidade de jogadores: ";
					cin >> mapIterator->second.qtdJogadores;
					cout << "\nCadastro atualizado!\n\n";
					break;
				}
			}
		}
	}
	
	system("PAUSE");
	return;
}


void consultarRom(map<int, tRom> &romMap) {
	system("CLS");						   // limpa tela
	map <int, tRom>::iterator mapIterator; // declara iterator
	
	int chave;		// variável de busca
	cin.ignore();
	
	cout << " == CONSULTAR ROM ==\n\n";
	
	cout << "\nInforme o ID do ROM: ";
	cin >> chave;
	
	for(mapIterator = romMap.begin(); mapIterator != romMap.end(); mapIterator++) {	// percorre toda a estrutura map
		if(mapIterator->second.ID == chave) {           // se elemento buscado existir na estrutura...
			cout << "\n============================";
			cout << "\nID do ROM: " << mapIterator->second.ID;
			cout << "\nTítulo: " << mapIterator->second.titulo;
			cout << "\nGênero: " << mapIterator->second.genero;
			cout << "\nDesenvolvedora: " << mapIterator->second.desenvolvedora;
			cout << "\nAno de lançamento: " << mapIterator->second.anoLancamento;
			cout << "\nQuantidade de jogadores: " << mapIterator->second.qtdJogadores; 
			cout << "\n============================\n\n";
		}
	}
	
	system("PAUSE");
	return;
}


void excluiRom(map<int, tRom> &romMap) {
	system("CLS");							// limpa tela
	map <int, tRom>::iterator mapIterator;  // declara Iterator
	
	int chave,opcao;					// variáveis de busca e cotrole
	bool returnID = false;				// variável para controlar ID que não existe
	
	cout << "  == EXCLUIR ROM ==\n\n";
	
	cout << "\nInforme o ID do ROM que deseja excluir: ";
	cin >> chave;
		
	cout << "\nDeseja realmente excluir esse ROM da sua biblioteca ?\n[1] - SIM\n[0] - NÃO\n\n";
	cin >> opcao;
	
	if(opcao == 1) {
		mapIterator = romMap.find(chave);  // encontra o elemento por meio da chave
		if(mapIterator != romMap.end()) {   // se elemento encontrado for diferente do final do mapa...
			romMap.erase(mapIterator);	   // apaga elemento encontrado
			qtdRom--;     				   // quantidade de rom's diminuni em -1
			cout << "\nROM excluido com sucesso!\n\n";
		}
	}
	
	system("PAUSE");
	return;
}


void catalogo(map<int, tRom> &romMap) {
	system("CLS");							// limpa tela
	map <int, tRom>::iterator mapIterator; 	// declara iterator
	
	cout << " == CATÁLOGO ==\n\n";
	
	for(mapIterator = romMap.begin(); mapIterator != romMap.end(); mapIterator++) {		// percorre todo o mapa
		cout << "===========================";
		cout << "\n[ID ROM]: " << mapIterator->second.ID;
		cout << "\nTítulo: " << mapIterator->second.titulo;
		cout << "\nGênero: " << mapIterator->second.genero;
		cout << "\nDesenvolvedora: " << mapIterator->second.desenvolvedora;
		cout << "\nAno de lançamento: " << mapIterator->second.anoLancamento;
		cout << "\nQuantidade de jogadores: " << mapIterator->second.qtdJogadores; 
		cout << "\n";
	}
	cout << "===========================\n\n";
	cout << "  [QUANTIDADE ROM's]: " << qtdRom;
	cout << "  \n  ******************";
	cout << "\n\n";
	system("PAUSE");
	return;
}


int menuPrincipal() {
	int opcao;		// variável de controle
	
	printf("==========================\n");
	printf("----- ROM's LIBRARY -----\n");
	printf("==========================\n\n");
	printf(" 1 - Cadastrar ROM\n");
	printf(" 2 - Editar ROM\n");
	printf(" 3 - Excluir ROM\n");
	printf(" 4 - Consultar ROM's\n");
	printf(" 5 - Imprimir catálogo\n");
	printf(" 6 - Fechar\n\n");
	
	do{
		printf("Escolha uma opção: ");
		fflush(stdin);
		scanf("%d", &opcao);
		if(opcao < 1 || opcao > 6) {
			printf("\nOpção inválida! Tente novamente\n\n");
		}
	}while(opcao < 1 || opcao > 6);
	
	return opcao;
}


int menuEditarRom() {
	int opcao;		// variável de controle
	
	do{
		system("CLS");
		printf("  == EDITAR ROM ==\n\n");
		printf(" 1 - Alterar ID do ROM\n");
		printf(" 2 - Alterar título\n");
		printf(" 3 - Alterar gênero\n");
		printf(" 4 - Alterar nome da desenvolvedora\n");
		printf(" 5 - Alterar ano de lançamento\n");
		printf(" 6 - Alterar quantidade de jogadores\n");
		printf(" 0 - Voltar\n\n");
		printf("Escolha uma opção: ");
		fflush(stdin);
		scanf("%d", &opcao);
		if(opcao > 6 || opcao < 0 ) {
			printf("Opcão inválida!\n\n");
		}
	}while(opcao > 6 || opcao < 0);
	
	return opcao;
}

