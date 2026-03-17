#include <stdio.h>

int num_alg(int num){
    int quant = 1;

    while(num>9){
        quant++;
        num /= 10;
    }

    return quant;
}

int num_algp(int num){
    int quant = 0;
    int test = 0;

    while(num>9){

       if((num%10)%2==0){
        quant++;
       }

        num /= 10;
    }

    if(num%2==0)
     quant++;

    return quant;
}

int main(void){
    int num;

    printf("Numero informado pelo usuario: ");
    scanf("%d", &num);

    printf("\nResultado informado pelo programa: %d algarismo(s)", num_alg(num));
    printf("\nQuantidade de algarismo(s) multiplo(s) de 2: %d", num_algp(num));
    printf("\nQuantidade de algarismo(s) multiplo(s) de 3: %d", num_alg(num) - num_algp(num));

    return 0;
}