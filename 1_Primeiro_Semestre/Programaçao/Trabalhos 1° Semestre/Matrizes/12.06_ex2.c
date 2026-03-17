#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"Matrizes.h"

int main (void)
{
    int matriz[5][5], somalinha[5], somacoluna[5], i, j;

    GM2(5, 5, matriz, 5);

    for(i=0; i<5; i++)
    {
        somacoluna[i]=0;
        somalinha[i]=0;
    }

    i=0;
    j=0;

    while(j<5)
    {
        somalinha[j]+=matriz[i][j];
        somacoluna[i]+=matriz[i][j];

        if(i==4)
        {
            i=-1;
            j++;
        }
        i++;
    }

     printf("===MATRIZ=== \n");
     MM2(5, 5, matriz);
     printf("\n===Soma das Linhas=== \n");
     for(i=0; i<5; i++)
    {
        printf("%-4d", somalinha[i]);
    }
     printf("\n\n===Soma das colunas=== \n");
     for(i=0; i<5; i++)
    {
        printf("%-4d", somacoluna[i]);
    }
    printf("\n\n");
}

