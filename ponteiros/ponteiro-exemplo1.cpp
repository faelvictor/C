#include <stdlib.h>
#include <stdio.h>

int main (void) {
    // Cria��o e inicializa��o das vari�veis
    int x = 2, y = 3;
    int z = x + y;
    
    // Impress�o dos endere�os das vari�veis x, y, z
    // Utiliza-se o operador & para indicar a impress�o do endere�o
    printf("Os enderecos das variaveis sao:\n");
    printf("x = %d\n", &x);
    printf("y = %d\n", &y);
    printf("z = %d\n", &z);
    printf("\n");
    // Impress�o dos valores armazenados nas vari�veis x, y, z.
    printf("Os valores das variaveis sao:\n");
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("z = %d\n", z);
    
    printf("\n");
    
    // Cria��o dos ponteiros e inicializa��o deles com os endere�os das vari�veis
    // O operador * indica para onde o ponteiro vai apontar
    // O operador & indica que o valor a ser armazenado no ponteiro � o endere�o
    int *px = &x;
    int *py = &y;
    int *pz = &z;
    
    // Impress�o dos endere�os dos ponteiros
    printf("Os enderecos dos ponteiros sao:\n");
    printf("&px = %d\n", &px);
    printf("&py = %d\n", &py);
    printf("&pz = %d\n", &pz);
    printf("\n");
    // Impress�o dos valores armazenados no ponteiro
    // Ou impress�o dos endere�os armazenados nos ponteiros
    printf("Os valores dos ponteiros sao:\n");
    printf("px = %d\n", px);
    printf("py = %d\n", py);
    printf("pz = %d\n", pz);
    printf("\n");
    // Impress�o dos valores armazenados nos endere�os que os ponteiros apontam
    printf("Os valores apontados pelos ponteiros sao:\n");
    printf("*px = %d\n", *px);
    printf("*py = %d\n", *py);
    printf("*pz = %d\n", *pz);
    
    printf("\n");
    system("pause");
    return 0;
}

