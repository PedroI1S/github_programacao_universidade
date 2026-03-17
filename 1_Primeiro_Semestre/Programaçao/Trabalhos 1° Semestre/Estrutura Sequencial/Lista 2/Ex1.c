#include <stdio.h>

int main (void)
{
    int idade;

    printf("insira a idade do jogador: ");
    scanf("%d", &idade);

    if (0 < idade && idade <= 4)
    {
        printf("%d anos Ainda eh muito cedo para jogar", idade);
    }
    else
    {
        if (5 <= idade && idade <=10)
        {
            printf ("%d anos Sub-10", idade);
        }
        else
        {
            if (11 <= idade && idade <= 17)
            {
                printf("%d anos Sub 17", idade);
            }
            else
            {
                if (18 <= idade && idade <=20)
                {
                    printf("%d anos Sub 20", idade);
                }
                else
                {
                    if (21 <= idade && idade <= 35)
                    {
                       printf("%d anos Profissional", idade);
                    }
                    else
                    {
                        if (36 <= idade && idade <= 55)
                        {
                            printf("%d anos Master", idade);
                        }
                        else
                        {
                            if(55 <= idade && idade <= 130)
                            {
                                printf("%d anos Melhor aposentar as chuteiras", idade);
                            }
                            else
                            {
                                printf("Valor invalido");
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}
