#include <stdio.h>
#include <stdlib.h>

void sort (char str[50],char c, int *qtd, float *rep){


    for(int i=0; str[i]!='\0'; i++){
        *qtd+=1;
        if(str[i]==c){
            *rep+=1;
        }
    }
}

int main (){
    char str[50], c;
    int qtd=0;
    float rep=0;

    scanf("%s", &str);
    scanf(" %c", &c);

    sort(str, c, &qtd, &rep);

    printf("%d\n%.2f\n", (int)rep, (rep/(float)qtd ));
}
