#include <stdio.h>

int VR (n1)
{
    int i=2, total=n1, contador=0;

    while(n1>=2)
    {
        n1-=i;
        i+=2;
        contador++;
    }

    if(n1==0)
    {
        printf("\n%d eh retangular ==> ", total);
        i=0;

        while(contador>0)
        {
            i+=2;
            printf("%d", i);

            contador--;
            if(contador>0)
            {
                printf(" + ");
            }
        }
        printf(" = %d", total);
    }
    else
    {
        i=0;
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
            printf("1 - Verifica se um numero eh retangular\n2 - Mostra os numeros retangulares em um intervalo\nEscolha uma opcao: ");
            scanf("%d", &opcao);
        }
        while (opcao != 1 && opcao != 2);

        if (opcao == 1)
        {
            do
            {
                printf("\nInsira um numero para a verificacao: ");
                scanf("%d", &num);
            }
            while(num<0);
            if (VR(num) == 0)
            {
                printf("\nO numero %d nao eh retangular", num);
            }
        }
        else
        {
            printf("\nInsira um limite inferior para gerar os retangulares: ");
            scanf("%d", &num);
            printf("Insira um limite superior: ");
            scanf("%d", &intervalo);

            while (num <= intervalo)
            {
                VR(num);
                num++;
            }
        }
        printf("\n\nDeseja continuar o programa (S/N): ");
        scanf(" %c", &ch);
        printf("\n\n");
    }
    while (ch != 'n' && ch != 'N');

    return 0;
}
