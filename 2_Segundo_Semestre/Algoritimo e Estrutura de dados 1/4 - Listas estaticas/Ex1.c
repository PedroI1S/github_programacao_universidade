#include<stdio.h>
#include<stdlib.h>
#include"list.h"

int main(void){
    int key;

    list *l = create();

    do{
        scanf("%d", &key);
        if(key != -1){
            insert(l, key);
        }
    }while(key != -1);

    invert(l);
    imprint(l);
    free(l);

    return 0;
}
