#include <stdio.h>
#include<locale.h>

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int limite_inferior, limite_superior, incremento, i;
    float soma_impares_div_35 = 0.0;
    int cont_impares_div_35 = 0;

    printf("Informe o limite inferior: ");
    scanf("%d", &limite_inferior);

    printf("Informe o limite superior: ");
    scanf("%d", &limite_superior);

    printf("Informe o incremento: ");
    scanf("%d", &incremento);

    // Verifica se os limites estão em ordem crescente ou decrescente
    if (limite_inferior > limite_superior)
    {
        int temp = limite_inferior;
        limite_inferior = limite_superior;
        limite_superior = temp;
    }

    for (i = limite_inferior; i <= limite_superior; i += incremento)
    {
        printf("%d ", i);

        // Verifica se o número é ímpar e divisível por 35
        if (i % 2 != 0 && i % 35 == 0)
        {
            soma_impares_div_35 += i;
            cont_impares_div_35++;
        }
    }

    // Calcula a média dos ímpares divisíveis por 35
    float media = 0.0;
    if (cont_impares_div_35 > 0)
    {
        media = soma_impares_div_35 / cont_impares_div_35;
    }

    printf("\nMédia dos ímpares divisíveis por 35: %.2f\n", media);

    return 0;
}
