#include <stdio.h>

int raiz (int n){
    int i;
    for(i=0; n>0; i++){
        n -= (1 + (2 * i));
    }
    
    if(n<0){
        i = i * -1;
    }

    return i;
}

int main (void){
    int n, res;
    
    printf("Numero a ser analisado: ");
    scanf("%d", &n);

    res = raiz(n);
    if(res>=0){
        printf("Raiz de %d = %d", n, res);
    }
    else{
        res = res * -1;
        printf("Raiz aproximada de %d = %d", n, res);
    }

    return 0;
}