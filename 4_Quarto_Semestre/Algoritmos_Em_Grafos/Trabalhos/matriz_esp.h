#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Estruturacao da matriz esparsa;

struct tipo_linha
{
    int ID_Coluna;
    struct tipo_linha *proximo;
    struct tipo_elemento *inicio;
};//Navega na linha, definindo colunas;

struct tipo_elemento
{
    int valor;
    int linha;
    struct tipo_elemento *proximo;
};//Navega na coluna, definindo linhas;

typedef struct
{
    int qtd_linha;
    int qtd_colunas;
    struct tipo_linha *inicio;
} Tipo_Mat_Esparsa;//Definicao e primeiro elemento;

//Criandores e alocacao de memória;

Tipo_Mat_Esparsa *criar_matriz()
{
    Tipo_Mat_Esparsa *nova = (Tipo_Mat_Esparsa *)malloc(sizeof(Tipo_Mat_Esparsa));
    nova->qtd_linha = 0;
    nova->qtd_colunas = 0;
    nova->inicio = NULL;
    return nova;
}

struct tipo_elemento *criar_elemento(int valor, int linha)
{
    struct tipo_elemento *novo = (struct tipo_elemento *)malloc(sizeof(struct tipo_elemento));
    novo->valor = valor;
    novo->linha = linha;
    novo->proximo = NULL;
    return novo;
}

struct tipo_linha *criar_linha(int ID_Coluna)
{
    struct tipo_linha *nova = (struct tipo_linha *)malloc(sizeof(struct tipo_linha));
    nova->ID_Coluna = ID_Coluna;
    nova->proximo = NULL;
    nova->inicio = NULL;
    return nova;
}

//Insercao na matriz;

void inserir_elemento(Tipo_Mat_Esparsa *mat, int linha, int coluna, int valor)
{
    if (valor == 0)
    {
        struct tipo_linha *atual_coluna = mat->inicio;
        struct tipo_linha *anterior_coluna = NULL;

        // Busca a coluna especificada
        while (atual_coluna != NULL && atual_coluna->ID_Coluna < coluna)
        {
            anterior_coluna = atual_coluna;
            atual_coluna = atual_coluna->proximo;
        }

        // Se a coluna foi encontrada, prossegue para remoção do elemento
        if (atual_coluna != NULL && atual_coluna->ID_Coluna == coluna)
        {
            struct tipo_elemento *atual_elem = atual_coluna->inicio;
            struct tipo_elemento *anterior_elem = NULL;

            // Busca o elemento na linha especificada
            while (atual_elem != NULL && atual_elem->linha < linha)
            {
                anterior_elem = atual_elem;
                atual_elem = atual_elem->proximo;
            }

            // Se o elemento foi encontrado, remove-o
            if (atual_elem != NULL && atual_elem->linha == linha)
            {
                if (anterior_elem == NULL)  // Caso seja o primeiro elemento da coluna
                    atual_coluna->inicio = atual_elem->proximo;
                else
                    anterior_elem->proximo = atual_elem->proximo;

                free(atual_elem); // Libera o elemento

                // Verifica se a coluna está vazia após a remoção do elemento
                if (atual_coluna->inicio == NULL)
                {
                    // Remove a coluna se ela estiver vazia
                    if (anterior_coluna == NULL)  // Caso seja a primeira coluna
                        mat->inicio = atual_coluna->proximo;
                    else
                        anterior_coluna->proximo = atual_coluna->proximo;

                    free(atual_coluna); // Libera a coluna

                    mat->qtd_colunas = anterior_coluna->ID_Coluna;
                }

                // Ajusta a quantidade de linhas, caso a última linha tenha sido removida
                if (linha == mat->qtd_linha)
                {
                    int nova_qtd_linha = 0;
                    struct tipo_linha *temp_coluna = mat->inicio;
                    while (temp_coluna != NULL)
                    {
                        struct tipo_elemento *temp_elem = temp_coluna->inicio;
                        while (temp_elem != NULL)
                        {
                            if (temp_elem->linha > nova_qtd_linha)
                                nova_qtd_linha = temp_elem->linha;
                            temp_elem = temp_elem->proximo;
                        }
                        temp_coluna = temp_coluna->proximo;
                    }
                    mat->qtd_linha = nova_qtd_linha;
                }
            }
        }
        return;  // Retorna, pois zero não deve ser inserido
    }

    // Caso contrário, prossegue com a inserção normal do valor não-zero
    struct tipo_linha *atual_coluna = mat->inicio;
    struct tipo_linha *anterior_coluna = NULL;

    // Controle do número de colunas da matriz
    if (coluna > mat->qtd_colunas)
        mat->qtd_colunas = coluna;

    // Busca a coluna na matriz
    while (atual_coluna != NULL && atual_coluna->ID_Coluna < coluna)
    {
        anterior_coluna = atual_coluna;
        atual_coluna = atual_coluna->proximo;
    }

    // Caso não encontre a coluna, cria uma nova
    if (atual_coluna == NULL || atual_coluna->ID_Coluna != coluna)
    {
        struct tipo_linha *nova_linha = criar_linha(coluna);

        // Insere a nova coluna na lista
        if (anterior_coluna == NULL)
        {
            nova_linha->proximo = mat->inicio;
            mat->inicio = nova_linha;
        }
        else
        {
            nova_linha->proximo = anterior_coluna->proximo;
            anterior_coluna->proximo = nova_linha;
        }

        atual_coluna = nova_linha;
    }

    // Procura pelo elemento na linha especificada
    struct tipo_elemento *atual_elem = atual_coluna->inicio;
    struct tipo_elemento *anterior_elem = NULL;

    while (atual_elem != NULL && atual_elem->linha < linha)
    {
        anterior_elem = atual_elem;
        atual_elem = atual_elem->proximo;
    }

    // Atualiza o valor do elemento se ele já existir
    if (atual_elem != NULL && atual_elem->linha == linha)
    {
        atual_elem->valor = valor;
    }
    else // Insere um novo elemento
    {
        struct tipo_elemento *novo_elem = criar_elemento(valor, linha);

        if (anterior_elem == NULL)  // Caso seja o primeiro elemento da coluna
        {
            novo_elem->proximo = atual_coluna->inicio;
            atual_coluna->inicio = novo_elem;
        }
        else
        {
            novo_elem->proximo = anterior_elem->proximo;
            anterior_elem->proximo = novo_elem;
        }

        // Atualiza o número de linhas da matriz, se necessário
        if (linha > mat->qtd_linha)
            mat->qtd_linha = linha;
    }
}



//transpor matriz;

Tipo_Mat_Esparsa *transpor_matriz(Tipo_Mat_Esparsa *mat)
{
    Tipo_Mat_Esparsa *transposta = criar_matriz();

    struct tipo_linha *coluna_atual = mat->inicio;
    while (coluna_atual != NULL)
    {
        struct tipo_elemento *elem_atual = coluna_atual->inicio;
        //percorre os elementos de cada coluna;
        while (elem_atual != NULL)
        {
            //insercao dos elementos alterando suas cordenadas, troca de linhas por colunas;
            inserir_elemento(transposta, coluna_atual->ID_Coluna, elem_atual->linha, elem_atual->valor);
            elem_atual = elem_atual->proximo;
        }
        coluna_atual = coluna_atual->proximo;
    }
    //especificando as dimencoes da nova matriz;
    transposta->qtd_linha = mat->qtd_colunas;
    transposta->qtd_colunas = mat->qtd_linha;

    return transposta;
}

//somar matrizes (A+B);

Tipo_Mat_Esparsa *somar_matrizes(Tipo_Mat_Esparsa *mat1, Tipo_Mat_Esparsa *mat2)
{
    // Verifica se as dimensões de uma matriz cabem dentro da outra
    int max_linhas = (mat1->qtd_linha > mat2->qtd_linha) ? mat1->qtd_linha : mat2->qtd_linha;
    int max_colunas = (mat1->qtd_colunas > mat2->qtd_colunas) ? mat1->qtd_colunas : mat2->qtd_colunas;

    Tipo_Mat_Esparsa *resultado = criar_matriz();
    resultado->qtd_linha = max_linhas;
    resultado->qtd_colunas = max_colunas;

    // Copia os elementos de mat1 para o resultado
    struct tipo_linha *coluna1 = mat1->inicio;
    while (coluna1 != NULL)
    {
        struct tipo_elemento *elem1 = coluna1->inicio;
        while (elem1 != NULL)
        {
            inserir_elemento(resultado, elem1->linha, coluna1->ID_Coluna, elem1->valor);
            elem1 = elem1->proximo;
        }
        coluna1 = coluna1->proximo;
    }

    // Adiciona os elementos de mat2 ao resultado, somando onde já há elementos
    struct tipo_linha *coluna2 = mat2->inicio;
    while (coluna2 != NULL)
    {
        struct tipo_elemento *elem2 = coluna2->inicio;
        while (elem2 != NULL)
        {
            struct tipo_linha *coluna_res = resultado->inicio;
            while (coluna_res != NULL && coluna_res->ID_Coluna != coluna2->ID_Coluna)
                coluna_res = coluna_res->proximo;

            struct tipo_elemento *elem_res = NULL;
            if (coluna_res != NULL)
            {
                elem_res = coluna_res->inicio;
                while (elem_res != NULL && elem_res->linha != elem2->linha)
                    elem_res = elem_res->proximo;
            }

            if (elem_res != NULL)
                elem_res->valor += elem2->valor;
            else
                inserir_elemento(resultado, elem2->linha, coluna2->ID_Coluna, elem2->valor);

            elem2 = elem2->proximo;
        }
        coluna2 = coluna2->proximo;
    }

    return resultado;
}

int buscar_elemento(Tipo_Mat_Esparsa *mat, int linha, int coluna) {
    struct tipo_linha *linha_atual = mat->inicio;

    while (linha_atual != NULL && linha_atual->ID_Coluna < coluna)
        linha_atual = linha_atual->proximo;

    if (linha_atual == NULL || linha_atual->ID_Coluna != coluna)
        return 0;

    struct tipo_elemento *elemento_atual = linha_atual->inicio;
    while (elemento_atual != NULL && elemento_atual->linha < linha)
        elemento_atual = elemento_atual->proximo;

    if (elemento_atual == NULL || elemento_atual->linha != linha)
        return 0;

    return elemento_atual->valor;
}



Tipo_Mat_Esparsa *produto_matrizes(Tipo_Mat_Esparsa *mat1, Tipo_Mat_Esparsa *mat2) {
    if (mat1->qtd_colunas != mat2->qtd_linha) {
        printf("Erro: As matrizes não podem ser multiplicadas devido a dimensões incompatíveis.\n");
        return NULL;
    }

    Tipo_Mat_Esparsa *resultado = criar_matriz();
    resultado->qtd_linha = mat1->qtd_linha;
    resultado->qtd_colunas = mat2->qtd_colunas;

    int soma = 0;
    for (int i = 0; i <= resultado->qtd_linha; i++) {
        for (int j = 0; j <= resultado->qtd_colunas; j++) {
            for (int k = 0; k <= mat1->qtd_colunas; k++) {
                soma += buscar_elemento(mat1, i, k) * buscar_elemento(mat2, k, j);
            }
            if (soma != 0) {
                inserir_elemento(resultado, i, j, soma);
            }
            soma = 0;
        }
    }
    return resultado;
}


void imprimir_matriz(Tipo_Mat_Esparsa *mat)
{
    struct tipo_linha *linha_atual = mat->inicio;

    if (linha_atual == NULL)
    {
        printf("Matriz vazia!\n");
        return;
    }

    while (linha_atual != NULL)
    {
        struct tipo_elemento *elem_atual = linha_atual->inicio;
        while (elem_atual != NULL)
        {
            printf("Valor %d na posição (%d, %d)\n", elem_atual->valor, elem_atual->linha, linha_atual->ID_Coluna);
            elem_atual = elem_atual->proximo;
        }
        linha_atual = linha_atual->proximo;
    }
}

void imprimir_matriz_completa(Tipo_Mat_Esparsa *mat)
{
    printf("\n");
    if(mat == NULL)
        return;
    for (int i = 1; i <= mat->qtd_linha; i++)
    {
        for (int j = 1; j <= mat->qtd_colunas; j++)
        {
            int valor_encontrado = 0;

            struct tipo_linha *linha_atual = mat->inicio;

            while (linha_atual != NULL && linha_atual->ID_Coluna < j)
                linha_atual = linha_atual->proximo;

            if (linha_atual != NULL && linha_atual->ID_Coluna == j)
            {
                struct tipo_elemento *elem_atual = linha_atual->inicio;

                while (elem_atual != NULL && elem_atual->linha < i)
                    elem_atual = elem_atual->proximo;

                if (elem_atual != NULL && elem_atual->linha == i)
                {
                    printf("%-4d", elem_atual->valor);
                    valor_encontrado = 1;
                }
            }

            if (!valor_encontrado)
                printf("%-4d", 0);
        }
        printf("\n");
    }
}

void liberar_matriz(Tipo_Mat_Esparsa *mat)
{
    if(mat == NULL)
        return;
    struct tipo_linha *atual_linha = mat->inicio;
    while (atual_linha != NULL)
    {
        struct tipo_elemento *atual_elem = atual_linha->inicio;
        while (atual_elem != NULL)
        {
            struct tipo_elemento *elem_proximo = atual_elem->proximo;
            free(atual_elem);
            atual_elem = elem_proximo;
        }
        struct tipo_linha *linha_proxima = atual_linha->proximo;
        free(atual_linha);
        atual_linha = linha_proxima;
    }
    free(mat);
}
