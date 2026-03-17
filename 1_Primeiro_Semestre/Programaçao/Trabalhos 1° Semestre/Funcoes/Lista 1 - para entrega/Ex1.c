#include <stdio.h>

int VT(int n1)
{
    int i;

    for (i = 1; i < n1; i++)
    {
        if (i * (i + 1) * (i + 2) == n1)
        {
            printf("\nO numero %d eh triangular ==> %d * %d * %d = %d", (i * (i + 1) * (i + 2)), i, (i + 1), (i + 2), (i * (i + 1) * (i + 2)));
            i = 0;
            break;
        }
    }
    return i;
}

int main(void)
{
    int num, intervalo, opcao;
    char ch;

    do
    {
        do
        {
            printf("1 - Verifica se um numero eh triangular\n2 - Mostra os numeros triangulares em um intervalo\nEscolha uma opcao: ");
            scanf("%d", &opcao);
        } while (opcao != 1 && opcao != 2);

        if (opcao == 1)
        {
            printf("\nInsira um numero para a verificacao: ");
            scanf("%d", &num);

            if (VT(num) != 0)
            {
                printf("\nO numero %d nao eh triangular", num);
            }
        }
        else
        {
            printf("\nInsira um limite inferior para gerar os triangulares: ");
            scanf("%d", &num);
            printf("Insira um limite superior: ");
            scanf("%d", &intervalo);

            while (num <= intervalo)
            {
                VT(num);
                num++;
            }
        }
        printf("\n\nDeseja continuar o programa (S/N): ");
        scanf(" %c", &ch);
        printf("\n\n\n");
    } while (ch != 'n' && ch != 'N');

    return 0;
}
