#include "matriz_esp.h"
#include <stdio.h>
#include <locale.h>

void menu() {
    printf("\n--- MENU INTERATIVO ---\n");
    printf("1. Selecionar matriz ativa (Exemplo 1, Exemplo 2, Personalizada ou Transposta)\n");
    printf("2. Inserir elemento na matriz personalizada\n");
    printf("3. Exibir matriz ativa\n");
    printf("4. Exibir dimensões da matriz ativa\n");
    printf("5. Transpor matriz ativa e salvar\n");
    printf("6. Somar matriz ativa com outra matriz\n");
    printf("7. Multiplicar matriz ativa com outra matriz\n");
    printf("8. Sair\n");
    printf("Escolha uma opcao: ");
}

void exibir_dimensoes(Tipo_Mat_Esparsa *mat) {
    if (mat->qtd_linha == 0 || mat->qtd_colunas == 0) {
        printf("Matriz vazia!\n");
    } else {
        printf("Dimensoes da Matriz Ativa: %d linhas x %d colunas\n", mat->qtd_linha, mat->qtd_colunas);
    }
}

int main() {

    setlocale(LC_ALL, "Portuguese");

    Tipo_Mat_Esparsa *mat1 = criar_matriz();
    Tipo_Mat_Esparsa *mat2 = criar_matriz();
    Tipo_Mat_Esparsa *mat_usuario = criar_matriz();
    Tipo_Mat_Esparsa *matriz_transposta = NULL;
    Tipo_Mat_Esparsa *matriz_ativa = mat1;  // Matriz ativa começa como mat1
    int opcao, linha, coluna, valor;

    // Preenchendo matriz de exemplo 1
    inserir_elemento(mat1, 1, 1, 2);
    inserir_elemento(mat1, 1, 2, 5);
    inserir_elemento(mat1, 2, 6, 3);
    inserir_elemento(mat1, 2, 5, 9);
    inserir_elemento(mat1, 4, 3, 12);
    inserir_elemento(mat1, 5, 5, 3);

    // Preenchendo matriz de exemplo 2
    inserir_elemento(mat2, 3, 3, 1);

    while (1) {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Escolha a matriz ativa:\n");
                printf("1. Matriz Exemplo 1\n");
                printf("2. Matriz Exemplo 2\n");
                printf("3. Matriz Personalizada\n");
                printf("4. Matriz Transposta\n");
                printf("Escolha: ");
                int escolha;
                scanf("%d", &escolha);
                if (escolha == 1) matriz_ativa = mat1;
                else if (escolha == 2) matriz_ativa = mat2;
                else if (escolha == 3) matriz_ativa = mat_usuario;
                else if (escolha == 4 && matriz_transposta != NULL) matriz_ativa = matriz_transposta;
                else printf("Escolha invalida ou matriz transposta não disponível!\n");
                break;

            case 2:
                printf("Insira o elemento na matriz personalizada:\n");
                printf("Linha: ");
                scanf("%d", &linha);
                printf("Coluna: ");
                scanf("%d", &coluna);
                printf("Valor: ");
                scanf("%d", &valor);
                inserir_elemento(mat_usuario, linha, coluna, valor);
                if (linha > mat_usuario->qtd_linha) mat_usuario->qtd_linha = linha;
                if (coluna > mat_usuario->qtd_colunas) mat_usuario->qtd_colunas = coluna;
                break;

            case 3:
                printf("\nMatriz Ativa:\n");
                imprimir_matriz_completa(matriz_ativa);
                printf("\n");
                imprimir_matriz(matriz_ativa);
                break;

            case 4:
                exibir_dimensoes(matriz_ativa);
                break;

            case 5:
                if (matriz_transposta != NULL) {
                    liberar_matriz(matriz_transposta);  // Libera a transposta anterior, se existir
                }
                matriz_transposta = transpor_matriz(matriz_ativa);
                printf("\nMatriz Transposta salva.\n");
                break;

            case 6: {
                printf("Escolha a matriz para somar com a matriz ativa:\n");
                printf("1. Matriz Exemplo 1\n");
                printf("2. Matriz Exemplo 2\n");
                printf("3. Matriz Personalizada\n");
                printf("Escolha: ");
                int soma_escolha;
                scanf("%d", &soma_escolha);

                Tipo_Mat_Esparsa *outra_matriz = (soma_escolha == 1) ? mat1 :
                                                  (soma_escolha == 2) ? mat2 : mat_usuario;

                Tipo_Mat_Esparsa *soma = somar_matrizes(matriz_ativa, outra_matriz);
                if (soma != NULL) {
                    printf("\nResultado da Soma (Matriz Ativa + Matriz Escolhida):\n");
                    imprimir_matriz_completa(soma);
                    liberar_matriz(soma);
                } else {
                    printf("Erro: Dimensões incompatíveis para soma!\n");
                }
                break;
            }

            case 7: {
                printf("Escolha a matriz para multiplicar com a matriz ativa:\n");
                printf("1. Matriz Exemplo 1\n");
                printf("2. Matriz Exemplo 2\n");
                printf("3. Matriz Personalizada\n");
                printf("Escolha: ");
                int mult_escolha;
                scanf("%d", &mult_escolha);

                Tipo_Mat_Esparsa *outra_matriz = (mult_escolha == 1) ? mat1 :
                                                  (mult_escolha == 2) ? mat2 : mat_usuario;

                Tipo_Mat_Esparsa *produto = produto_matrizes(matriz_ativa, outra_matriz);
                if (produto != NULL) {
                    printf("\nResultado da Multiplicação (Matriz Ativa x Matriz Escolhida):\n");
                    imprimir_matriz_completa(produto);
                    liberar_matriz(produto);
                } else {
                    printf("Erro: Dimensões incompatíveis para multiplicação!\n");
                }
                break;
            }

            case 8:
                printf("Saindo...\n");
                liberar_matriz(mat1);
                liberar_matriz(mat2);
                liberar_matriz(mat_usuario);
                if (matriz_transposta != NULL) liberar_matriz(matriz_transposta);
                return 0;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    }
}
