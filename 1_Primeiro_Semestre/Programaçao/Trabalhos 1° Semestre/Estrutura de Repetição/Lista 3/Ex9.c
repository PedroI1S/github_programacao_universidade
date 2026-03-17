#include <stdio.h>

int main(void)
{
    int mulheres = 0, homens = 0;
    float altura=-1, alturamax = 0, alturamin = 1000, altmul = 0, althom = 0;
    char sexo, ch;

    do
    {


        do
        {
            do
            {
                printf("\nInforme altura: ");
                scanf("%f", &altura);
            }
            while (altura < 0);

            if(altura!=0)
            {


                if (altura > alturamax)
                {
                    alturamax = altura;
                }

                if (altura < alturamin)
                {
                    alturamin = altura;
                }

                do
                {
                    printf("Informe o sexo (M/F): ");
                    fflush(stdin);
                    scanf(" %c", &sexo);
                }
                while (sexo != 'M' && sexo != 'm' && sexo != 'F' && sexo != 'f');

                if (sexo == 'F' || sexo == 'f')
                {
                    mulheres++;
                    altmul += altura;
                }
                else
                {
                    homens++;
                    althom += altura;
                }
            }
        }
        while (altura != 0);

        printf("\nAltura Maxima: %.2f", alturamax);
        printf("\nAltura Minima: %.2f", alturamin);

        printf("\n\n===Mulheres===");
        printf("\nTotal: %d", mulheres);
        printf("\nMédia das alturas: %.2f", altmul / mulheres);
        printf("\nPercentual: %d %%", mulheres * 100 / (homens + mulheres));

        printf("\n\n===Homens===");
        printf("\nTotal: %d", homens);
        printf("\nMédia das alturas: %.2f", althom / homens);
        printf("\nPercentual: %d %%", homens * 100 / (homens + mulheres));

        printf("\n\nDeseja continuar o programa (S/N): ");
        fflush(stdin);
        scanf("%c", &ch);

    }
    while(ch=='S'||ch=='s');

    return 0;
}
