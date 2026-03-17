#include<stdio.h>
#include<stdlib.h>
/*
void subvetor(int *v, int *vet, int ini, int fim){

    for(int i=0;i<(fim-ini);i++){
        vet[i] = v[ini+i];
    }
}


int main (){

    int tam, ini, fim;

    scanf("%d", &tam);

    int v[tam];

    for(int i=0; i<tam; i++){
        scanf("%d", &v[i]);
    }

    scanf("%d %d", &ini, &fim);

    int vet[fim-ini];

    subvetor(v, vet, ini, fim);

    for(int i=0;i<(fim-ini);i++){
      printf("%d ", vet[i]);
    }
}
*/
/*
void soma(int *v1, int *v2, int n1, int n2){
    if(n1<n2){
        for(int i=0; i<n1; i++){
            v2[i]+=v1[i];
        }
        for(int i=0; i<n2; i++){
            printf("%d ", v2[i]);
        }
    }
    else{
        for(int i=0; i<n2; i++){
            v1[i]+=v2[i];
        }
        for(int i=0; i<n1; i++){
            printf("%d ", v1[i]);
        }
    }

}

int main (){
    int n2, n1, i;

    scanf("%d", &n1);
    int v1[n1];

    for(i=0; i<n1; i++){
        scanf("%d", v1[i]);
    }

    scanf("%d", &n2);
    int v2[n2];

    for(i=0; i<n2; i++){
        scanf("%d", v2[i]);
    }

    soma(v1, v2, n1, n2);
}
*/

void decode(char* alfa, int* vet, int i){
    int aux;

    for(int j=0; j<i; j++){
        aux = vet[j];
        vet[j] = (int)alfa[(aux-1)];
    }
}


int main() {
    char *alfa;
    int *vet;
    int i, aux=0;

    //String
    alfa = malloc(sizeof(char)*500);
    scanf(" %s", alfa);

    for(i=0; alfa[i]!='\0'; i++); //Contagem da string

    alfa = realloc(alfa, sizeof(char)*(i+1)); //Redimensionamento da string

    //Vetor
    vet = (int*) calloc(sizeof(int), 500);

    for(i=0; vet[i]!=-1; i++){
        scanf(" %d", &vet[i]);
        //vet[i]= aux;
    }

    i--; //i=tamanho do vetor;

    vet = realloc(vet, sizeof(int)*i); //Redimensionamento do vetor

    decode(alfa, vet, i);

    //Impressão
    for(int j=0; j<i; j++){
        printf("%c", (char)vet[j]);
    }

    free(vet);
    free(alfa);

    return 0;
}



