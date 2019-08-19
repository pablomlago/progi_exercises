#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define VEC1_SIZE 4
#define VEC2_SIZE 6
#define VEC_RES (VEC1_SIZE+VEC2_SIZE) //Tamaño do vector resultante de combinar os anteriores

void escribirVector(int *vecUsuario, int elemsVec);
void leerVector(int *vecUsuario, int elemsVec);
void combinarVectores(int *resultado,int *vecUsuario1, int *vecUsuario2, int elemsVec1, int elemsVec2);

//Pedimos ao usuario un vector de tamaño (elemsVec)
void escribirVector(int *vecUsuario, int elemsVec) 
{
    printf("Introduce un vector de enteiros ordenados: \n");
    for(int i = 0; i < elemsVec; i++)
    {
        printf("%d: ",i);
        scanf("%d",&vecUsuario[i]);
    }
}

//Imprimimos un vector de enteiros de tamaño (elemsVec)
void leerVector(int *vecUsuario, int elemsVec)
{
    for(int i = 0; i < elemsVec; i++)
    {
        printf("%d ",vecUsuario[i]);
    }
    printf("\n");
}

//Combinamos dous vectores ordenados de enteiros e gardamos o resultado noutro
void combinarVectores(int *resultado,int *vecUsuario1, int *vecUsuario2, int elemsVec1, int elemsVec2)
{
    int j = 0, k = 0;
    
    //Supoñemos que o vector resultado ten un tamaño igual a suma dos 
    //dous vectores que se combinan
    for(int i = 0; i < (elemsVec1 + elemsVec2); i++) 
    {
        if(j < elemsVec1 && k < elemsVec2) //Non sobrepasamos o tamaño de ningún dos vectores
        {
            if(vecUsuario1[j] <= vecUsuario2[k]) //Válidos pois os vectores están ordenados
            {
                resultado[i] = vecUsuario1[j];
                j++;
            }
            else
            {
                resultado[i] = vecUsuario2[k];
                k++;
            }
        }
        //Sobrepasouse o tamaño dun dos vectores
        //Os elementos restantes son os que quedan no vector no que aínda
        //non se sobrepasou o seu tamaño
        else 
        {
            if(j < elemsVec1)
            {
                resultado[i] = vecUsuario1[j];
                j++;
            }
            else
            {
                resultado[i] = vecUsuario2[k];
                k++;
            }
        }
    }
    
}


int main()
{
   int vecUsuario1[VEC1_SIZE]; 
   int vecUsuario2[VEC2_SIZE];
   int resultado[VEC_RES];
   
   //Pedimos o usuario que introduza os dous vectores de enteiros ordenados
   escribirVector(vecUsuario1,VEC1_SIZE);
   escribirVector(vecUsuario2,VEC2_SIZE);
   
   //Combinamos os dous vectores e mostramos o resultado
   combinarVectores(resultado,vecUsuario1,vecUsuario2,VEC1_SIZE,VEC2_SIZE);
   printf("O vector resultado é: \n");
   leerVector(resultado,VEC_RES);
   
   return (EXIT_SUCCESS);
}