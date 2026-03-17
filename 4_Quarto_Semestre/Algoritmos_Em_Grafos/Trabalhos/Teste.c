#include "matriz_esp.h"
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Portuguese");
    Tipo_Mat_Esparsa *mat1 = criar_matriz();
    Tipo_Mat_Esparsa *mat2 = criar_matriz();

    // Preenche `mat1`
    inserir_elemento(mat1, 1, 1, 1);
    inserir_elemento(mat1, 1, 2, 2);
    inserir_elemento(mat1, 2, 1, 3);
    inserir_elemento(mat1, 3, 3, 4);

    // Preenche `mat2`
    inserir_elemento(mat2, 1, 1, 0);
    inserir_elemento(mat2, 1, 2, 6);
    inserir_elemento(mat2, 3, 1, 7);
    inserir_elemento(mat2, 3, 3, 8);

    printf("Matriz 1:\n");
    imprimir_matriz_completa(mat1);
    imprimir_matriz(mat1);

    printf("\nMatriz 2:\n");
    imprimir_matriz_completa(mat2);
    imprimir_matriz(mat2);
    printf("\n");

    // Realiza a multiplicação
    Tipo_Mat_Esparsa *resultado = produto_matrizes(mat1, mat2);

    printf("\nResultado da Multiplicação:\n");
    imprimir_matriz_completa(resultado);

    liberar_matriz(mat1);
    liberar_matriz(mat2);
    liberar_matriz(resultado);

    return 0;
}
