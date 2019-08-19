#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ETAPAS 5
#define MAX_DATOS 100

#define HORAS_SEGUNDOS 3600
#define MINUTOS_SEGUNDOS 60

#define DIAS_ANO 365
#define DIAS_MES 31

#define PENALIZACION 5 //Penalización por abandono nunha etapa

#define EXITO 0
#define FRACASO -1 //Fallo abrindo ou pechando un arquivo

struct
{
    int dia;
    int mes;
    int ano;
} typedef data; //Representa a data dunha etapa
    
struct
{
    int horas;
    int minutos;
    int segundos;
} typedef tempo; //Tempo realizado nunha etapa

struct
{
    int dorsal;
    char nome[50];
    data datasEtapas[NUM_ETAPAS];
    tempo temposEtapas[NUM_ETAPAS];
} typedef datosCiclista; //Datos de cada ciclista

int introducirDatosCiclistas(int numDatos);
int introducirDatosEstrutura(datosCiclista *datos, int numDatos);

int calcularAbandonos(datosCiclista *datos, int numDatos);

int determinarDatosIniciais();
int leerDatosCiclistas(datosCiclista *datos, int numDatos, int N);
int introducirResultadosEtapa(datosCiclista *datos, int numDatos);
int determinarLider(datosCiclista *datos, int numDatos);
int mostrarDatos(int numDatos);

void ordenarPorDorsal(datosCiclista *datos, int N);

//Contamos os datos que hai inicialmente no arquivo
//Non se realizan comprobacións para determinar se ten o formato adecuado
//Contamos o número de liñas pois os datos de cada ciclista están separados por liñas
int determinarDatosIniciais()
{
    FILE *ptf;
    int erroPeche = 0;
    
    if((ptf = fopen("datos.dat","rt")) == NULL)
    {
        printf("Non se conseguiu abrir o arquivo (datos.dat)!\n");
        return (FRACASO);
    }
    
    char chr;
    int linas = 0;
    
    while(feof(ptf) == 0) //Non chegamos o final do arquivos
    {
        chr = fgetc(ptf);
        if(feof(ptf) == 0)
        {
            if(chr == '\n') //Detectouse un salto de liña
            {
                linas++;
            }
        }
    }
    
    erroPeche = fclose(ptf);
    if(erroPeche != 0)
    {
        printf("O arquivo (datos.dat) non se pechou correctamente!\n");
        return (FRACASO);
    }
    return linas;
}

//Función para ordenar o vector de estrutura según o número do dorsal do ciclista
void ordenarPorDorsal(datosCiclista *datos, int N) 
{
    int tempMin = 1000;
    int indice = 0;
    datosCiclista temp;
    for(int i = 0; i < N; i++)
    {
        tempMin = datos[i].dorsal;
        for(int j = i; j < N;j++) //Buscamos o mínimo do resto dos datos
        {
            if(tempMin > datos[j].dorsal)
            {
                tempMin = datos[j].dorsal;
                indice = j;
            }
        }
        if(i != indice) //O dorsal mínimo non é o dese mesmo ciclista
        {
            //Intercambiamos as posicións
            temp = datos[i];
            datos[i] = datos[indice];
            datos[indice] = temp;
        }
    }
}

//Función para introducir novos ciclistas no arquivo
//Podemos introducir unha cantidade arbitraria de datos pero despois
//existe a posiblidade de que non podamos cargar todos no vector
int introducirDatosCiclistas(int numDatos)
{
    int tempDia = 0, tempMes = 0, tempAno = 0;
    data datasEtapas[NUM_ETAPAS] = {
        [0].ano=2017,[0].mes=9,[0].dia=4,
        [1].ano=2017,[1].mes=10,[1].dia=4,
        [2].ano=2017,[2].mes=11,[2].dia=4,
        [3].ano=2017,[3].mes=11,[3].dia=4,
        [4].ano=2017,[4].mes=12,[4].dia=4};
    
    FILE* datas;
    int erroPeche = 0;
    
    //Lemos as datas dun arquivo de texto
    //Ses este non existe empregamos aquelas definidas por defecto
    if((datas = fopen("datasEtapas.dat","rt")) == NULL)
    {
        printf("Non se conseguiu abrir o arquivo (datasEtapas.dat)!\n");
    }
    else
    {
        for(int i = 0; i < NUM_ETAPAS; i++)
        {
            if(feof(datas) == 0)
            {
                fscanf(datas,"%d %d %d",&tempDia,&tempMes,&tempAno);
                if((tempDia > 0) && (tempDia <= 31) && 
                        (tempMes > 0) && (tempMes <= 12)) //A data debe ser válida senón úsase a por defecto
                {
                    datasEtapas[i].dia = tempDia;
                    datasEtapas[i].mes = tempMes;
                    datasEtapas[i].ano = tempAno;
                }
            }
        }
        erroPeche = fclose(datas);
        if(erroPeche != 0)
        {
            printf("O arquivo (datasEtapas.dat) non se pechou correctamente!\n");
        }
    }
    //Non se realiza comprobación de se a distribución das datas é lóxica
    
    FILE* ptf;
    
    datosCiclista temp;
    int opcion = 0;
    
    if(numDatos == 0) //Non hai datos no arquivo
    {
        if((ptf = fopen("datos.dat","wt")) == NULL)
        {
            printf("Non se conseguiu abrir o arquivo (datos.dat)!\n");
            return(FRACASO);
        }
    }
    else //Xa hai datos no arquivo
    {
        if((ptf = fopen("datos.dat","at")) == NULL)
        {
            printf("Non se conseguiu abrir o arquivo (datos.dat)!\n");
            return(FRACASO);
        }
    }
    
    //Inicializamos as datas e facemos nulos todos os tempos
    for(int i = 0; i < NUM_ETAPAS; i++)
    {
        temp.temposEtapas[i].horas = 0;
        temp.temposEtapas[i].minutos = 0;
        temp.temposEtapas[i].segundos = 0;
        temp.datasEtapas[i].ano = datasEtapas[i].ano;
        temp.datasEtapas[i].mes = datasEtapas[i].mes;
        temp.datasEtapas[i].dia = datasEtapas[i].dia;
    }
    
    do //Introducimos os datos do cilista e valores nulos nos tempos das etapas
    {
        printf("Introduce o dorsal do ciclista: ");
        scanf("%d",&temp.dorsal);
        printf("Introduce o nome do ciclista (sen espazos): ");
        scanf("%s",temp.nome);
        fprintf(ptf, "%d %s ", temp.dorsal,temp.nome);
        for(int i = 0; i < NUM_ETAPAS; i++)
        {
            if(i < (NUM_ETAPAS -1))
            {
                fprintf(ptf,"%d %d %d %d %d %d ",
                        temp.datasEtapas[i].dia,
                        temp.datasEtapas[i].mes,
                        temp.datasEtapas[i].ano,
                        temp.temposEtapas[i].horas,
                        temp.temposEtapas[i].minutos,
                        temp.temposEtapas[i].segundos);
            }
            else //Queremos un salto de liña para separar os distintos ciclistas
            {
                fprintf(ptf,"%d %d %d %d %d %d\n",
                        temp.datasEtapas[i].dia,
                        temp.datasEtapas[i].mes,
                        temp.datasEtapas[i].ano,
                        temp.temposEtapas[i].horas,
                        temp.temposEtapas[i].minutos,
                        temp.temposEtapas[i].segundos);
            }
            
        }
        numDatos++;
        
        printf("Desexa continuar introducindo datos? (Non: 0, Si: 1): ");
        scanf("%d",&opcion);
        
    } while(opcion != 0); //Podemos seguir introducindo datos
    
    erroPeche = fclose(ptf);
    if(erroPeche != 0)
    {
        printf("O arquivo (datos.dat) non se pechou correctamente!\n");
        return(FRACASO);
    }
    
    return numDatos;
}

//Volcamos os datos da estrutura no arquivo
//Para actualizar este coas modificacións que se puideron facer cos datos
int introducirDatosEstrutura(datosCiclista *datos, int numDatos)
{
    FILE* ptf;
    int erroPeche = 0;
    
    if(numDatos != 0)
    {
        if((ptf = fopen("datos.dat","wt")) == NULL)
        {
            printf("Non se conseguiu abrir o arquivo (datos.dat)!\n");
            return (FRACASO);
        }
        else
        {
            for(int i = 0; i < numDatos; i++)
            {
                fprintf(ptf,"%d %s ",datos[i].dorsal,datos[i].nome);
                for(int j = 0; j < NUM_ETAPAS; j++)
                {
                    if(j < (NUM_ETAPAS -1))
                    {
                        fprintf(ptf,"%d %d %d %d %d %d ",
                            datos[i].datasEtapas[j].dia,
                            datos[i].datasEtapas[j].mes,
                            datos[i].datasEtapas[j].ano,
                            datos[i].temposEtapas[j].horas,
                            datos[i].temposEtapas[j].minutos,
                            datos[i].temposEtapas[j].segundos);
                    }
                    else //Queremos un salto de liña para separar os distintos ciclistas
                    {
                        fprintf(ptf,"%d %d %d %d %d %d\n",
                            datos[i].datasEtapas[j].dia,
                            datos[i].datasEtapas[j].mes,
                            datos[i].datasEtapas[j].ano,
                            datos[i].temposEtapas[j].horas,
                            datos[i].temposEtapas[j].minutos,
                            datos[i].temposEtapas[j].segundos);
                    }
                }
            }
        }
    }
    erroPeche = fclose(ptf);
    if(erroPeche != 0)
    {
        printf("O arquivo (datos.dat) non se pechou correctamente!\n");
        return (FRACASO);
    }
    return (EXITO);
}

//Gardamos os datos do arquivo nun vector de estruturas
int leerDatosCiclistas(datosCiclista *datos, int numDatos, int N)
{
    int erroPeche = 0;
    FILE* ptf;
    
    if((ptf = fopen("datos.dat","rt")) == NULL)
    {
        printf("Non se conseguiu abrir o arquivo (datos.dat)!\n");
        return (FRACASO);
    }
    
    if(numDatos == 0)
    {
        printf("O ficheiro esta baleiro!\n");
    }
    else if(numDatos > N) //Hai máis datos que os que se poden gardar no vector
    {
        printf("Non se poden gardar máis de %d datos\n", MAX_DATOS);
    }
    else
    {
        for(int i = 0; i < numDatos; i++)
        {
            fscanf(ptf,"%d %s",&datos[i].dorsal,datos[i].nome);
            for(int j = 0; j < NUM_ETAPAS; j++)
            {
                fscanf(ptf,"%d %d %d %d %d %d",&datos[i].datasEtapas[j].dia,
                        &datos[i].datasEtapas[j].mes,
                        &datos[i].datasEtapas[j].ano,
                        &datos[i].temposEtapas[j].horas,
                        &datos[i].temposEtapas[j].minutos,
                        &datos[i].temposEtapas[j].segundos);
                
            }
        }
    }
    
    erroPeche = fclose(ptf);
    if(erroPeche != 0)
    {
        printf("O arquivo (datos.dat) non se pechou correctamente!\n");
        return (FRACASO);
    }
    return (EXITO);
}

//Función para introducir os tempos por etapa de cada ciclista
int introducirResultadosEtapa(datosCiclista *datos, int numDatos)
{
    int numEtapa = 0;
    int tempSegundos = 0, tempMinutos = 0, tempHoras = 0;
    
    int datosValidos = 0;
    
    if(numDatos == 0)
    {
        printf("Non hai datos gardados!\n");
    }
    else
    {
        do
        {
            printf("Introduce o número da etapa (1-%d): ",NUM_ETAPAS);
            scanf("%d",&numEtapa);
            if((numEtapa < 1) || (numEtapa > NUM_ETAPAS)) //Débese introducir unha etapa válida
            {
                printf("Introduce unha etapa válida!\n");
                datosValidos = 0;
            }
            else
            {
                datosValidos = 1;
            }
        } while(!datosValidos);
        
        numEtapa--; //Usaremos a etapa para acceder a unha posición do vector
        
        for(int i = 0; i < numDatos; i++)
        {
            //Non hai ningún tempo introducido para ese ciclista nesa etapa
            if(datos[i].temposEtapas[numEtapa].horas == 0 &&
                        datos[i].temposEtapas[numEtapa].minutos == 0 &&
                        datos[i].temposEtapas[numEtapa].segundos == 0)
            {
            
                printf("Dorsal: %d, Nome: %s\n",datos[i].dorsal, datos[i].nome);
                do
                {
                    printf("Introduce o seu tempo: (Horas Minutos Segundos): ");
                    scanf("%d %d %d",&tempHoras,&tempMinutos,&tempSegundos); 
                    //O tempo debe ser válido
                    if((tempHoras > 24) || (tempMinutos > 60) || (tempSegundos > 60))
                    {
                        printf("Os datos non son válidos!\n");
                        datosValidos = 0;
                    }
                    else
                    {
                        datos[i].temposEtapas[numEtapa].horas = tempHoras;
                        datos[i].temposEtapas[numEtapa].minutos = tempMinutos;
                        datos[i].temposEtapas[numEtapa].segundos = tempSegundos;
                        datosValidos = 1;
                    } 
                } while(!datosValidos);
            }
        }
    }
    
    introducirDatosEstrutura(datos, numDatos); //Actualizamos o arquivo ca nova informacion
    return(EXITO);
}

int calcularAbandonos(datosCiclista *datos, int numDatos)
{
    data dataUsuario;
    
    int abandonos = 0, abandonosTotais = 0;  
    
    int datosValidos = 0;
    
    if(numDatos == 0)
    {
        printf("Non hai datos gardados!\n");
    }
    else
    {
        do
        {
            printf("Introduce a data da etapa(Dia Mes Ano): ");
            scanf("%d %d %d",&dataUsuario.dia,&dataUsuario.mes,&dataUsuario.ano);
            if((dataUsuario.dia > 0) && (dataUsuario.dia <= 31) && 
                        (dataUsuario.mes > 0) && (dataUsuario.mes <= 12)) //A data debe ser válida senón úsase a por defecto
            {
                datosValidos = 1;
            }
            else
            {
                printf("Introduce unha data válida!\n");
                datosValidos = 0;
            }
           
        } while(!datosValidos);
        
        for(int i = 0; i < numDatos; i++)
        {
            abandonos = 0; //Reiniciamos o contador de abandonos individuais
            printf("Dorsal: %d, Nome: %s\n",datos[i].dorsal, datos[i].nome);
            for(int j = 0; j < NUM_ETAPAS; j++)
            {
                //Se os tempos nesa etapa son nulos
                if(datos[i].temposEtapas[j].horas == 0 &&
                        datos[i].temposEtapas[j].minutos == 0 &&
                        datos[i].temposEtapas[j].segundos == 0)
                {
                    //Se esa etapa tivo lugar antes ou na mesma data introducida polo usuario
                    if((dataUsuario.ano*DIAS_ANO+dataUsuario.mes*DIAS_MES+dataUsuario.dia)
                            >= (datos[i].datasEtapas[j].ano*DIAS_ANO+ 
                            datos[i].datasEtapas[j].mes*DIAS_MES+ 
                            datos[i].datasEtapas[j].dia))
                    {
                        printf("Abandonou na etapa: %d\n",j+1);
                        abandonos++;
                        abandonosTotais++;
                    }
                }
            }
            printf("O ciclista abandonou en %d etapa(s)\n",abandonos);
        }
        printf("En total hubo %d abandono(s)\n",abandonosTotais);
    }
    
    return (EXITO);
}


//Función para determinar o líder da volta ciclista
int determinarLider(datosCiclista *datos, int numDatos)
{
    int tempMin = 0, tempSum = 0;
    int indice = 0;
    
    if(numDatos == 0)
    {
        printf("Non hai datos no arquivo!\n");
    }
    else
    {
        for(int i = 0; i < numDatos; i++)
        {
            tempSum = 0;
            for(int j = 0; j < NUM_ETAPAS; j++)
            {
                //Introducimos unha penalización por abandono
                if(datos[i].temposEtapas[j].horas == 0 &&
                        datos[i].temposEtapas[j].minutos == 0 &&
                        datos[i].temposEtapas[j].segundos == 0)
                {
                    tempSum += PENALIZACION*HORAS_SEGUNDOS; 
                }
                //Se non abandonou sumamos o tempo realizado nesa etapa
                else
                {
                    tempSum += datos[i].temposEtapas[j].horas*HORAS_SEGUNDOS;
                    tempSum += datos[i].temposEtapas[j].minutos*MINUTOS_SEGUNDOS;
                    tempSum += datos[i].temposEtapas[j].segundos;
                }
            }
            if(i == 0) //O primeiro dato será o primeiro tempo mínimo
            {
                tempMin = tempSum;
                indice = i; //Gardamos a posición do líder temporal
            }
            else
            {
                if(tempSum < tempMin) //Hai un ciclista cun tempo mellor
                {
                    tempMin = tempSum;
                    indice = i;  //Gardamos a posición do líder temporal
                }
            }
        }
        printf("O actual líder é:\nDorsal: %d Nome: %s\n",datos [indice].dorsal,datos[indice].nome);
    }
    
    return (EXITO);
}

//Mostramos na consola os datos almacenados no arquivo
int mostrarDatos(int numDatos)
{
    int erroPeche = 0;
    FILE* ptf;
    
    datosCiclista temp;
    
    if((ptf = fopen("datos.dat","rt")) == NULL)
    {
        printf("Non se conseguiu abrir o arquivo (datos.dat)!\n");
        return (FRACASO);
    }
    
    if(numDatos == 0)
    {
        printf("Non hai datos no arquivo!\n");
    }
    else
    {
        for(int i = 0; i < numDatos; i++)
        {
           fscanf(ptf,"%d %s",&temp.dorsal,temp.nome);
           printf("Dorsal: %d, Nome: %s\nResultados por etapa:\n",temp.dorsal,temp.nome);
           for(int j = 0; j < NUM_ETAPAS; j++)
           {
               fscanf(ptf,"%d %d %d %d %d %d",&temp.datasEtapas[j].dia,
                        &temp.datasEtapas[j].mes,
                        &temp.datasEtapas[j].ano,
                        &temp.temposEtapas[j].horas,
                        &temp.temposEtapas[j].minutos,
                        &temp.temposEtapas[j].segundos);
               printf("%dª Etapa: %02d/%02d/%04d %02d:%02d:%02d\n",j+1,
                       temp.datasEtapas[j].dia,
                       temp.datasEtapas[j].mes,
                       temp.datasEtapas[j].ano,
                       temp.temposEtapas[j].horas,
                       temp.temposEtapas[j].minutos,
                       temp.temposEtapas[j].segundos);
           }
        }
    }
    
    erroPeche = fclose(ptf);
    if(erroPeche != 0)
    {
        printf("O arquivo (datos.dat) non se pechou correctamente!\n");
        return (FRACASO);
    }
    return(EXITO);
}

//Temos en menú na función main para escoller que operacións realizar cos datos
int main()
{
    int opcion = 0;
    datosCiclista datos[MAX_DATOS];
    int numDatos = 0;
    int tempDatos = 0; 
    
    tempDatos = determinarDatosIniciais(); //Comprobamos se xa hai datos no arquivo
    if(tempDatos != FRACASO)
    {
        numDatos = tempDatos;
        leerDatosCiclistas(datos,numDatos,MAX_DATOS);
    }
    else
    {
        numDatos = 0;
    }
    do
    {
        printf("Que desexas facer: \n"
                "(0)Introducir datos\n"
                "(1)Introducir resultados etapa\n"
                "(2)Calcular número abandonos\n"
                "(3)Determinar líder\n"
                "(4)Mostrar datos\n"
                "(5)Ordenar datos por dorsal\n"
                "(6)Saír: ");
        scanf("%d", &opcion);
        switch(opcion)
        {
            case 0:
                tempDatos = introducirDatosCiclistas(numDatos);
                if(tempDatos != FRACASO)
                {
                    numDatos = tempDatos;
                }
                leerDatosCiclistas(datos,numDatos,MAX_DATOS);
                break;
            case 1:
                leerDatosCiclistas(datos,numDatos,MAX_DATOS);
                introducirResultadosEtapa(datos, numDatos);
                break;
            case 2:
                leerDatosCiclistas(datos,numDatos,MAX_DATOS);
                calcularAbandonos(datos, numDatos);
                break;
            case 3:
                leerDatosCiclistas(datos,numDatos,MAX_DATOS);
                determinarLider(datos, numDatos);
                break;
            case 4:
                mostrarDatos(numDatos);
                break;
            case 5:
                leerDatosCiclistas(datos,numDatos,MAX_DATOS);
                ordenarPorDorsal(datos, numDatos);
                introducirDatosEstrutura(datos, numDatos);
                break;
            default:
                opcion = 6;
                break;
        }
        
    } while(opcion != 6);
    
    return(EXITO);
}