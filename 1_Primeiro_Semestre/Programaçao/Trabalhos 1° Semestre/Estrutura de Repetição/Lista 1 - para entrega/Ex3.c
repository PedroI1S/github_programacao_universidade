/*Apresentar os números primos entre dois valores, que representam os limites inferior e superior,
respectivamente, de um intervalo, informados pelo usuário. Apresentá-los com n números por linha. n é
informado pelo usuário. Validar n para que seja maior que 0. Validar o limite inferior para seja maior que 1 e o
limite superior para que seja maior ou igual ao limite inferior. Implementar a repetição de programa.*/
#include<stdio.h>

int main (void)
{
    unsigned int inf, sup, linhas, i=2, j=0, primo=0;
    char ch;
    do
    {
        printf("Informe um limite superior: ");
        scanf("%d", &sup);
        printf("Informe um limite inforior: ");
        scanf("%d", &inf);
        printf("Informe quantos primos deseja mostrar por linha: ");
        scanf("%d", &linhas);

        while(inf<=sup)
        {
            while(i<inf)
            {
                if(inf%i==0)
                {
                    primo=1;
                }
                i++;
            }
            if(primo==0)
            {
                printf("%-5d", inf);
                j++;
                if(j==linhas)
                {
                    printf("\n");
                    j=0;
                }
            }

            inf++;
            primo=0;
            i=2;
        }
        printf("\n\nDeseja continar o programa: ");
        scanf(" %c", &ch);
    }
    while(ch!='n'&&ch!='N');
}
