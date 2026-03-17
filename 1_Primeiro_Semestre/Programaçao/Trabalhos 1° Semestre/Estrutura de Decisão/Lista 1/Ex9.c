#include <stdio.h>

int main (void)
{
    int num, sal;

    printf("indique o salario atual: R$");
    scanf("%d", &sal);
    printf("Digite:\n1 Para Escrituario\n2 Para Secretario\n3 Para Caixa\n4 Para Gerente\n5 Para Diretor\n");
    scanf("%d",&num);

    if (num<=0 || num>=6)
    {
        printf("escolha inválida");
    }
    else
    {
        switch (num)
        {
            case 1:
                printf("Cargo: Escrituario \nValor do aumento salarial: R$%d \nNovo salário: R$%d", (int)(sal*0.50), (int)(sal*1.50));
                break;

            case 2:
                printf("Cargo: Secretario \nValor do aumento salarial: R$%d \nNovo salário: R$%d", (int)(sal*0.35), (int)(sal*1.35));
                break;

            case 3:
                printf("Cargo: Caixa \nValor do aumento salarial: R$%d \nNovo salário: R$%d", (int)(sal*0.20), (int)(sal*1.20));
                break;

            case 4:
                printf("Cargo: Gerente \nValor do aumento salarial: R$%d \nNovo salário: R$%d", (int)(sal*0.10), (int)(sal*1.10));
                break;

            case 5:
                printf("Cargo: Diretor \nValor do aumento salarial: R$%d \nNovo salário: R$%d", (int)(sal*0.00), (int)(sal*1.00));
        }
    }
    return 0;
}
