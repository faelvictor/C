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
Irei abordar as seguintes estruturas:

## Ponteiros
## Lista Linear
## Lista Duplamente Encadeada 
## Fila
## Pilha
## Tabela hash 
## Mapa
 
   
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
É aqui que entram os ponteiros. A memória alocada dinamicamente é acessada por esses ponteiros, que na verdade
são variáveis que armazenam o endereço de uma área de memória.
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

asterisco -> informa o conteúdo armazenado em uma variável

![ponteiro2](https://user-images.githubusercontent.com/72525405/95511538-fdeae300-098d-11eb-9364-2fefe6f5592c.PNG)

- px conterá o endereço da variável x;
- py conterá o endereço da variável y;
- pz conterá o endereço da variável z.

Utilizando a alocação dinamica de memória, permite que o espaço em memória seja alocado apenas quando necessário. 
A maior vantagem no uso da alocação dinâmica é que, dado o endereço inicial da área alocada e o índice de um elemento, podemos acessá-lo imediatamente, com um simples e rápido cálculo. 

O grande problema está em não poder redimensionar o uso de memória de uma estrutura, ou seja, deve ser conhecido previamente e de tamanho imutável.
 
# 2 - Lista Linear

Pense o conceito de lista em uma lista de compras. Uma lista de compras você escreve (insere) os produtos que serão comprados e quando forem, você risca eles da lista (exclui).
Já em uma lista em estrutura de dados possui os **nós**.

Nós são elementos que preenchem a lista, cada nó é um registro que será armazenado em uma struct, ou seja, cada nó possui suas próprias informaçoes.
Mas oque é uma lista linear ? 

Lista linear ou unidemensional, significa que é possivel buscar as informações sequencialmente, uma após a outra.
A lista linear também é dinâmica, ou seja, pode aumentar ou diminuir sob demanda, conforme o crescimento do programa.
Por serem dinâmicos, os nós são armazenados na área de heap do processo.

Para acessar esses nós, primeiro é necessário saber pelo menos o endereço do primeiro nó. Esse nó costuma ser denominado de cabeça da lista (head).
Esse primeiro endereço deve ser armazenado por uma variável.

A estrutura de lista lembra a de um vetor, mas há algumas diferenças.

**LISTA vs VETOR**

- **Acesso**

Vetor = Os elementos de um vetor podem ser acessados diretamente,
por meio de seus índices.

Listas = Nas listas os nós são acessados sequencialmente, um
após o outro, pelos ponteiros.

- **Alocação**

Vetor = Os vetores são alocados antes da execução do processo,
sendo que todo espaço previsto para o vetor já é alocado e
reservado, sem possibilidades de ajustes

Listas = Nas listas o espaço em memória é alocado conforme o
necessário.

Vamos tomar como exemplo uma lista com três nós. Cada nó possui a seguinte estrutura:

```
struct tipo_no {
  int info;
  struct tipo_no *prox;
};
typedef struct tipo_no no;
```

A estrutura define um tipo camado 'no'.

Cada nó é uma 'struct tipo_no' que é composta de:
- um campo info, inteiro;
- um campo prox, ponteiro para outro nó

Claro que podem haver mais dados, mas vamos manter a estrutura simplificada.

Depois de adicionar três elementos na lista linear, visualmente ficaria assim:
![lista1](https://user-images.githubusercontent.com/72525405/95789868-b4afd180-0cb4-11eb-8f9a-786992578735.PNG)

Os valores 1, 2 e 3 representam os valores armazenados no campo info.
Os valores 500, 508 e 516 são endereços de memória hipotéticos.

O primeiro nó aponta para o segundo, e o segundo aponta para o terceiro.
O terceiro nó não aponta para ninguém, pois ele é o final da lista.
E quem é início? É o ponteiro que armazena o endereço do início da lista, ou seja, do primeiro nó.

**Inicialização de uma lista**
A inicialização de uma lista consiste em fazer com que o primeiro ponteiro aponte para NULL, ou seja, a lista é uma lista vazia, não há nenhum nó inserido.
É importante entender que essa inicialização, pois com esse primeiro ponteiro com valor NULL é que vamos conseguir prosseguir nossas operaçoes.

Podemos fazer essa inicialização dentro de uma função, ou iniciar logo na função main. Eu particularmente prefiro fazer na main, por ser uma linha de código.

```
int main() {
    no *lista = NULL;    // Inicialização da lista
    
    system("PAUSE");
    return 0;
}
```



