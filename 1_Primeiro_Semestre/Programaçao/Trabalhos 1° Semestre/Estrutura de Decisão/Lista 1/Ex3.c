#include <stdio.h>

int main (void)
{
    int n1, n2, n3, meio, maior, menor;

    printf("insira 3 valores: \n");
    scanf("%d %d %d", &n1, &n2, &n3);

    if((n1>n2 && n1<n3)||(n1<n2 && n1>n3))
       {
           meio=n1;

           if(n2>n3)
           {
               maior=n2;
               menor=n3;
           }
           else
           {
               maior=n3;
               menor=n2;
           }
       }
       else if((n2>n1 && n2<n3)||(n2<n1 && n2>n3))
        {
            meio=n2;

            if(n1>n3)
            {
                maior=n1;
                menor=n3;
            }
            else
            {
                maior=n3;
                menor=n1;
            }
        }
        else
        {
            meio=n3;

            if(n2>n1)
            {
                maior=n2;
                menor=n1;
            }
            else
            {
                maior=n1;
                menor=n2;
            }
        }
    printf("Maior:%d \nMeio:%d\nMenor:%d \n", maior, meio, menor);

    return 0;
}
