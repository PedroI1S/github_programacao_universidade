#include<stdio.h>

int main (void)
{
    int quant, quantt;
    float val, valort;
    char ch=0;

    do
    {
        valort=0;
        quantt=0;

        do
        {
            printf("Informe a quantidade de um produto: ");
            scanf("%d", &quant);
            if(quant>0)
            {
                printf("Informe o valor unitario do(s) produto(s): R$");
                scanf("%f", &val);

                valort+=(val*quant);
                quantt+=quant;
            }
        }
        while(quant>0);

        printf("\nValor total da compra: R$%.2f", valort);
        printf("\nValor medio dos produtos: R$%.2f", valort/(float)quantt);

        printf("\n\nO valor total da compra eh %d reais e %.0f centavos.", (int)valort, (valort-(int)valort)*100);

        printf("\n\n%d reais equivale a: ", (int)valort);

        printf("\n\n%d nota(s) de 100", (int)valort/100);
        printf("\n%d nota(s) de 50", ((int)valort%100)/50);
        printf("\n%d nota(s) de 20", (((int)valort%100)%50)/20);
        printf("\n%d nota(s) de 10", ((((int)valort%100)%50)%20)/10);
        printf("\n%d nota(s) de 5", (((((int)valort%100)%50)%20)%10)/5);
        printf("\n%d nota(s) de 2", ((((((int)valort%100)%50)%20)%10)%5)/2);
        printf("\n%d moeda(s) de 1", ((((((int)valort%100)%50)%20)%10)%5)%2);

        printf("\n\nDeseja continuar o programa (s/n): ");
        fflush(stdin);
        scanf("%c", &ch);
    }
    while(ch!='N' && ch!='n');
}
