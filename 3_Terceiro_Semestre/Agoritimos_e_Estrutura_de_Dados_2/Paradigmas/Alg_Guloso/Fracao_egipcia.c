#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int * decompor_fracao(int n, int d)
{
    int *denominadores = malloc(sizeof(int)*100);
    int count = 0, uf;
    
    if(n / d > 0 ){
        printf("%d + ", n / d);
        n = n % d;
    }

    while (n != 0)
    {
        if (d % n == 0)
            uf = d / n;
        else
            uf = d / n + 1;
        denominadores[count++] = uf;

        n = n * uf - d;
        d = d * uf;
    }
    denominadores[count++] = -1;
    denominadores = realloc(denominadores, count);
    return denominadores;
}

int main()
{
    int n, d;

    scanf("%d %d", &n, &d);
    int * denominadores = decompor_fracao(n, d); 

    for (int i = 0; denominadores[i] != -1; i++)
    {
        if (i > 0)
            printf(" + ");

        printf("1/%d", denominadores[i]);
    }
    printf("\n");

    return 0;
}
