#include <stdio.h>
#include <stdlib.h>

int* calculoPotencias(int enteiro, int N);

int* calculoPotencias(int enteiro, int N) //Calcula N potencias dun enteiro dado
{
    int *potencias = (int*)malloc(N*sizeof(int));
        
    if(potencias != NULL) //Comrpobamos que a asignación de memoria no montón se realizou satisfactoriamente
    {
        *potencias = enteiro; 
        for(int i = 1; i < N; i++) //Calcumaos recursivamente as potencias a partir da anterior
        {
            *(potencias + i) = enteiro;
            *(potencias + i) *= *(potencias + (i-1));
        }
    }
        
    return potencias;
}

int main()
{
    int enteiro = 0, N = 0;
    int *potencias;
    
    //Pedimos o usuario o enteiro e o número de potencias a calcular
    printf("Introduce un enteiro: ");
    scanf("%d", &enteiro);
    printf("Introduce as potencias a calcular: ");
    scanf("%d", &N);
    
    if(potencias > 0)
    {
        potencias = calculoPotencias(enteiro, N);
        if(potencias != NULL)
        {
            for(int i = 0; i < N; i++)
            {
                printf("%dª Potencia: %d\n", i+1, *(potencias + i));
            }
        }
        else
        {
            printf("Erro ao reservar memoria no montón!\n");
        }
        
        free(potencias);
        potencias = NULL;
    }
    else
    {
        printf("O número de potencias introducido non é válido!\n");
    }
    return (EXIT_SUCCESS);
}