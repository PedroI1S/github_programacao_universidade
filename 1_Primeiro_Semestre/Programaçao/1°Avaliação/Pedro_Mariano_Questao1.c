#include<stdio.h>

int main (void)
{
    unsigned int num, i=1, valor_antigo=0, valor_novo=0, crescente=0;

    printf("Digite o valor de n: ");
    scanf("%d", &num);
    printf("\n");

    while(num>=i)
    {
        valor_antigo=valor_novo;
        valor_novo=0;
        printf("Informe o valor %d: ", i);
        scanf("%d", &valor_novo);

        if(valor_antigo>valor_novo)
        {
            crescente=1;
        }
        i++;
    }
    if(crescente==0)
    {
        printf("Os numeros estao em ordem crescente.\n");
    }
    else
    {
        printf("Os numeros nao estao em ordem crescente.\n");
    }
    return 0;
}
