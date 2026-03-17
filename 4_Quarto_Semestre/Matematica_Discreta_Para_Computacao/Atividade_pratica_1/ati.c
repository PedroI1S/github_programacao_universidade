#include "Conjuntos.h"

int main(void)
{
    int controle = 0;

    do
    {
        int totalElementos, cardinalidadeA1, cardinalidadeA2, escolhaPotencia;
        ListaE *A = criar_listaE(), *A1, *A2;

        printf("Informe o numero de elementos: ");
        scanf("%d", &totalElementos);

        printf("Insira os elementos separados por espacos: ");
        for (int i = 0; i < totalElementos; i++)
        {
            int elemento;
            scanf("%d", &elemento);
            inserir_ultimo(elemento, &A);
        }

        printf("Informe a cardinalidade dos subconjuntos A1 e A2: ");
        do
        {
            scanf("%d %d", &cardinalidadeA1, &cardinalidadeA2);
            if (cardinalidadeA1 > totalElementos || cardinalidadeA2 > totalElementos)
                printf("Os valores devem ser menores que o conjunto A.\nInsira outros valores:");
        } while (cardinalidadeA1 > totalElementos || cardinalidadeA2 > totalElementos);

        A1 = obter_conjunto_aleatorio(A, cardinalidadeA1);
        A2 = obter_conjunto_aleatorio(A, cardinalidadeA2);

        printf("Informe o subconjunto para calcular o conjunto potencia (1 para A1, 2 para A2): ");
        do
        {
            scanf("%d", &escolhaPotencia);
        } while (escolhaPotencia != 1 && escolhaPotencia != 2);

        imprimir_resultados(A, A1, A2, escolhaPotencia);

        liberar_LE(A);
        liberar_LE(A1);
        liberar_LE(A2);

        printf("\nDigite (1) para informar outro conjunto ou (2) para sair: ");
        do
        {
            scanf("%d", &controle);
        } while (controle != 1 && controle != 2);
        printf("\n\n");
    } while (controle != 2);

    return 0;
}
