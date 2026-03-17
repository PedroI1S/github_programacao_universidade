#include <stdio.h>

int main (void)
{
    float prm, g1, g2, g3;

    printf("Valor do premio: R$");
    scanf("%f", &prm);

    g1 = prm * 0.46;
    g2 = prm * 0.32;
    g3 = prm - (g1 + g2);

    printf("\nO primeiro ganhador recebera: R$%.2f", g1);
    printf("\nO segundo ganhador recebera: R$%.2f", g2);
    printf("\nO terceiro ganhador recebera: R$%.2f", g3);

    return 0;
}
