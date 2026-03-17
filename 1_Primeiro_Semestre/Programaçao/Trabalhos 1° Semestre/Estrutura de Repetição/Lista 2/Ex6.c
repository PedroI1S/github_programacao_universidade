/* Ler números inteiros. Prosseguir a leitura até ser informado o valor zero que não deve ser considerado nos cálculos. Informar:
a) Quantos valores positivos foram informados.
b) Quantos valores negativos e pares foram informados. Exemplo: Se a entrada for -1, -2, -3, deverá retornar 1, pois tem apenas um
número negativo que é par.
c) A média dos valores divisíveis por 3 informados. Usar a funcão abs() (que pertence a biblioteca stdlib) para converter os valores
negativos em positivos. Validar para não fazer divisão por zero no cálculo da média.*/
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int num = 1, positivos = 0, negativos = 0, total = 0, cont = 0;

    while (num != 0)
    {
        printf("Informe um numero inteiro: ");
        scanf("%d", &num);

        if (num > 0)
        {
            positivos++;
        }
        else
        {
            num = abs(num);
            if (num % 2 == 0)
            {
                negativos++;
            }
        }
        if (num % 3 == 0 && num != 0)
        {
            total += num;
            cont++;
        }
    }
    printf("Valores positivos: %d\n", positivos);
    printf("Valores negativos e pares: %d\n", negativos);
    if (cont > 0)
    {
        printf("Media dos valores divisiveis por tres informados: %f\n", (float)total / cont);
    }
    else
    {
        printf("Nao foram informados valores divisiveis por tres.\n");
    }

    return 0;
}
