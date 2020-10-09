# Introdução
 Esse repositório foi criado com intuito de centralizar e compartilhar conhecimentos em estrutura de dados com a linguagens C, adquiridos no curso de Bacharelado em Ciencia da Computação na disciplina Estrutura de Dados I.
 Os códigos tratam-se de pequenos programas e exemplos, que aplicam o tratamento de dados com Tabela Hash, Mapa, Fila, Pilha e Listas. Antes de se aventurar nas várias estruturas de dados da linguagem C, precisamos deixar claro duas coisas: a escolha da estrutura dependerá exclusivamente da sua aplicação, e o conceito de ponteiros é imprescindível para aprender essas estruturas.
 
# Estruturas de Dados 

Estrutura de dados é um modo particular de organização e armazenamento de dados na memória de um computador, de modo que possam ser usados de forma mais eficiente. É um conceito importantissimo, e utilizado em diversas áreas da computação. No geral, em uma estrutura de dados precisamos saber como realizar um determinado conjunto de operações básicas, como por exemplo:
- Inserir um novo item
- Excluir um item existente
- Buscar algum item 
- Ordernar um item
- Editar um item

Os tipos de estruturas de dados estão relacionadas exatamente com o COMO aquela estrutura irá fazer essas operaçoes. Inserir no final ou no inicio? Remover um item no final ou no inicio? São essas respostas que irão determinar as caracteristicas de cada estrutura.
Uma estrutura de dados bem definida consegue resolver problemas extremamente complexos de forma simples, mas afinal, ques estruturas são essas? 
Vou abordar... 

## Ponteiros
## Listas 
## Listas Duplamente Encadeadas 
## Filas 
## Pilhas 
## Tabela hash 
## Mapas 
 
   
# 1 - Ponteiros
 >“Os ponteiros são variáveis, como muitas outras. [...] A
diferença é que ao invés de armazenarem informações
como verdadeiro, falso, o nome ou idade de uma pessoa,
os ponteiros armazenam os endereços de memória onde
essas variáveis estão armazenadas” (PIVA JUNIOR, p. 454, 2014).

Não existe comunicação sem endereços!
Exemplos:
- Carteiros precisam dos endereços (CEP) para as
correspondências;
- Pessoas precisam do endereço (e-mail) de outras para enviar
mensagens formais;
- Os computações precisam de endereços (IP) para
comunicarem entre si

A própria memória RAM de um computador é dividida em endereços. Um computador com 8GB de RAM pode ter até 8 bilhões de endereços (se divida em pedacinho de 1 byte).
Só é possível encontrar dados, porque toda a memória está endereçada.
É aqui que entram os ponteiros. São variáveis que armazenam o endereço de outra variável.
Um pouco confuso né? Vou ilustrar:

Supondo que você declarou 3 variáveis do tipo 'int'. Cada variável do tipo 'int' precisa de 4 bytes de espaço na memória.

```int x = 2, y = 3, z = x + y:```


![ponteiro](https://user-images.githubusercontent.com/72525405/95510104-c9762780-098b-11eb-87ef-aa0284e89110.PNG)

Agora criaremos novas variáveis, os ponteiros, apontando para o endereço de memória das variáveis criadas anteriormente.

```
int *px = &x;
int *py = &y;
int *pz = &z;
 ```
& -> informa o endereço de uma variável
* -> informa o conteúdo armazenado em uma variável

![ponteiro2](https://user-images.githubusercontent.com/72525405/95511538-fdeae300-098d-11eb-9364-2fefe6f5592c.PNG)

- px conterá o endereço da variável x;
- py conterá o endereço da variável y;
- pz conterá o endereço da variável z.

Entenda que uma variável possui o conteúdo (um numero, uma string, falso, verdadeiro...), e o seu endereço de memória (onde ela foi alocado na memória).
 
