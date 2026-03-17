#include <stdio.h>

int main (void)
{
    int seg;
    float min, h, dia;

    printf("Informe o tempo em segundos: ");
    scanf("%d", &seg);

    min = (float)seg / 60;
    h = min / 60;
    dia = h / 24;

    printf("\nO tempo em minutos eh: %.2f", min);
    printf("\nO tempo em horas eh: %.1f", h);
    printf("\nO tempo em dias eh: %.0f", dia);

    return 0;
}
