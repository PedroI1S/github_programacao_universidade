#include <stdio.h>

int main (void)
{
    int num1, num2;

    printf("insira o primeiro digito:");
    scanf("%d", &num1);
    printf("insira o segundo digito: ");
    scanf("%d", &num2);

    if(num1 > num2)
    {
        printf ("%d eh maior que &d", num1, num2);
    }
    else
    {
        if(num1 < num2)
        {
            printf("%d eh menor que %d", num1, num2);
        }
        else
        {
            printf("%d eh igual a %d", num1, num2);
        }
    }


    return 0;
}
