#include "grafo.h"

int main() {
    int opcao, numVertices, origem, destino, vertice;

    printf("Digite o número de vértices do grafo: ");
    scanf("%d", &numVertices);

    Grafo *grafo = criarGrafo(numVertices);

    do {
        printf("\nMenu:\n");
        printf("1. Inserir Aresta\n");
        printf("2. Remover Aresta\n");
        printf("3. Remover Vértice\n");
        printf("4. Inserir Vértice\n");
        printf("5. Visualizar Grafo\n");
        printf("6. Grafo Modelo\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a origem e o destino da aresta: ");
                scanf("%d %d", &origem, &destino);
                inserirAresta(grafo, origem, destino);
                break;
            case 2:
                printf("Digite a origem e o destino da aresta a ser removida: ");
                scanf("%d %d", &origem, &destino);
                removerAresta(grafo, origem, destino);
                break;
            case 3:
                printf("Digite o vértice a ser removido: ");
                scanf("%d", &vertice);
                removerVertice(grafo, vertice);
                break;
            case 4:
                inserirVertice(grafo);
                break;
            case 5:
                visualizarGrafo(grafo);
                break;
            case 6:
                for(int i=grafo->numVertices; i<10; i++)
                    inserirVertice(grafo);
                inserirAresta(grafo, 1, 2);
                inserirAresta(grafo, 1, 6);
                inserirAresta(grafo, 2, 4);
                inserirAresta(grafo, 2, 3);
                inserirAresta(grafo, 3, 5);
                inserirAresta(grafo, 4, 6);
                inserirAresta(grafo, 4, 5);
                inserirAresta(grafo, 4, 7);
                inserirAresta(grafo, 7, 8);
                inserirAresta(grafo, 7, 9);
                break;
            case 7:
                liberarGrafo(grafo);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 7);

    return 0;
}
