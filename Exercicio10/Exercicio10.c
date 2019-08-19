#include <stdio.h>
#include <stdlib.h>

#define VEC_SIZE 3

int main()
{
    int enteiro = 0;
    double real = 3.1416;
    char cadea[] = "Hola";
    float vecReal[VEC_SIZE] = {0,1,2};
    
    int *pEnteiro = &enteiro;
    double *pReal = &real;
    char *pCadea = cadea;
    float *pVecReal = vecReal;
    
    printf("Enteiro. Valor: %d, Enderezo: %p\n",enteiro,&enteiro);
    printf("Punteiro enteiro. Valor: %d, Enderezo: %p\n\n", *pEnteiro, pEnteiro);
    
    printf("Real. Valor: %f, Enderezo: %p\n",real,&real);
    printf("Punteiro real. Valor: %f, Enderezo: %p\n\n", *pReal, pReal);
    
    printf("Cadea. Valor: %s, Enderezo: %p\n",cadea,cadea);
    printf("Punteiro cadea. Valor: %s, Enderezo: %p\n\n", pCadea, pCadea);
    
    for(int i = 0; i <  VEC_SIZE; i++) //Recorremos os elementos do vector de reais
    {
        printf("Vector reais. Valor[%d]: %f\n", i, vecReal[i]);
    }
    printf("Enderezo: %p\n\n",vecReal);
    
    for(int i = 0; i <  VEC_SIZE; i++) //Recoremos os elementos do vector de reais usando o punteiro
    {
        printf("Punteiro vector reais. Valor[%d]: %f\n", i, *(pVecReal + i));
    }
    printf("Enderezo: %p\n\n",pVecReal);
    
    return (EXIT_SUCCESS);
}