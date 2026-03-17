#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Função para verificar se a matriz é reflexiva
bool ehReflexiva(int tamanho, int matriz[tamanho][tamanho])
{
    for (int i = 0; i < tamanho; i++)
    {
        if (matriz[i][i] != 1)
        {
            return false;
        }
    }
    return true;
}

// Função para verificar se a matriz é simétrica
bool ehSimetrica(int tamanho, int matriz[tamanho][tamanho])
{
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            if (matriz[i][j] != matriz[j][i])
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    int tamanho = 1;
    printf("Informe o tamanho da matriz (3, 4 ou 5): ");
    do
    {
        scanf("%d", &tamanho);
        if (tamanho < 3 || tamanho > 5)
        {
            printf("Tamanho inválido! Apenas 3, 4 ou 5 são permitidos.\n");
        }
    } while (tamanho < 3 || tamanho > 5);

    int matriz[tamanho][tamanho];
    char separador;

    printf("Insira os valores da matriz linha por linha, separados por espaço:\n");
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            if (j < tamanho - 1)
                scanf("%d%c", &matriz[i][j], &separador);
            else
                scanf("%d", &matriz[i][j]);
            if (matriz[i][j] > 1)
                    matriz[i][j] = 1;
        }
    }

    bool reflexiva = ehReflexiva(tamanho, matriz);
    bool simetrica = ehSimetrica(tamanho, matriz);

    if (reflexiva && simetrica)
        printf("A relação representada pela matriz é reflexiva e simétrica.\n");
    else if (reflexiva)
        printf("A relação representada pela matriz é apenas reflexiva.\n");
    else if (simetrica)
        printf("A relação representada pela matriz é apenas simétrica.\n");
    else
        printf("A relação representada pela matriz não é reflexiva nem simétrica.\n");

    printf("\nDigite (1) para informar outra matriz ou (2) para sair: ");
    int opcao = 0;
    scanf("%d", &opcao);

    if (opcao == 1)
        main();
    else
        printf("Encerrando o programa.\n");

    return 0;
}