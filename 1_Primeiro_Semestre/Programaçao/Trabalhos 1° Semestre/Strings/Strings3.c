#include<stdio.h>

void primeiro (char string[])
{
    int k=0;

    for(int i=0; string[i]!='\0'; i++)
    {
        if(string[i]==' ')
        {
            if(k==0)
            {
                printf("%c", string[(i+1)]);
            }
            k=1;
        }
        else
        {
            k=0;
        }
    }
}
void ultimo (char string[])
{
    int k=0;

    for(int i=0; string[i]!='\0'; i++)
    {
        if(string[i]==' ')
        {
            if(k==0)
            {
                printf("%c", string[(i-1)]);
            }
            k=1;
        }
        else
        {
            k=0;
        }
    }
}

int main (void)
{
    char string[100];
    int i, k=0, conts, palavras;

    do
    {
        printf("Informe uma string de ate 100 carcteres: ");
        fflush(stdin);
        gets(string);

        for(i=0; string[i]!='\0'; i++)
        {
            conts++;
        }
    }
    while(conts>100);

    for(i=0; string[i]!='\0'; i++)
    {
        if(string[i]==' ')
        {
            if(k==0)
            {
                palavras++;
            }
            k=1;
        }
        else
        {
            k=0;
        }
    }


    printf("\n\n\"%s\" possui %d palavras", string, palavras);
    printf("\n\nPrimeiro caractere de cada palavra da string");
    primeiro(string);
    printf("\nUltimo caractere de cada palavra da string");
    ultimo(string);
    printf("\n\nPrimeira palavra da string: ");
    for(i=0; string[i]!=' '; i++)
    {
            printf("%c", string[i]);
    }
}
