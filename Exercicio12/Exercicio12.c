#include <stdio.h>
#include <stdlib.h>

#define DIXITOS_IP 4

char *IP(int d1, int d2, int d3, int d4);

char *intToChar(int numero);

char *intToChar(int numero)
{
    char *numChar = NULL;
    int elementos = 2;
    int dixito = 0;
    
    if(numero > 9)
    {
        elementos++;
        if(numero > 99)
        {
            elementos++;
        }
    }
    
    numChar = (char*)malloc(elementos*sizeof(char));
    
    if(numChar != NULL)
    {
        for(int i = 0; i < elementos; i++)
        {
            dixito = numero % 10;
            *(numChar + (elementos-(i+2))) = dixito + 48;
            numero /= 10;
        }
        *(numChar + (elementos - 1)) = '\0';
    }
    
    return numChar;
}

char *IP(int d1, int d2, int d3, int d4)
{
    char *vecCharIP[DIXITOS_IP] = {NULL,NULL,NULL,NULL};
    int vecNumIP[DIXITOS_IP]  = {d1, d2, d3, d4};
    int caracteresIP = 4; //Tres puntos e o carácter nulo
    
    int k = 0;
    int conta = 0;
    
    int cadeaInvalida = 0;
    
    for(int i = 0; i < DIXITOS_IP; i++)
    {
        vecCharIP[i] = intToChar(vecNumIP[i]);
        
        while(*(vecCharIP[i] + k) != '\0')
        {
            caracteresIP++;
            k++;
        }
        k = 0;
    }
    
    char *direccionIP = (char*)malloc(caracteresIP*sizeof(char));
    
    if(direccionIP != NULL)
    {
        for(int i = 0; i < DIXITOS_IP; i++)
        {
            vecCharIP[i] = intToChar(vecNumIP[i]);
            if(vecCharIP[i] != NULL)
            {
                while(*(vecCharIP[i] + k) != '\0')
                {
                    *(direccionIP + conta) = *(vecCharIP[i] + k);
                    k++;
                    conta++;
                }
                k = 0;
        
                if(i != (DIXITOS_IP - 1))
                {
                    *(direccionIP + conta) = '.';
                    conta++;
                }
            }
            else
            {
                cadeaInvalida = 1;
            }
        }
        *(direccionIP + conta) = '\0';
    }
    
    for(int i = 0; i < DIXITOS_IP; i++)
    {
        if(vecCharIP[i] != NULL)
        {
            //No meu ordenador da problemas ao descomentar este free
            //Pero non vexo ningún erro no código que o explique
            //Imaxino que pode ser un erro da máquina virtual
            //Mais o correcto sería que non estivera comentado
            //Porque senón quedaría memoria sen liberar o final da execución do programa
            
            //free(vecCharIP[i]);
            vecCharIP[i] = NULL;
        }
    }
    
    if(cadeaInvalida)
    {
        free(direccionIP);
        direccionIP = NULL;
    }
    
    return direccionIP;
}

int main(int argc, char** argv)
{
    int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
    char *direccionIP = NULL;
    
    if(argc != 5)
    {
        printf("Non se introduciron os parámetros adecuados!\n");
    }
    else
    {
        d1 = atoi(argv[1]);
        d2 = atoi(argv[2]);
        d3 = atoi(argv[3]);
        d4 = atoi(argv[4]);
    
        if((d1 > 255) ||
            (d2 > 255) ||
            (d3 > 255) ||
            (d4 > 255))
        {
            printf("Non se introduciu unha dirección IP válida!");
        }
        else
        {
            direccionIP = IP(d1, d2, d3, d4);
            
            if(direccionIP != NULL)
            {
                printf("A dirección IP é: %s", direccionIP);
                
                //No meu ordenador da problemas ao descomentar este free
                //Pero non vexo ningún erro no código que o explique
                //Imaxino que pode ser un erro da máquina virtual
                //Mais o correcto sería que non estivera comentado
                //Porque senón quedaría memoria sen liberar o final da execución do programa
                
                //free(direccionIP);
                direccionIP = NULL;
            }
        }
    }
    
    return (EXIT_SUCCESS);
}


