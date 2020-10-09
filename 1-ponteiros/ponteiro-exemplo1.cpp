#include <stdlib.h>
#include <stdio.h>

int main (void) {
    // Criação e inicialização das variáveis
    int x = 2, y = 3;
    int z = x + y;
    
    // Impressão dos endereços das variáveis x, y, z
    // Utiliza-se o operador & para indicar a impressão do endereço
    printf("Os enderecos das variaveis sao:\n");
    printf("x = %d\n", &x);
    printf("y = %d\n", &y);
    printf("z = %d\n", &z);
    printf("\n");
    // Impressão dos valores armazenados nas variáveis x, y, z.
    printf("Os valores das variaveis sao:\n");
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("z = %d\n", z);
    
    printf("\n");
    
    // Criação dos ponteiros e inicialização deles com os endereços das variáveis
    // O operador * indica para onde o ponteiro vai apontar
    // O operador & indica que o valor a ser armazenado no ponteiro é o endereço
    int *px = &x;
    int *py = &y;
    int *pz = &z;
    
    // Impressão dos endereços dos ponteiros
    printf("Os enderecos dos ponteiros sao:\n");
    printf("&px = %d\n", &px);
    printf("&py = %d\n", &py);
    printf("&pz = %d\n", &pz);
    printf("\n");
    // Impressão dos valores armazenados no ponteiro
    // Ou impressão dos endereços armazenados nos ponteiros
    printf("Os valores dos ponteiros sao:\n");
    printf("px = %d\n", px);
    printf("py = %d\n", py);
    printf("pz = %d\n", pz);
    printf("\n");
    // Impressão dos valores armazenados nos endereços que os ponteiros apontam
    printf("Os valores apontados pelos ponteiros sao:\n");
    printf("*px = %d\n", *px);
    printf("*py = %d\n", *py);
    printf("*pz = %d\n", *pz);
    
    printf("\n");
    system("pause");
    return 0;
}

