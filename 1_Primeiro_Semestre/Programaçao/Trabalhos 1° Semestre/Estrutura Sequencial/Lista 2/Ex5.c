#include <stdio.h>

int main (void)
{
    int num1, num2, num3;

    printf("insira o primeiro digito: ");
    scanf("%d", &num1);
    printf("insira o segundo digito: ");
    scanf("%d", &num2);
    printf("insira o terceiro digito: ");
    scanf("%d", &num3);

    if ((num1>=num2 && num1<=num3)||(num1<=num2 && num1>=num3))
    {
        printf("Numero do meio eh: %d", num1);
    }
    else
    {
        if ((num2>=num1 && num2<=num3)||(num2<=num1 && num2>=num3))
        {
            printf("Numero do meio eh: %d", num2);
        }
        else
        {
            printf("Numero do meio eh: %d", num3);
        }
    }
    return 0;
}
