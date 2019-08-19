#include <stdio.h>
#include <stdlib.h>

int main() {
    
    FILE *ptf_d; //Arquivo onde se almacenan os datos
    FILE *ptf_a; //Arquivo onde se gardaran as sumas parciais
    
    int sumaParcial = 0, temp = 0, erroPeche = 0;
    if((ptf_d = fopen("datos.dat","rt")) == NULL) //Modo lectura de texto
    {
        printf("Non se conseguiu abrir o arquivo (datos.dat)!");
        return (EXIT_FAILURE);
    }
    if((ptf_a = fopen("acum.dat","w+")) == NULL) //Modo lectura e escritura nun novo arquivo
    {
        printf("Non se conseguiu crear o arquivo (acum.dat)!");
        return (EXIT_FAILURE);
    }
    
    while(feof(ptf_d) == 0) //Non se chegou o final do arquivo
    {
        fscanf(ptf_d,"%d",&temp); //Leemos un dato de datos.dat
        if(feof(ptf_d) == 0)
        {
            sumaParcial += temp; //Sumámosllo aos anteriores
        }
        fprintf(ptf_a,"%d\n",sumaParcial); //Gardamos o resultado en acum.dat
    }
    
    //Pechamos os arquivos
    erroPeche = fclose(ptf_d);
    if(erroPeche != 0)
    {
        printf("O arquivo (datos.dat) non se pechou correctamente!");
        return (EXIT_FAILURE);
    }
    
    erroPeche = fclose(ptf_a);
    if(erroPeche != 0)
    {
        printf("O arquivo (acum.dat) non se pechou correctamente!");
        return (EXIT_FAILURE);
    }
    
    printf("Operación realizada con éxito!\n");
    return (EXIT_SUCCESS);
}
