/*Ler um número e ler um dígito. Contar quantos dígitos o número possui. Exemplo:
É informado 5 como dígito:
55 – possui 2 dígitos cinco;
10 – possui nenhum dígito cinco;
1550 – possui dois dígitos cinco;
50050 – possui dois dígitos cinco.
Repetir o programa enquanto informados valores positivos.*/
#include<stdio.h>

int main (void)
{
    int dig, num, soma;
    char ch;

    do
    {
        do
        {
            printf("Informe um digito: ");
            scanf("%d", &dig);
            printf("\n");
        }
        while(dig>=10 || dig<0);

        do
        {
            printf("Digite um numero: ");
            scanf("%d", &num);

            if(num>0)
            {
                while(num>=9)
                {
                    if((num%10)%dig==0)
                    {
                        soma++;
                    }
                    num=num/10;
                }
             printf("O numer possui %d digitos igual a %d\n\n", soma, dig);
            }
            soma=0;
        }
        while(num!=0);

        printf("\n\nDeseja continuar o programa? (S/N): ");
        scanf(" %c", &ch);

    }while(ch!='n' && ch!='N');

    return 0;
}

