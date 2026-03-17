#include <stdio.h>

int main (void)
{
    float peso, altura, idade;
    char sexo;

    printf("Informe seu peso, altura(em cm), idade e sexo(M para masculino e F para feminino); respectivamente: \n");
    scanf("%f %f %f %c", &peso, &altura, &idade, &sexo);

    if (altura<0 || idade<0 || peso<0 || !(sexo=='M' || sexo=='F' || sexo=='m' || sexo=='f'))
    {
        printf("valor invalido inserido");
    }
    else
    {
            if (sexo == 'M' || sexo == 'm')
        {
            printf("Sexo: Masculino\n");
            printf("GEB: %.2f kcal", 66.47+(13.75*peso)+(5*altura)-(6.75*idade));
        }
        else
        {
            printf("Sexo: Feminino\n");
            printf("GEB: %.2f kcal", 655.1+(9.56*peso)+(1.85*altura)-(4.67*idade));
        }
    }
    return 0;
}

