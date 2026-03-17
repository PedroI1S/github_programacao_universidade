#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"Matrizes.h"

int main (void)
{
    int matriz[10][10], i=0, j=0;

    while(j<10)
    {
        matriz[i][j] = 1;

        if(i==(10-1))
        {
            j++;
            i=-1;
        }
        i++;
    }

    printf("==== MATRIZ ORIGINAL ====\n");
    MM2(10, 10, matriz);

    i=0;
    j=0;

    while(j<10)
    {
        if(i==j)
        {
            matriz[i][j]=0;
        }
        if(i==9-j)
        {
            matriz[i][j]=0;
        }

        if(i==(10-1))
        {
            j++;
            i=-1;
        }
        i++;
    }

    printf("\n\n==== MATRIZ ATUAL ====\n");
    MM2(10, 10, matriz);
}
