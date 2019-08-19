#include <stdio.h>
#include <stdlib.h>


//Estrutura para a fracción
struct 
{
    int numerador;
    int denominador;
} typedef fraccion;

fraccion SumaFraccions(fraccion fraccion1, fraccion fraccion2);
int atoparMCD(int num1, int num2); //Preciso para achar a fracción irredutible

fraccion SumaFraccions(fraccion fraccion1, fraccion fraccion2)
{
    fraccion fraccionSuma;
    int mcd;
    
    //Sumamos as fraccións
    fraccionSuma.denominador = fraccion1.denominador*fraccion2.denominador;
    fraccionSuma.numerador = fraccion1.numerador*fraccion2.denominador +
            fraccion2.numerador*fraccion1.denominador;
    
    //Simplificamos a fracción
    mcd = atoparMCD(fraccionSuma.numerador, fraccionSuma.denominador);
    fraccionSuma.numerador /= mcd;
    fraccionSuma.denominador /= mcd;
    
    return fraccionSuma;
}

//Determinamos o máximo común divisor mediante o algoritmo de Euclides
int atoparMCD(int num1, int num2) 
{
    int dividendo, divisor, resto;
    
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
    fraccion fraccion1, fraccion2, suma;
    printf("Introduce as fraccións a sumar: \n");
    printf("Fracción 1 (Numerador Denominador): ");
    scanf("%d %d",&fraccion1.numerador,&fraccion1.denominador);
    printf("Fracción 2 (Numerador Denominador): ");
    scanf("%d %d",&fraccion2.numerador,&fraccion2.denominador);
    suma = SumaFraccions(fraccion1, fraccion2);
    printf("A fracción irredutible resultado de sumar as fraccións é: %d/%d",
        suma.numerador,suma.denominador);
    
    return (EXIT_SUCCESS);
}


        