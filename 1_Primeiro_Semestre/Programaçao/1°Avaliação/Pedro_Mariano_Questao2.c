#include<stdio.h>

int main (void)
{
    char ch, keep;
    int num, i, primos, soma, numeros, somadig, cont;

    do
    {
        //resetando as varianveis//
        soma=0;
        numeros=0;
        somadig=0;
        cont=0;

        do
        {
            printf("Informe um caractere: ");
            scanf(" %c", &ch);

            num=(int)ch;

            if(ch>='a' && ch<='z' || ch>='A' && ch<='Z')
            {
                //resetando as variaveis//
                primos=0;
                i=2;

                while(i<num)
                {
                    if(num%i==0)
                    {
                        primos=1;
                    }
                    i++;
                }

                if(primos==0)
                {
                    printf("%d eh primo\n", num);
                    soma+=num;
                }
                else
                {
                    printf("%d nao eh primo\n", num);
                }
                cont++;
            }
            else
            {
                if(ch!='0')
                {
                    numeros++;
                    cont++;
                }
            }

        }
        while(ch!='0');

        printf("\n\nSoma dos primos: %d", soma);
        printf("\nSoma dos digitos de %d: ", soma);

        while(soma>0)
        {
            somadig+=soma%10;
            soma=soma/10;
        }
        printf("%d", somadig);
        printf("\nPercentual de caracteres numeros: %d%%\n\n", (100*numeros)/cont);

        printf("Repetir a execucao do programa(S/N): ");
        //O espaço antes do "%c" automaticamente faz com que o scan ignore enter//
        scanf(" %c", &keep);

    }
    while(keep!='n'&&keep!='N');

    return 0;
}
