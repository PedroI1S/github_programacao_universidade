#include<stdio.h>

int main (void)
{
    int inf, sup, soma=0, valor_antigo=0, valor_novo=1, i=0;

    printf("Informe um limite inferior: ");
    scanf("%d", &inf);
    printf("Informe um limite superior: ");
    scanf("%d", &sup);

    while(inf<=sup)
    {
        printf("%-4d ==>", inf);

        while(i<=inf)
        {
            printf("%-5d", valor_novo);

            valor_novo+=valor_antigo;
            valor_antigo=valor_novo-valor_antigo;
            i++;
            soma+=valor_antigo;
        }
        i=0;
        valor_antigo=0;
        valor_novo=1;
        inf++;

        printf(" = %d", soma);
        soma=0;
        printf("\n");
    }

    return 0;
}
