#include <stdio.h>
#include <stdlib.h>

float encontprom(int num1, int num2); //Promedio de dous valores enteiros
int atoparMCD(int num1, int num2); //Máximo Común Divisor de dous enteiros

float encontprom(int num1, int num2) //Media de dous valores
{
    float promedio;
    promedio = (num1 + num2) / 2.0;
    return promedio;
}

int atoparMCD(int num1, int num2) 
{
    int dividendo, divisor, resto;
    //Algoritmo de Euclides
    dividendo = num1;
    divisor = num2;
    resto = dividendo % divisor;
    while(resto != 0)
    {
        dividendo = divisor;
        divisor = resto;
        resto = dividendo % divisor;
    }
    return divisor;
}

int main()
{
    int a,b;
    float resultado;
    printf("Dame dous valores enteiros: ");
    scanf("%d %d",&a,&b);
    resultado = encontprom(a, b);
    printf("Promedio=%.02f\n",resultado); //Mostramos o promedio con dúas cifras decimais
    
    printf("Dame dous valores enteiros: ");
    scanf("%d %d",&a,&b);;
    printf("MCD=%d\n",atoparMCD(a,b));
    
    return (EXIT_SUCCESS);
}
