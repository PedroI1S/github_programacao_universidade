/*Elaborar um programa para automatizar o caixa de uma loja. Ler a quantidade e o valor unitário de cada produto. Calcular o valor
total da compra. Informar esse valor para o usuário e o usuário informa o valor para pagamento. O programa calcula o troco e
informa-o ao usuário em notas de 10, 5, 1 e os centavos. Prosseguir a leitura enquanto a quantidade for maior que zero. Se
informado zero ou valor negativo para a quantidade, não ler o valor unitário.*/
#include<stdio.h>

int main (void)
{
    int num=1, t10, t5, t1, cent;
    float val, total=0, pagamento, troco;

    while(num!= 0)
    {
        printf("Informe a quantidade de produtos: ");
        scanf("%d", &num);

        if(num>0)
        {
            printf("Informe o valor do produto: R$");
            scanf("%f", &val);

            total=total+((float)num*val);
        }
    }
    printf("\n\nValor total da compra: R$%.2f", total);
    printf("\nInforme o pagamento: R$");
    scanf("%f", &pagamento);
    troco= pagamento-total;
    printf("Troco: R$%.2f", troco);

    if (troco >= 0)
    {
        t10 = (int)troco / 10;
        printf("\n\n%d Notas de 10", t10);
        t5 = ((int)troco % 10) / 5;
        printf("\n%d Notas de 5", t5);
        t1 = ((int)troco % 5);
        printf("\n%d Notas de 1", t1);
        cent = ((int)(troco * 100)) % 100;
        printf("\n%d Centavos\n", cent);
    }
    else
    {
        printf("\n\nPagamento insuficiente. Faltam R$%.2f\n", -troco);
    }

}
