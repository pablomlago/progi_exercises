#include <stdio.h>
#include <stdlib.h>

#define NUMERO_VOCAIS 11 //Temos en conta maiúsculas e minúsculas
#define MAX_SIZE 100 //Tamaño máximo da cadena introducida polo usuario

//Determina o número de vocais e palabras nunha cadena de texto introducida
//polo usuario
void Contar(char *fraseUsuario, int *numeroVocais, int *numeroPalabras);

void Contar(char *fraseUsuario, int *numeroVocais, int *numeroPalabras)
{
    int i = 0;
    *numeroVocais = 0;
    *numeroPalabras = 1; //Para simplificar contar as palabras
    char vocais[] = {'a','e','i','o','u','A','E','I','O','U','\0'};
    if(fraseUsuario[i] == '\0') //O usuario non introduce nada
    {
        *numeroPalabras = 0;
    }
    else
    {
        while(fraseUsuario[i] != '\0')
        {
            for(int j = 0; j < NUMERO_VOCAIS; j++) //Comparamos co vector da vocais
            {
                if(fraseUsuario[i] == vocais[j])
                {
                    *numeroVocais +=1;
                }
            }
        
            if(fraseUsuario[i] == ' ') //Por cada espacio contamos unha palabra máis
            {
                *numeroPalabras +=1;
            }
            i++;
        }
    }
    return;
}

int main()
{
    int numeroVocais = 0, numeroPalabras = 0;
    char fraseUsuario[MAX_SIZE];
    printf("Introduce unha cadea de texto: "); 
    gets(fraseUsuario); //Obtemos a cadea de texto introducida polo usuario
    Contar(fraseUsuario,&numeroVocais,&numeroPalabras); //Paso por referencia
    printf("Numero Vocais: %d, Numero Palabras: %d\n",numeroVocais,numeroPalabras);
    
    return (EXIT_SUCCESS);
}