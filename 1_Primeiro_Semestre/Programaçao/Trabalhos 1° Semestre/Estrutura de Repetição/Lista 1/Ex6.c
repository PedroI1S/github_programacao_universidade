#include<stdio.h>
#include<locale.h>

int main (void)
{
    int i, fatorial;
    long long int resultado=1;

    printf("Informe um numero: ");
    scanf("%d", &fatorial);

    for(i=fatorial; i>=1 ; i--)
    {
        if(i==fatorial)
        {
            printf("%d! = ", fatorial);
        }
        if(i==1)
        {
            printf("%d", i);
        }
        else
        {
            printf("%d  *  ", i);
        }
        resultado *=i;
    }
    printf(" = %lld", resultado);

    return 0;
}
