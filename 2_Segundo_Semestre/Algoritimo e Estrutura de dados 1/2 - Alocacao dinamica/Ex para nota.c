#include<stdio.h>
#include<stdlib.h>

int * prog_arit(int n, int r){
        int *prog = malloc(sizeof(int)*n);

        for(int i=0; i<n; i++){
                prog[i]= (i+1)*r;
        }
    return prog;
}

int main (){
    int n, r;
    int *prog;

    scanf("%d %d", &n, &r);

    prog = prog_arit(n, r);

    for(int i=0; i<n; i++){
        printf("%d ", prog[i]);
    }
    return 0;
}
