#include <stdlib.h>
#include <stdio.h>

int main (void) {
    float nota1, nota2, media;		 // 
    float *pnota1 = &nota1;
    float *pnota2 = &nota2;
    float *pmedia = &media;
    
    do{
       printf("Digite a nota 1: ");
       scanf("%f", &nota1);
    }while(nota1 < 0 || nota1 > 10);
    
    do{
       printf("Digite a nota 2: ");
       scanf("%f", &nota2);
    }while(nota2 < 0 || nota2 > 10);
    
    *pmedia = (*pnota1 + *pnota2) / 2;
    
    printf("Notas variaveis:\n");
    printf("Nota 1: %.2f\n", nota1);
    printf("Nota 2: %.2f\n", nota2);
    printf("Media.: %.2f\n", media);
    printf("\n");
    printf("Notas ponteiros:\n");
    printf("Nota 1: %.2f\n", *pnota1);
    printf("Nota 2: %.2f\n", *pnota2);
    printf("Media.: %.2f\n", *pmedia);
    
    printf("\n");
    system("pause");
    return 0;
}
