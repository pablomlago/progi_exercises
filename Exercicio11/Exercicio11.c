#include <stdio.h>
#include <stdlib.h>

int* calcularMaximo(int *vecEnteiros, int numDatos);

int* calcularMaximo(int *vecEnteiros, int numDatos)
{
    int tempMax = 0;
    int indice = 0;
    
    tempMax = *vecEnteiros; //Podemos sempre facer esta asignación ao asegurarnos previamente que numDatos > 0
    //Comprobación previa a invocación da función
        
    for(int i = 1; i < numDatos; i++)
    {
        if(tempMax < *(vecEnteiros + i)) 
        {
            tempMax = *(vecEnteiros + i);
            indice  = i;
        }
    }
    return (vecEnteiros + indice); //Devolvemos un punteiro ao máximo
}

int main()
{
    int numDatos = 0;
    int *maximo = NULL;
    
    //Pedimos o usuario o número de datos que desexa introducir
    printf("Cantos datos desexas introducir: ");
    scanf("%d", &numDatos);
    
    if(numDatos > 0)
    {
        int *vecEnteiros = (int*)malloc(numDatos*sizeof(int));
    
        if(vecEnteiros != NULL)
        {
            printf("Introduce os datos: \n");
            
            //Permitimos o usuario introducir os datos
            for(int i = 0; i < numDatos; i++)
            {
                printf("%dº: ", i);
                scanf("%d", (vecEnteiros + i));
            }
    
            maximo = calcularMaximo(vecEnteiros, numDatos); //Gardamos o punteiro ao máximo
            
            if(maximo != NULL)
            {
                printf("O máximo é: %d", *maximo);
            }
            
            free(vecEnteiros);
            vecEnteiros = NULL;
        }
        else
        {
            printf("Erro ao reservar memoria no montón!\n");
        }
    }
    else
    {
        printf("O número de datos introducido non é válido!\n");
    }
    
    return (EXIT_SUCCESS);
}