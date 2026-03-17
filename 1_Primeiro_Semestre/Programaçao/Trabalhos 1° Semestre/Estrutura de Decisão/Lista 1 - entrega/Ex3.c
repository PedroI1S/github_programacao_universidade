#include <stdio.h>
#include <locale.h>

int main (void)
{
    setlocale(LC_ALL, "Portuguese");
    char a, b;
    float temp;

    printf("O paciente se sente bem? (""s"" para sim ""n"" para não)\nR: ");
    fflush(stdin);
    scanf("%c", &a);

    if(a=='s' || a=='S')
    {
        printf("\no paciente está saudável\n");
    }
    else if(a=='n' || a=='N')
    {
        printf("\nO paciente sente dor? \nR: ");
        fflush(stdin);
        scanf("%c", &b);

        if(b=='s' || b=='S')
        {
            printf("\nO paciente está doente\n");
        }
        else if(b=='n' || b=='N')
        {
            printf("\n Qual a temperatura do paciente? \nR: ");
            scanf("%f", &temp);

            if(temp<=37)
            {
                printf("\nO paciente está saudável\n");
            }
            else
            {
                printf("\nO paciente está doente\n");
            }
        }
        else
        {
            printf("\nCaractere inválido!\n");
        }
    }
    else
    {
        printf("\nCaractere inválido!\n");
    }

    return 0;
}
