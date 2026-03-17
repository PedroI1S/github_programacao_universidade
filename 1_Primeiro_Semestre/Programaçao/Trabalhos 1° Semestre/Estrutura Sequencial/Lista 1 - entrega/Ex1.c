#include <stdio.h>
#include <math.h>

int main (void)
{
    int cnv, cnvmais;
    float ctesp, prcon;

    printf("Custo do espetaculo: R$");
    scanf("%f", &ctesp);
    printf("Preco do convite: R$");
    scanf("%f", &prcon);

    cnv = ceil((int)ctesp / prcon);
    cnvmais = ceil((int)cnv * 1.25);

    printf("\n%d Convites cobrem o custo do espetaculo", cnv);
    printf("\n%d Convites cobrem o custo do espetaculo com 25%% de lucro", cnvmais);

    return 0;
}
