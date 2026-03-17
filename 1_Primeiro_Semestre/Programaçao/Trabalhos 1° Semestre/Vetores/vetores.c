#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Vetores.h"

/* Exercicio1
int main (void)
{
    int lim, tamanho=0, menor=100, lmenor, pares=0, tpares=0;

    do
    {
        printf("Informe o tamanho do vetor: ");
        scanf("%d", &tamanho);
        if(tamanho<0)
        {
            printf("\nInsira um valor positivo!\n");
        }
    }while(tamanho<=0);
    do
    {
        printf("Informe o limite do vetor: ");
        scanf("%d", &lim);
        if(lim<0)
        {
            printf("\nInsira um valor positivo!\n");
        }
    }while(lim<0);

    int vet[tamanho];

    iGEV(vet, tamanho, lim);

    printf("===Vetor Gerado===\n");
    iMEV(vet, tamanho);

    for(int i=0; i<tamanho; i++)
    {
        if (vet[i]<menor)
        {
            menor = vet[i];
            lmenor = i;
        }
        if(vet[i]%2==0)
        {
            pares+=vet[i];
            tpares++;
        }
    }
    printf("\n\nO menor valor eh %d e esta no indice %d", menor, lmenor);
    printf("\nMedia dos pares: %.2f\n\n", pares/(float)tpares);

}*/
/* Exercicio 2
int main (void)
{
    int vetor[15], vetorpi[15], pares=0, impares=14;

    iGEV(vetor, 15, 25);
    printf("=== Vetor ===\n");
    iMEV(vetor, 15);

    for(int i=0; i<15; i++)
    {
        if(vetor[i]%2==0)
        {
            vetorpi[pares]=vetor[i];
            pares++;
        }
        else
        {
            vetorpi[impares]=vetor[i];
            impares--;
        }
    }
    for(int i=0; i<15; i++)
    {
        if(i==0)
        {
            printf("\n\n=== Vetor de pares ===\n");
        }
        if(i==pares)
        {
            printf("\n\n===Vetor de impares ===\n");
        }
        printf("%-5d", vetorpi[i]);
    }
    printf("\n\n");
}
*/
/*Exercicio 3
int main (void)
{
    int VetorA[10], VetorB[10], i;

    iGEV(VetorA, 10, 10);

    for(i=0; i<10; i++)
    {
        VetorB[i]=VetorA[9-i];
    }

    printf("===Vetor A===\n");
    iMEV(VetorA, 10);
    printf("\n\n===Vetor B===\n");
    iMEV(VetorB, 10);
}
*/
/*Exercicio 4*/
int main (void)
{
    int na, nb, nc, menor, i;

    do
    {
        printf("Informe o tamanho do vetor A: ");
        scanf("%d", &na);
        if(na<0)
        {
            printf("\nInsira um valor positivo!\n");
        }
    }while(na<=0);
    do
    {
        printf("Informe o tamanho do vetor B: ");
        scanf("%d", &nb);
        if(nb<0)
        {
            printf("\nInsira um valor positivo!\n");
        }
    }while(nb<=0);

    if(na>nb)
    {
        nc=na;
        menor=nb;
    }
    else
    {
        nc=nb;
        menor=na;
    }
    i=nc;

    int vetorA[na], vetorB[nb], vetorC[nc];

    iGEV(vetorA, na, 20);
    iGEV(vetorB, nb, 15);

    while(i>(nc-menor))
    {
        if(na>nb)
        {
            vetorC[i]=1;
        }
        else
        {
            vetorC[i]=-1;
        }
        i--;
    }

    while(i>0)
    {
        if(vetorA[i]>vetorB[i])
        {
            vetorC[i]= 1;
        }
        else if(vetorA[i]<vetorB[i])
        {
            vetorC[i]=-1;
        }
        else
        {
            vetorC[i]=0;
        }
        i--;

    }
    printf("\n\n===Vetor A===\n");
    iMEV(vetorA, na);
    printf("\n\n===Vetor B===\n");
    iMEV(vetorB, nb);
    printf("\n\n===Vetor C===\n");
    iMEV(vetorC, nc);
}
