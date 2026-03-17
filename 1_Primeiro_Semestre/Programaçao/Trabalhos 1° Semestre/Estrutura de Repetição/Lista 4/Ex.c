#include<stdio.h>

int main (void)
{
    int i, soma;
    char ch;

    do
    {
        i=1000;
        while(i<10000)
        {
            soma=(i/100)+(i%100);

            if(soma*soma==i)
            {
                printf("%-5d \t", i);
            }
            i++;
        }
        printf("\n\nDeseja continuar o programa? (s/n): ");
        scanf(" %c", &ch);
    }
    while(ch=='s' || ch=='S');
}
