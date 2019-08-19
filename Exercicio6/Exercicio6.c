#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int calcularMaximo(int *datosArchivo,int indice); //Máximo dos datos no arquivo
int calcularMinimo(int *datosArchivo,int indice); //Mínimo dos datos no arquivo
float calcularMedia(int *datosArchivo,int indice); //Media dos datosn no arquivo

int calcularMaximo(int *datosArchivo,int indice) //Indice é o número de elementos no vector
{
    int tempMax = 0;
    if(indice != 0) //Se hai algún dato no vector
    {
        tempMax = datosArchivo[0];
        for(int i = 1; i < indice; i++)
        {
            if(tempMax <= datosArchivo[i])
            {
                tempMax = datosArchivo[i];
            }
        }
    }
    
    return tempMax;
}

int calcularMinimo(int *datosArchivo,int indice) //Indice é o número de elementos no vector
{
    int tempMin = 0;
    if(indice != 0) //Se hai algún dato no vector
    {
        tempMin = datosArchivo[0];
        for(int i = 1; i < indice; i++)
        {
            if(tempMin >= datosArchivo[i])
            {
                tempMin = datosArchivo[i];
            }
        }
    }
    
    return tempMin;
}

float calcularMedia(int *datosArchivo,int indice) //Indice é o número de elementos no vector
{
    int suma = 0;
    for(int i = 0; i < indice; i++)
    {
        suma += datosArchivo[i];
    }
    return (suma / indice);
}

int main() {
    
    FILE *ptf;
    char nomeArquivo[20];
    
    int erroPeche = 0;
    int datosArchivo[MAX_SIZE];
    
    int indice = 0, temp = 0;
    
    //Pedimos ao usuario o nome do arquivo
    printf("Introduce o nome do arquivo: ");
    scanf("%s",nomeArquivo);
    
    //Abrimos o arquivo
    if((ptf = fopen(nomeArquivo,"rt")) == NULL) //Lectura en modo texto
    {
        printf("Non se conseguiu abrir o arquivo!");
        return (EXIT_FAILURE);
    }
    
    while((feof(ptf) == 0) && (indice <= MAX_SIZE))
    {
        fscanf(ptf,"%d",&datosArchivo[indice]);
        if(feof(ptf) == 0) //Asegurámonos de non contar datos de máis
        {
            indice++;
        }
    }
    
    //Mostramos o máximo, mínimo e a media dos datos
    printf("O máximo é: %d\n",calcularMaximo(datosArchivo,indice));
    printf("O mínimo é: %d\n",calcularMinimo(datosArchivo,indice));
    printf("A media é: %f\n",calcularMedia(datosArchivo,indice));
    
    //Pechamos o arquivo
    erroPeche = fclose(ptf);
    if(erroPeche != 0)
    {
        printf("O arquivo non se pechou correctamente!");
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}
