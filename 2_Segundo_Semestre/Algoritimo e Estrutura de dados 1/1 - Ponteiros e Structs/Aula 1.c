#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct{
    int ra;
    char nome[50];
    float p1, p2, p3;
}boletim;

int main() {
    int numero=0, i, indice_p1 = 0, indice_m = 0, indice_M = 0;
    float maior_p1 = 0, menor_media = 100, maior_media = 0;

    scanf("%d", &numero);

    boletim aluno[numero];

    for(i=0; i<numero; i++){

        scanf("%d", &aluno[i].ra);
        scanf("%s", &aluno[i].nome);
        scanf("%f %f %f", &aluno[i].p1, &aluno[i].p2, &aluno[i].p3);

        if(((aluno[i].p1+aluno[i].p2+aluno[i].p3)/3) > maior_media)
        {
            maior_media = (aluno[i].p1+aluno[i].p2+aluno[i].p3)/3;
            indice_M = i;
        }
        if(((aluno[i].p1+aluno[i].p2+aluno[i].p3)/3) < menor_media)
        {
            menor_media = (aluno[i].p1+aluno[i].p2+aluno[i].p3)/3;
            indice_m = i;
        }
        if(aluno[i].p1 > maior_p1)
        {
            maior_p1 = aluno[i].p1;
            indice_p1 = i;
        }
    }

    for(i=0; i<numero; i++){
        if((aluno[i].p1+aluno[i].p2+aluno[i].p3)/3 >= 6){
            printf("Aprovado!\n");
        }else{
            printf("Reprovado!\n");
        }
    }

    printf("O aluno com maior media e: %d %s %.1f\n", aluno[indice_M].ra, aluno[indice_M].nome, maior_media);
    printf("O aluno com menor media e: %d %s %.1f\n", aluno[indice_m].ra, aluno[indice_m].nome, menor_media);
    printf("O aluno com maior P1 e: %d %s %.1f\n", aluno[indice_p1].ra, aluno[indice_p1].nome, maior_p1);


    return 0;
}

