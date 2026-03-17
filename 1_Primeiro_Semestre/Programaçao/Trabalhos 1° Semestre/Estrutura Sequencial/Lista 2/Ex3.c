#include <stdio.h>

int main (void)
{
    float imc, altura, peso;

    printf("insira sua altura: ");
    scanf("%f", &altura);
    printf("insira deu peso: ");
    scanf("%f", &peso);

    imc = peso / (altura * altura);

    if (peso < 0 || peso > 300 || altura < 0 || altura > 2.5)
    {
        printf("Valor inserido eh invalido");
    }
    else
    {
        if(imc > 0 && imc < 20)
    {
        printf("IMC:%.2f, Abaixo do peso", imc);
    }
        else
        {
            if(imc >= 20 && imc <25)
            {
            printf("IMC:%.2f, Peso normal", imc);
            }
            else
                if(imc >=25 && imc < 30)
            {
                printf("IMC:%.2f, Acima do peso", imc);
            }
            else
            {
                if(imc >=30 && imc <34)
                {
                    printf("IMC:%.2f, Obeso", imc);
                }
                else
                {
                    printf("IMC:%.2f, Muito obeso", imc);
                }
            }
        }
    }

    return 0;
}
