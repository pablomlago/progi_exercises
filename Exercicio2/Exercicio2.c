#include <stdio.h>
#include <stdlib.h>

#define NUMERO_ERROS 5 //Número de mensaxes de erro definidos

void mostrarMensaxeErro(int numeroErro);

void mostrarMensaxeErro(int numeroErro)
{
    char mensaxesErro[NUMERO_ERROS][50] = {"400 Solicitude incorrecta","401 Usuario non autorizado",
    "404 Páxina non atopada","500 Erro interno","503 Servicio non disponible"};
    
    if((numeroErro >= 0) && (numeroErro < NUMERO_ERROS))
    {
        printf("Produciuse o seguinte erro: %s\n",mensaxesErro[numeroErro]);
    }
    else
    {
        printf("Erro non identificado!\n"); //Non está definido certo erro
    }
}

int main()
{
    int numeroErro = 0;
    printf("Cal é o código do erro: ");
    scanf("%d",&numeroErro);
    mostrarMensaxeErro(numeroErro);
    
    return (EXIT_SUCCESS);
}