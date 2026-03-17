#include <stdio.h.>

int main (void)
{
    int dia, mes, ano, dia1, mes1, ano1;

    printf("insira a primeira data da forma dia, enter, mes, enter e ano enter:\n");
    scanf("%d %d %d", &dia, &mes, &ano);
    printf("insira a segunda data da mesma forma:\n");
    scanf("%d %d %d", &dia1, &mes1, &ano1);

    if(ano>ano1)
    {
        printf("A primeira data eh maior");
    }
    else if(ano1>ano)
    {
        printf("A segunda data eh maior");
    }
    else
    {
        if(mes>mes1)
        {
           printf("A primeira data eh maior");
        }
        else if(mes1>mes)
        {
            printf("A segunda data eh maior");
        }
        else
        {
            if(dia>dia1)
            {
                printf("A primeira data eh maior");
            }
            else if(dia1>dia)
            {
                printf("A segunda data eh maior");
            }
            else
            {
                printf("As datas sao iguais");
            }

        }
    }


    return 0;
}
