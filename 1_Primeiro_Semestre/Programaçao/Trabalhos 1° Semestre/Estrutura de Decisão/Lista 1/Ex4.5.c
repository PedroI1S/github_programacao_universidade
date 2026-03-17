#include <stdio.h>

int main(void)
{
    int ano, dia, mes, data, valido=1;

    printf("Insira uma data para analise: ");
    scanf("%d", &data);

    dia = data /1000000;
    ano = data %10000;
    mes = (data %1000000)/10000;

 if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1)
    {
        valido = 0;
    }
 else if (mes == 2)
    {
        int bissexto = ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0);
        if (dia > (28 + bissexto))
        {
            valido = 0;
        }
    }
 else if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30)
    {
        valido = 0;
    }

if (valido)
    {
        printf("Data valida!\n");
    }
else
    {
        printf("Data invalida!\n");
    }

return 0;
}
