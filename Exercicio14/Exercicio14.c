#include <stdio.h>
#include <stdlib.h>

struct {
    float *datos;
    int dimX;
    int dimY;
} typedef Matriz; //Estrutura para representar as matrices


Matriz* introducirMatriz();
Matriz* xerarMatrizSparse(Matriz *matrizUsuario);
Matriz* recuperarMatrizCompleta(Matriz *matrizSparse);
Matriz* crearMatriz(int dim_X, int dim_Y);

void mostrarMatriz(Matriz *matrizUsuario);

//Mostramos unha matriz no seu formato habitual
void mostrarMatriz(Matriz *matrizUsuario)
{
    float temp = 0;
  
    for(int i = 0; i < (*matrizUsuario).dimX; i++)
    {
        for(int j = 0; j < (*matrizUsuario).dimY; j++)
        {
            temp = *(((*matrizUsuario).datos) + i*(*matrizUsuario).dimY + j); //Elemento (i,j) da matriz
            printf("%.1f ", temp);
        }
        printf("\n");
    }
    printf("\n\n");
}

Matriz* crearMatriz(int dim_X, int dim_Y)
{
    Matriz *novaMatriz = (Matriz*)malloc(sizeof(Matriz));
    
    if(novaMatriz != NULL) //Comprobamos se se pudo asignar memoria no montón
    {
        (*novaMatriz).dimX = dim_X;
        (*novaMatriz).dimY = dim_Y;
        (*novaMatriz).datos = (float*)malloc(dim_X*dim_Y*sizeof(float));
        
        //Se non se conseguiu asignar memoria para os datos da matriz
        //Liberamos a memoria desta
        if((*novaMatriz).datos == NULL)
        {
            free(novaMatriz);
            novaMatriz = NULL;
        }
    }
    return novaMatriz;
}

Matriz* introducirMatriz()
{
    Matriz *matrizUsuario = NULL;
    
    int dim_X, dim_Y;
    float temp;
    //Pedimos ao usuario as dimensións da matriz
    printf("Introduce as dimensións da matriz (X Y): ");
    scanf("%d %d",&dim_X, &dim_Y);
    
    if(dim_X < 1 || dim_Y < 1) //As dimensón deben ser vaĺidas
    {
        printf("As dimensións introducidas non son válidas!\n");
        return NULL;
    }
    
    else
    {
        //Creamos unha matriz de dimensións dadas
        matrizUsuario = crearMatriz(dim_X, dim_Y);
    
        if(matrizUsuario != NULL)
        {
            //Permitimos o usuario introducir os elementos da matriz
            for(int i = 0; i < dim_X; i++)
            {
                for(int j = 0; j < dim_Y; j++)
                {
                    printf("Dato [%d][%d]: ", i, j);
                    scanf("%f",&temp);
                    *(((*matrizUsuario).datos) + i*dim_Y + j) = temp;
                }
            }
            printf("\n");
        }
    }
    return matrizUsuario;
}

Matriz* xerarMatrizSparse(Matriz *matrizUsuario)
{
    Matriz *matrizSparse = NULL;
    
    int elementosNonNulos = 0;
    
    //Elementos da matriz orixinal
    int elementosMatriz = (*matrizUsuario).dimX * (*matrizUsuario).dimY;
    
    //Contador para a matriz Sparse
    int k = 0;
    
    int dim_X = 0, dim_Y = 3; //Toda matriz Sparse ten 3 columnas
    
    //Determinamos os elementos non nulos da matriz orixinal
    for(int i = 0; i < elementosMatriz; i++)
    {
        if(*(((*matrizUsuario).datos) + i) != 0)
        {
            elementosNonNulos++;
        }
    }
    
    //Se non hai elementos nulos non ten sentido xerar unha matriz Sparse
    if(elementosNonNulos == 0)
    {
        printf("Non hai elementos nulos na matriz! Non se xera Sparse!\n");
    }
    else
    {
        //Comprobamos se a matriz Sparse terá máis elementos que a orixinal
        if((dim_Y*elementosNonNulos) > ((*matrizUsuario).dimX * (*matrizUsuario).dimY))
        {
            printf("A matriz Sparse ten máis elementos que a matriz orixinal!\n");
        }   
    
        dim_X = elementosNonNulos; //Tantas filas como elementos non nulos
        matrizSparse = crearMatriz(dim_X, dim_Y);
    
        if(matrizSparse != NULL)
        {
            dim_X = (*matrizUsuario).dimX;
            dim_Y = (*matrizUsuario).dimY;
    
            for(int i = 0; i < dim_X; i++)
            {
                for(int j = 0; j < dim_Y; j++)
                {
                    if(*(((*matrizUsuario).datos) + i*dim_Y + j) != 0)
                    {
                        //Completamos unha fila da matriz Sparse
                        //Cada vez que temos un dato non nulo
                        *(((*matrizSparse).datos) + k) = i;
                        k++;
                        *(((*matrizSparse).datos) + k) = j;
                        k++;
                        *(((*matrizSparse).datos) + k) = *(((*matrizUsuario).datos) + i*dim_Y + j);
                        k++;
                    }
                }
            }
        }
    }
    return matrizSparse;
}

Matriz* recuperarMatrizCompleta(Matriz *matrizSparse)
{
    Matriz *matrizCompleta = NULL;
    int elementos = ((*matrizSparse).dimX)*((*matrizSparse).dimY);
    
    int tempMaxX = 0, tempMaxY = 0, coordenada = 0;
    
    //Tomamos uns máximos iniciales para cada coordenada
    tempMaxX = *((*matrizSparse).datos); 
    tempMaxY = *((*matrizSparse).datos + 1);
    
    for(int i = 2; i < elementos; i++)
    {
        //Determinamos en que posición da fila estamos
        coordenada = i % 3;
        
        //O primeiro elemento de cada fila danos a coordenada X
        if(coordenada == 0)
        {
            if(tempMaxX < *((*matrizSparse).datos + i))
            {
                tempMaxX = *((*matrizSparse).datos + i);
            }
            
        }
        //O segundo elemento de cada fila danos a coordenada Y
        else if(coordenada == 1)
        {
            if(tempMaxY < *((*matrizSparse).datos + i))
            {
                tempMaxY = *((*matrizSparse).datos + i);
            }
        }
    }
    
    //Sumamos un a cada máximo para obter as dimensións da matriz orixinal
    tempMaxX++;
    tempMaxY++;
    
    //Creamos unha matriz con esas dimensións
    matrizCompleta = crearMatriz(tempMaxX, tempMaxY);
    
    if(matrizCompleta != NULL)
    {
        //Facemos nulos todos os elementos da matriz completa
        for(int i = 0; i < tempMaxX*tempMaxY; i++)
        {
            *(((*matrizCompleta).datos) + i) = 0;
        }
    
        int coordX = 0, coordY = 0; 
        float temp = 0;
    
        for(int i = 0; i < elementos; i++)
        {
            //Posición nas filas da matriz Sparse
            coordenada = i % 3;
            
            temp = *(((*matrizSparse).datos) + i);
            if(coordenada == 0) 
            {
                coordX = temp;
            }
            if(coordenada == 1)
            {
                coordY = temp;
            }
            if(coordenada == 2)
            {
                //Situamos o elemento na posición obtida nos pasos anteriores
                *(((*matrizCompleta).datos) + coordX*tempMaxY + coordY) = temp;
            }
        }
    }
    
    return matrizCompleta;
}


int main() {
    
    //Punteiros a todas as matrices que empregaremos
    Matriz *matrizUsuario = NULL;
    Matriz *matrizSparse = NULL;
    Matriz *matrizCompleta = NULL;
    
    matrizUsuario = introducirMatriz();
    if(matrizUsuario != NULL)
    {
        mostrarMatriz(matrizUsuario);
        matrizSparse = xerarMatrizSparse(matrizUsuario);
        if(matrizSparse != NULL)
        {
            mostrarMatriz(matrizSparse);
            matrizCompleta = recuperarMatrizCompleta(matrizSparse);
            if(matrizCompleta != NULL)
            {
                mostrarMatriz(matrizCompleta); 
            }
        }
         
    }
    
    if(matrizUsuario != NULL)
    {
        free((*matrizUsuario).datos);
        (*matrizUsuario).datos = NULL;
        
        free(matrizUsuario); 
        matrizUsuario = NULL;
    }
    
    if(matrizSparse != NULL)
    {
        free((*matrizSparse).datos);
        (*matrizSparse).datos = NULL;
        
        free(matrizSparse);
        matrizSparse = NULL;
    }
    
    if(matrizCompleta != NULL)
    {
        free((*matrizCompleta).datos);
        (*matrizCompleta).datos = NULL;
                
        free(matrizCompleta);
        matrizCompleta = NULL;
    }
    
    return (EXIT_SUCCESS);
}


