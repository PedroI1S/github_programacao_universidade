#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h> // Para configurar o locale

// Estrutura para armazenar uma aresta na lista de adjacências
typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta* prox;
} Aresta;

// Estrutura para armazenar um vértice e sua lista de adjacências
typedef struct Vertice {
    int id;
    Aresta* listaAdj;
    struct Vertice* prox;
} Vertice;

// Estrutura para a fila usada na BFS
typedef struct Fila {
    int vertice;
    struct Fila* prox;
} Fila;

// Funções auxiliares
Vertice* encontrarVertice(Vertice* grafo, int id) {
    while (grafo != NULL) {
        if (grafo->id == id) {
            return grafo;
        }
        grafo = grafo->prox;
    }
    return NULL;
}

bool existeAresta(Vertice* grafo, int origem, int destino) {
    Vertice* vertOrigem = encontrarVertice(grafo, origem);
    if (!vertOrigem) return false;

    Aresta* adj = vertOrigem->listaAdj;
    while (adj != NULL) {
        if (adj->destino == destino) return true;
        adj = adj->prox;
    }
    return false;
}

void liberarListaAdj(Aresta* listaAdj) {
    while (listaAdj != NULL) {
        Aresta* temp = listaAdj;
        listaAdj = listaAdj->prox;
        free(temp);
    }
}

// Funções principais
void inserirVertice(Vertice** grafo, int id) {
    if (encontrarVertice(*grafo, id)) {
        printf("Vértice %d já existe!\n", id);
        return;
    }

    Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice));
    novoVertice->id = id;
    novoVertice->listaAdj = NULL;
    novoVertice->prox = *grafo;
    *grafo = novoVertice;

    printf("Vértice %d inserido.\n", id);
}

void inserirAresta(Vertice* grafo, int origem, int destino, int peso) {
    Vertice* vertOrigem = encontrarVertice(grafo, origem);
    Vertice* vertDestino = encontrarVertice(grafo, destino);

    if (!vertOrigem || !vertDestino) {
        printf("Um ou ambos os vértices não existem.\n");
        return;
    }

    if (existeAresta(grafo, origem, destino)) {
        printf("Já existe uma aresta entre %d e %d.\n", origem, destino);
        return;
    }

    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->prox = vertOrigem->listaAdj;
    vertOrigem->listaAdj = novaAresta;

    novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->destino = origem;
    novaAresta->peso = peso;
    novaAresta->prox = vertDestino->listaAdj;
    vertDestino->listaAdj = novaAresta;

    printf("Aresta entre %d e %d com peso %d inserida.\n", origem, destino, peso);
}

// Função para remover arestas que apontam para um vértice
void removerArestasEntrada(Vertice* grafo, int id) {
    Vertice* atual = grafo;
    while (atual != NULL) {
        Aresta* anterior = NULL;
        Aresta* adj = atual->listaAdj;
        while (adj != NULL) {
            if (adj->destino == id) {
                if (anterior) {
                    anterior->prox = adj->prox;
                } else {
                    atual->listaAdj = adj->prox;
                }
                Aresta* temp = adj;
                adj = adj->prox;
                free(temp);
            } else {
                anterior = adj;
                adj = adj->prox;
            }
        }
        atual = atual->prox;
    }
}

void removerVertice(Vertice** grafo, int id) {
    Vertice* atual = *grafo;
    Vertice* anterior = NULL;

    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->prox;
    }

    if (!atual) {
        printf("Vértice %d não encontrado.\n", id);
        return;
    }

    if (anterior) {
        anterior->prox = atual->prox;
    } else {
        *grafo = atual->prox;
    }

    // Remove todas as arestas de entrada que apontam para o vértice
    removerArestasEntrada(*grafo, id);

    // Libera a lista de adjacências do vértice
    liberarListaAdj(atual->listaAdj);
    free(atual);
    printf("Vértice %d removido.\n", id);
}

void visualizarGrafo(Vertice* grafo) {
    while (grafo != NULL) {
        printf("Vértice %d:\n", grafo->id);
        Aresta* adj = grafo->listaAdj;
        while (adj != NULL) {
            printf("  -> %d (peso %d)\n", adj->destino, adj->peso);
            adj = adj->prox;
        }
        grafo = grafo->prox;
    }
}

void liberarGrafo(Vertice** grafo) {
    while (*grafo != NULL) {
        Vertice* temp = *grafo;
        liberarListaAdj(temp->listaAdj);
        *grafo = temp->prox;
        free(temp);
    }
}

int calcularGrau(Vertice* grafo, int id) {
    Vertice* vertice = encontrarVertice(grafo, id);
    if (!vertice) {
        printf("Vértice %d não encontrado.\n", id);
        return -1;
    }

    int grau = 0;
    Aresta* adj = vertice->listaAdj;
    while (adj != NULL) {
        grau++;
        adj = adj->prox;
    }

    return grau;
}

// Função auxiliar para busca em profundidade (DFS)
void dfs(Vertice* grafo, int id, bool* visitados, int* idParaIndice) {
    if (idParaIndice[id] == -1 || visitados[idParaIndice[id]]) return;

    visitados[idParaIndice[id]] = true;
    Vertice* vertice = encontrarVertice(grafo, id);
    if (!vertice) return;

    Aresta* adj = vertice->listaAdj;
    while (adj != NULL) {
        dfs(grafo, adj->destino, visitados, idParaIndice);
        adj = adj->prox;
    }
}

// Verifica se o grafo é conexo
bool grafoConexo(Vertice* grafo, int totalVertices) {
    if (!grafo) return false;

    // Mapeia IDs para índices sequenciais
    int* idParaIndice = (int*)malloc(totalVertices * sizeof(int));
    for (int i = 0; i < totalVertices; i++) {
        idParaIndice[i] = -1;
    }

    int indice = 0;
    Vertice* atual = grafo;
    while (atual != NULL) {
        idParaIndice[atual->id] = indice++;
        atual = atual->prox;
    }

    // Array para marcar vértices visitados
    bool* visitados = (bool*)calloc(totalVertices, sizeof(bool));

    // Realiza a DFS a partir do primeiro vértice
    dfs(grafo, grafo->id, visitados, idParaIndice);

    // Verifica se todos os vértices foram visitados
    for (int i = 0; i < totalVertices; i++) {
        if (idParaIndice[i] != -1 && !visitados[idParaIndice[i]]) {
            free(visitados);
            free(idParaIndice);
            return false;
        }
    }

    free(visitados);
    free(idParaIndice);
    return true;
}

// Função para adicionar um vértice à fila
void enfileirar(Fila** fila, int vertice) {
    Fila* novo = (Fila*)malloc(sizeof(Fila));
    novo->vertice = vertice;
    novo->prox = NULL;

    if (*fila == NULL) {
        *fila = novo;
    } else {
        Fila* temp = *fila;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novo;
    }
}

// Função para remover um vértice da fila
int desenfileirar(Fila** fila) {
    if (*fila == NULL) return -1;

    Fila* temp = *fila;
    int vertice = temp->vertice;
    *fila = temp->prox;
    free(temp);
    return vertice;
}

// Função para realizar a busca em largura (BFS)
void bfs(Vertice* grafo, int idInicial, int totalVertices) {
    if (!grafo) return;

    // Mapeia IDs para índices sequenciais
    int* idParaIndice = (int*)malloc(totalVertices * sizeof(int));
    for (int i = 0; i < totalVertices; i++) {
        idParaIndice[i] = -1;
    }

    int indice = 0;
    Vertice* atual = grafo;
    while (atual != NULL) {
        idParaIndice[atual->id] = indice++;
        atual = atual->prox;
    }

    // Array para marcar vértices visitados
    bool* visitados = (bool*)calloc(totalVertices, sizeof(bool));

    // Fila para a BFS
    Fila* fila = NULL;

    // Marca o vértice inicial como visitado e o enfileira
    visitados[idParaIndice[idInicial]] = true;
    enfileirar(&fila, idInicial);

    printf("Caminhamento em amplitude (BFS) a partir do vértice %d:\n", idInicial);

    while (fila != NULL) {
        int verticeAtual = desenfileirar(&fila);
        printf("%d ", verticeAtual);

        Vertice* vertice = encontrarVertice(grafo, verticeAtual);
        if (!vertice) continue;

        Aresta* adj = vertice->listaAdj;
        while (adj != NULL) {
            if (!visitados[idParaIndice[adj->destino]]) {
                visitados[idParaIndice[adj->destino]] = true;
                enfileirar(&fila, adj->destino);
            }
            adj = adj->prox;
        }
    }

    printf("\n");

    free(visitados);
    free(idParaIndice);
}

// Converte a lista de adjacências do grafo para uma matriz de adjacência
void converterParaMatriz(Vertice* grafo, int** matriz, int totalVertices) {
    // Inicializa a matriz com zeros
    for (int i = 0; i < totalVertices; i++) {
        for (int j = 0; j < totalVertices; j++) {
            matriz[i][j] = 0;
        }
    }

    // Mapeia IDs para índices sequenciais
    int* idParaIndice = (int*)malloc(totalVertices * sizeof(int));
    for (int i = 0; i < totalVertices; i++) {
        idParaIndice[i] = -1;
    }

    int indice = 0;
    Vertice* atual = grafo;
    while (atual != NULL) {
        idParaIndice[atual->id] = indice++;
        atual = atual->prox;
    }

    // Preenche a matriz de adjacência
    atual = grafo;
    while (atual != NULL) {
        Aresta* adj = atual->listaAdj;
        while (adj != NULL) {
            matriz[idParaIndice[atual->id]][idParaIndice[adj->destino]] = adj->peso;
            adj = adj->prox;
        }
        atual = atual->prox;
    }

    free(idParaIndice);
}

int main() {
    // Configura o locale para português
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Vertice* grafo = NULL;
    int opcao, id, origem, destino, peso, totalVertices = 0;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir Vértice\n");
        printf("2. Inserir Aresta\n");
        printf("3. Remover Vértice\n");
        printf("4. Visualizar Grafo\n");
        printf("5. Informar grau de um vértice\n");
        printf("6. Verificar se o grafo é conexo\n");
        printf("7. Converter para matriz de adjacência\n");
        printf("8. Realizar busca em largura (BFS)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o ID do vértice: ");
                scanf("%d", &id);
                inserirVertice(&grafo, id);
                totalVertices++;
                break;
            case 2:
                printf("Digite a origem, destino e peso da aresta: ");
                scanf("%d %d %d", &origem, &destino, &peso);
                inserirAresta(grafo, origem, destino, peso);
                break;
            case 3:
                printf("Digite o ID do vértice a ser removido: ");
                scanf("%d", &id);
                removerVertice(&grafo, id);
                totalVertices--;
                break;
            case 4:
                visualizarGrafo(grafo);
                break;
            case 5:
                printf("Digite o ID do vértice: ");
                scanf("%d", &id);
                int grau = calcularGrau(grafo, id);
                if (grau != -1) {
                    printf("Grau do vértice %d: %d\n", id, grau);
                }
                break;
            case 6:
                if (grafoConexo(grafo, totalVertices)) {
                    printf("O grafo é conexo.\n");
                } else {
                    printf("O grafo não é conexo.\n");
                }
                break;
            case 7: {
                int** matriz = (int**)malloc(totalVertices * sizeof(int*));
                for (int i = 0; i < totalVertices; i++) {
                    matriz[i] = (int*)malloc(totalVertices * sizeof(int));
                }
                converterParaMatriz(grafo, matriz, totalVertices);

                printf("Matriz de adjacência:\n");
                for (int i = 0; i < totalVertices; i++) {
                    for (int j = 0; j < totalVertices; j++) {
                        printf("%d ", matriz[i][j]);
                    }
                    printf("\n");
                }

                for (int i = 0; i < totalVertices; i++) {
                    free(matriz[i]);
                }
                free(matriz);
                break;
            }
            case 8:
                printf("Digite o ID do vértice inicial para a BFS: ");
                scanf("%d", &id);
                bfs(grafo, id, totalVertices);
                break;
            case 0:
                liberarGrafo(&grafo);
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}