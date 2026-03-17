#include<stdio.h>
#include<math.h>

int main (void)
{
    int i=1, j=0, u=1;

    printf("=== DIVISIVEIS POR 3 ===\n");
    while(i<=100)
    {
        if(i%3==0)
        {
            printf("%-8d", i);
            j++;
            if(j%6==0)
            {
                printf("\n");
            }
        }
        i++;
    }

    j=0;
    i=0;
    printf("\n\n=== QUADRADO DAS DIVISIVEIS POR 3 ===\n");

    while(i<=100)
    {
        if(i%3==0)
        {
            printf("%-8d", i*i);
            j++;
            if(j%6==0)
            {
                printf("\n");
            }
        }
        i++;
    }

    j=0;
    i=0;
    printf("\n\n=== DIVISIVEIS POR 5 OU 7 ===\n");

    while(i<=100)
    {
        if((i%5==0)||(i%7==0))
        {
            printf("%-8d", i);
            j++;
            if(j%6==0)
            {
                printf("\n");
            }
        }
        i++;
    }

    j=0;
    i=0;
    printf("\n\n=== RAIZ QUADRADA DOS DIVISIVEIS POR 5 OU 7 ====\n");

    while(i<=100)
    {
        if((i%5==0)||(i%7==0))
        {
            printf("%-8d", sqrt(i));
            j++;
            if(j%6==0)
            {
                printf("\n");
            }
        }
        i++;

    }
    return 0;
}
