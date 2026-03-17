#include<stdio.h>
#include<locale.h>

int main (void)
{
    setlocale(LC_ALL, "Portuguese");
    float arvoreA=1.50, arvoreB=1.10, i=0;

    while(arvoreA>=arvoreB)
    {
        i++;
        arvoreA+=0.02;
        arvoreB+=0.03;
    }
    printf("Altura final da árvore A: %.2f\nAltura final da árvore B: %.2f\n\nSerão necessários %.0f anos para para que a árvore B seja maior que a árvore A.", arvoreA, arvoreB, i);
}
