#include <stdio.h>

int main (void)
{
    int i=0, j=0, conts=0, contsub=0;
    char ch, string[200], substring[200];

    do
    {
        printf("Informe uma string: ");
        fflush(stdin);
        gets(string);

        printf("informe uma substring: ");
        fflush(stdin);
        gets(substring);

         for(i=0; string[i]!='\0'; i++)
        {
            conts++;
        }
         for(i=0; substring[i]!='\0'; i++)
        {
            contsub++;
        }

        char conjunta[(conts+contsub)];
        j=0;

        for(i=0; i<=(conts+contsub); i++)
        {
            if(i<conts)
            {
                conjunta[i]=string[i];
            }
            else
            {
                conjunta[i]=substring[j];
                j++;
            }
        }

        printf("\n%s", conjunta);

        printf("\n\nDeseja continuar o programa? (S/N): ");
        scanf(" %c", &ch);
        printf("\n\n");

    }
    while(ch!='n'&&ch!='N');
}


