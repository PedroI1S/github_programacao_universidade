#include <stdio.h>
#include <locale.h>

int main (void)
{
    setlocale(LC_ALL, "Portuguese");
    int op, a, b, c;

    printf("Menu de opções:\nOpção 1 - Mostra os números em ordem crescente\nOpção 2 - Mostra os números em ordem decrescente\nOpção 3 - Mostra os números que são múltiplos de 2\nDigite a opção desejada:");
    scanf("%d", &op);

    switch(op)
    {
    case 1:
        printf("\nInforme três valores inteiros:\n-a:");
        scanf("%d", &a);
        printf("-b:");
        scanf("%d", &b);
        printf("-c:");
        scanf("%d", &c);

        printf("---------------------------------------------------");

        if(a>=b && a>c)
        {
            if(b>c)
            {
                printf("\nOrdem crescente: %d - %d - %d\n", c, b, a);
            }
            else
            {
                printf("\nOrdem crescente: %d - %d - %d\n", b, c, a);
            }
        }
        else if(b>=c && b>a)
        {
            if(a>c)
            {
                printf("\nOrdem crescente: %d - %d - %d\n", c, a, b);
            }
            else
            {
                printf("\nOrdem crescente: %d - %d - %d\n", a, c, b);
            }
        }
        else if(c>=a && c>b)
        {
            if(a>b)
            {
                printf("\nOrdem crescente: %d - %d - %d\n", b, a, c);
            }
            else
            {
                printf("\nOrdem crescente: %d - %d - %d\n", a, b, c);
            }
        }
        else
        {
            printf("\nOs números são iguais\n");
        }
        break;

    case 2:
        printf("\nInforme três valores inteiros:\n-a:");
        scanf("%d", &a);
        printf("-b:");
        scanf("%d", &b);
        printf("-c:");
        scanf("%d", &c);

        printf("---------------------------------------------------");

        if(a>b && a>c)
        {
            if(b>c)
            {
                printf("\nOrdem decrescente: %d - %d - %d\n", a, b, c);
            }
            else
            {
                printf("\nOrdem decrescente: %d - %d - %d\n", a, c, b);
            }
        }
        else if(b>c && b>a)
        {
            if(a>c)
            {
                printf("\nOrdem decrescente: %d - %d - %d\n", b, a, c);
            }
            else
            {
                printf("\nOrdem decrescente: %d - %d - %d\n", b, c, a);
            }
        }
        else if(c>a && c>b)
        {
            if(a>b)
            {
                printf("\nOrdem decrescente: %d - %d - %d\n", c, a, b);
            }
            else
            {
                printf("\nOrdem decrescente: %d - %d - %d\n", c, b, a);
            }
        }
        else
        {
            printf("\nOs números são iguais\n");
        }
        break;

    case 3:
        printf("\nInforme três valores inteiros:\n-a:");
        scanf("%d", &a);
        printf("-b:");
        scanf("%d", &b);
        printf("-c:");
        scanf("%d", &c);

        printf("---------------------------------------------------\n");

        if(a%2==0)
        {
            if(b%2==0)
            {
                if(c%2==0)
                {
                    printf("Todos os números inseridos são múltiplos de 2.\n");
                }
                else
                {
                    printf("Apenas os números %d e %d são múltiplos de 2.\n", a, b);
                }
            }
            else if(c%2==0)
            {
                printf("Apenas os números %d e %d são múltiplos de 2.\n", a, c);
            }
            else
            {
                printf("Apenas o número %d é múltiplo de 2.\n", a);
            }
        }
        else if(b%2==0)
        {
            if(c%2==0)
            {
                printf("Apenas os números %d e %d são múltiplos de 2.\n", b, c);
            }
            else
            {
                printf("Apenas o número %d é múltiplo de 2.\n", b);
            }

        }
        else if(c%2==0)
        {
            printf("Apenas o número %d é múltiplo de 2.\n", c);
        }
        else
        {
            printf("Nenhum dos números digitados são múltplos de 2.\n");
        }

        break;

    default:
        printf("\nValor inválido, digite um dos números contidos no menu de opções.\n");
    }
    return 0;
}
