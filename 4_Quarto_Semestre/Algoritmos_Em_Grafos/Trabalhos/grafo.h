#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura para o nó da lista de adjacência
typedef struct No {
    int vertice;
    struct No *proximo;
} No;

// Estrutura para representar o grafo
typedef struct Grafo {
    int numVertices;
    No **listaAdjacencia;
} Grafo;

// Função para criar um novo nó
No *criarNo(int vertice) {
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->vertice = vertice;
    novoNo->proximo = NULL;
    return novoNo;
}

// Função para inicializar o grafo
Grafo *criarGrafo(int numVertices) {
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo->numVertices = numVertices;
    grafo->listaAdjacencia = (No **)malloc(numVertices * sizeof(No *));
    for (int i = 0; i < numVertices; i++) {
        grafo->listaAdjacencia[i] = NULL;
    }
    return grafo;
}

// Função para verificar se uma aresta já existe
bool arestaExiste(Grafo *grafo, int origem, int destino) {
    No *atual = grafo->listaAdjacencia[origem];
    while (atual) {
        if (atual->vertice == destino) {
            return true;
        }
        atual = atual->proximo;
    }
    return false;
}

// Função para inserir uma aresta
void inserirAresta(Grafo *grafo, int origem, int destino) {
    if (origem >= grafo->numVertices || destino >= grafo->numVertices) {
        printf("Erro: Vértice inexistente.\n");
        return;
    }

    if (arestaExiste(grafo, origem, destino)) {
        printf("Erro: Aresta já existe.\n");
        return;
    }

    // Inserir destino na lista de origem
    No *novoNo = criarNo(destino);
    novoNo->proximo = grafo->listaAdjacencia[origem];
    grafo->listaAdjacencia[origem] = novoNo;

    // Como o grafo não é orientado, inserir origem na lista de destino
    novoNo = criarNo(origem);
    novoNo->proximo = grafo->listaAdjacencia[destino];
    grafo->listaAdjacencia[destino] = novoNo;
}

// Função para remover uma aresta
void removerAresta(Grafo *grafo, int origem, int destino) {
    if (origem >= grafo->numVertices || destino >= grafo->numVertices) {
        printf("Erro: Vértice inexistente.\n");
        return;
    }

    No **atual = &grafo->listaAdjacencia[origem];
    while (*atual && (*atual)->vertice != destino) {
        atual = &(*atual)->proximo;
    }
    if (*atual) {
        No *temp = *atual;
        *atual = temp->proximo;
        free(temp);
    }

    atual = &grafo->listaAdjacencia[destino];
    while (*atual && (*atual)->vertice != origem) {
        atual = &(*atual)->proximo;
    }
    if (*atual) {
        No *temp = *atual;
        *atual = temp->proximo;
        free(temp);
    }
}

// Função para remover um vértice
void removerVertice(Grafo *grafo, int vertice) {
    if (vertice >= grafo->numVertices) {
        printf("Erro: Vértice inexistente.\n");
        return;
    }

    // Remover todas as arestas conectadas ao vértice
    for (int i = 0; i < grafo->numVertices; i++) {
        if (i != vertice) {
            removerAresta(grafo, i, vertice);
        }
    }

    // Liberar a lista de adjacência do vértice
    No *temp = grafo->listaAdjacencia[vertice];
    while (temp) {
        No *aux = temp;
        temp = temp->proximo;
        free(aux);
    }
    grafo->listaAdjacencia[vertice] = NULL;

    // Ajustar listas de adjacências
    for (int i = vertice; i < grafo->numVertices - 1; i++) {
        grafo->listaAdjacencia[i] = grafo->listaAdjacencia[i + 1];
    }

    grafo->numVertices--;
    grafo->listaAdjacencia = (No **)realloc(grafo->listaAdjacencia, grafo->numVertices * sizeof(No *));
    printf("Vértice %d removido com sucesso.\n", vertice);
}

// Função para inserir um vértice
void inserirVertice(Grafo *grafo) {
    grafo->numVertices++;
    grafo->listaAdjacencia = (No **)realloc(grafo->listaAdjacencia, grafo->numVertices * sizeof(No *));
    grafo->listaAdjacencia[grafo->numVertices - 1] = NULL;
    printf("Vértice %d inserido com sucesso.\n", grafo->numVertices - 1);
}

// Função para imprimir o grafo
void visualizarGrafo(Grafo *grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        No *temp = grafo->listaAdjacencia[i];
        printf("Vértice %d:\n", i);
        while (temp) {
            printf(" -> %d", temp->vertice);
            temp = temp->proximo;
        }
        printf("\n");
    }
}

// Função para liberar memória
void liberarGrafo(Grafo *grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        No *temp = grafo->listaAdjacencia[i];
        while (temp) {
            No *aux = temp;
            temp = temp->proximo;
            free(aux);
        }
    }
    free(grafo->listaAdjacencia);
    free(grafo);
}
