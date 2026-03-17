#include<stdio.h>
#include<locale.h>

int main (void)
{
    setlocale(LC_ALL, "Portuguese");
    int num,i=0, soma=0, produto=1, j=0, k=0;
    float sodt=-1;

    printf("Informe um numero maior que 2: ");
    scanf("%d", &num);

    for(i=2; i<=num; i+=2)
    {
        printf("%-6d", i);

        if(i%9==0)
        {
            printf("\n");
        }

        soma += i;

        if((i+1)%9==0)
        {
            produto *= (i+1);
        }

        sodt += i+(i-1);
        j+=2;
    }

    printf("\n\nSoma dos pares: %d", soma);
    if(produto==1)
    {
        printf("\nProduto dos impares divisíveis por 9: não há nenhum numero que corresponda as condições no intervalo");
    }
    else
    {
        printf("\nProduto dos impares divisíveis por 9: %d", produto);
    }
    printf("\nMedia de todos os numeros dentro do intervalo: %.2f\n\n", (sodt+num)/j);

    return 0;
}
