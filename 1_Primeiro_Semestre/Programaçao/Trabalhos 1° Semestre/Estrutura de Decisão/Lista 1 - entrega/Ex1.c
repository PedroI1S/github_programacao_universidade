#include <stdio.h>
#include <locale.h>

int main (void)
{
    setlocale(LC_ALL, "Portuguese");
    float min, brut;

    printf("Informe o salário minimo: R$");
    scanf("%f", &min);
    printf("Informe o salário bruto: R$");
    scanf("%f", &brut);

    if(brut<=(3*min))
    {
        printf("\n Desconto do INSS: R$%.2f", brut*0.08);
        printf("\n Salário líquido: R$%.2f", brut-(brut*0.08));
    }
    else
    {
        printf("\n Desconto do INSS: R$%.2f", brut*0.1);
        printf("\n Salário líquido: R$%.2f", brut-(brut*0.1));
    }
    return 0;
}
