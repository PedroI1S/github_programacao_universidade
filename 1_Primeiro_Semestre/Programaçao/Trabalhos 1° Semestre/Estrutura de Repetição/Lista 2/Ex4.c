/*Ler caracteres e parar quando o usuário informar o caractere '0'. Utilizando a tabela ASCII contar quantos caracteres são letras
maiúsculas, quantos são letras minúsculas e quantos caracteres não são letras. Sugestão: utilizar o código numérico para comparar
(A equivale a 65, B a 66...).*/
#include<stdio.h>

int main (void)
{
    char ch;
    int M=0, m=0, nc=0;

    do
    {
        fflush(stdin);
        printf("\nInforme um caractere (informe O para parar):");
        scanf("%c", &ch);

        if(ch>='a' && ch<='z')
        {
            m++;
        }
        else if(ch>='A' && ch<='Z')
        {
            M++;
        }
        else
        {
            nc++;
        }
    }while(ch!='O');
    printf("\n\nLetras Maisculas: %d\nLetras Minusculas: %d\nNao sao letras: %d\n", M, m, nc);

    return 0;
}
