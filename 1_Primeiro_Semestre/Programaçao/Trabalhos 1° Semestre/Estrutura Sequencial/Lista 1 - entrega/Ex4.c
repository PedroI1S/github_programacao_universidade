#include <stdio.h>

int main (void)
{
    int num, result;

    printf("Numero inteiro: ");
    scanf("%d", &num);

    result = ((num * 3) + 1) + ((num * 2) - 1);

    printf("\nA soma do sucessor de seu triplo com o antecessor de seu dobro eh: %d", result);

    return 0;
}
