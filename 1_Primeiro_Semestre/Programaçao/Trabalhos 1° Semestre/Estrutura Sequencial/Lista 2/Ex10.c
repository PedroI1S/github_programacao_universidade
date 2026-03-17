#include <stdio.h>

int main()
{
    int num1, num2, num3;
    int soma, produto, menor, maior;
    float media;

    printf("Digite o primeiro numero: ");
    scanf("%d", &num1);

    printf("Digite o segundo numero: ");
    scanf("%d", &num2);

    printf("Digite o terceiro numero: ");
    scanf("%d", &num3);

    // Calcula a soma
    soma = num1 + num2 + num3;

    // Calcula a media
    media = (float)soma / 3;

    // Calcula o produto
    produto = num1 * num2 * num3;

    // Encontra o menor numero
    menor = num1;
    if(num2 < menor)
        menor = num2;
    if(num3 < menor)
        menor = num3;

    // Encontra o maior numero
    maior = num1;
    if(num2 > maior)
        maior = num2;
    if(num3 > maior)
        maior = num3;

    // Imprime os resultados
    printf("Soma: %d\n", soma);
    printf("Media: %.2f\n", media);
    printf("Produto: %d\n", produto);
    printf("Menor: %d\n", menor);
    printf("Maior: %d\n", maior);

    return 0;
}
