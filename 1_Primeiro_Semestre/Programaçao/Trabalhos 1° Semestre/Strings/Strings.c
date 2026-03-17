#include <stdio.h>

int main (void)
{
    char string[200], ch;
    int j=0, i=0, k=0, contador=0, espacos=0;

    do
    {
        printf("Informe um texto: ");
        fflush(stdin);
        gets(string);

        for(i=0; string[i]!='\0'; i++)
        {
            if(string[i]==' ')
            {
                if(k==0)
                {
                    espacos++;
                }
                k=1;
            }
            else
            {
                k=0;
            }
        }

        int vetor[espacos];

        j=0;
        vetor[j]=0;
        contador=i;
        k=0;

        for(i=0; i<contador; i++)
        {
            if(string[i]==' ')
            {
                vetor[j]++;
                k=0;
            }
            else
            {
                if(k==0)
                {
                    j++;
                    vetor[j]=0;
                }
                k=1;
            }
        }
        printf("==== VETOR ====\n");
        for(i=0; i<=espacos; i++)
        {
            if(vetor[i]!=0)
            {
                printf("%-4d", vetor[i]);
            }
        }

        printf("\n\nDeseja repetir o programa? (S/N): ");
        scanf(" %c", &ch);
        printf("\n\n");

    }
    while(ch!='n'&&ch!='N');
}

