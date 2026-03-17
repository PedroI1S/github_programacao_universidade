#include <stdio.h>
#include <stdlib.h>

typedef struct CellDE CellDE;

typedef struct ListaDE ListaDE;

struct CellDE
{
    int item;
    CellDE *previous, *next;
};

struct ListaDE
{
    CellDE *head;
};

CellDE *criar_celulaDE(int key)
{
    CellDE *c = (CellDE *)malloc(sizeof(CellDE));
    c->item = key;

    c->previous = c->next = NULL;

    return c;
}

ListaDE *criar_ListaDE()
{
    ListaDE *l = (ListaDE *)malloc(sizeof(ListaDE));

    l->head = NULL;

    return l;
}

int ListaDE_vazia(ListaDE *l)
{
    return (l == NULL) || (l->head == NULL);
}

int procurar(int key, ListaDE *l)
{
    CellDE *aux;

    if (l != NULL)
    {
        aux = l->head;
        while (aux != NULL)
        {
            if (aux->item == key)
                return 1;

            aux = aux->next;
        }
    }

    return 0;
}

void inserir_primeiro(int key, ListaDE *l)
{
    CellDE *aux;

    if (l == NULL)
        l = criar_ListaDE();

    aux = criar_celulaDE(key);

    aux->next = l->head;

    if (l->head != NULL)
        l->head->previous = aux;
    l->head = aux;
}

void inserir_ultimo(int key, ListaDE *l)
{
    CellDE *aux, *nova;

    if (l == NULL)
        l = criar_ListaDE();

    if (ListaDE_vazia(l))
        inserir_primeiro(key, l);
    else
    {
        aux = l->head;

        while (aux->next != NULL)
            aux = aux->next;

        nova = criar_celulaDE(key);

        aux->next = nova;
        nova->previous = aux;
    }
}

int remover(int key, ListaDE *l)
{
    CellDE *auxA;

    if (!ListaDE_vazia(l))
    {
        auxA = l->head;
        if (auxA->item == key)
        {
            l->head = l->head->next;
            l->head->previous = NULL;
            free(auxA);

            return 1;
        }
        else
        {
            while ((auxA != NULL) && (auxA->item != key))
                auxA = auxA->next;

            if (auxA != NULL)
            {
                auxA->previous->next = auxA->next;

                if (auxA->next != NULL)
                    auxA->next->previous = auxA->previous;
            }

            free(auxA);

            return 1;
        }
    }

    return 0;
}

void imprimir(ListaDE *l)
{
    CellDE *aux;

    if (!ListaDE_vazia(l))
    {
        aux = l->head;

        while (aux != NULL)
        {
            printf("%d ", aux->item);

            aux = aux->next;
        }

        printf("\n");
    }
}

int liberar_LE(ListaDE *l)
{
    CellDE *aux = NULL;
    if (l != NULL)
    {
        while (l->head != NULL)
        {
            aux = l->head;

            l->head = aux->next;

            free(aux);
        }

        free(l);

        return 1;
    }

    return 0;
}

int tamanho_LE(ListaDE *l)
{
    CellDE *aux;
    int tam = 0;

    if (!ListaDE_vazia(l))
    {
        aux = l->head;

        while (aux != NULL)
        {
            aux = aux->next;

            tam++;
        }
    }

    return tam;
}

int inserir_por_ultimo(ListaDE *l, int key)
{
    ListaDE *aux = l;

    if (l->head->next == NULL)
    {
        CellDE *ultima = criar_celulaDE(key);
        l->head->next = ultima;
        return 1;
    }
    aux->head = l->head->next;
    return inserir_por_ultimo(aux, key);
}

int procurar_item(ListaDE *l, int key)
{
    ListaDE *aux = l;

    if (l->head->item == key)
        return 1;
    if (l->head->next == NULL)
        return 0;
    else
    {
        aux->head = l->head->next;
        return procurar_item(aux, key);
    }
}

void remove_rep(ListaDE *list)
{
    CellDE *cell = list->head, *aux;

    while (cell != NULL)
    {
        aux = cell->next;
        while (aux != NULL)
        {
            if (aux->item == cell->item)
            {
                if (aux->next != NULL)
                    aux->next->previous = aux->previous;
                aux->previous->next = aux->next;
                CellDE *rem = aux;
                aux = aux->next;
                free(rem);
            }
            else
                aux = aux->next;
        }

        cell = cell->next;
    }
}

/*void remove_rep(ListaDE *list) {
    CellDE *current = list->head;
    CellDE *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        while (nextNode != NULL) {
            if (current->item == nextNode->item) {
                // Remove the duplicate node
                if (nextNode->next != NULL)
                    nextNode->next->previous = nextNode->previous;
                nextNode->previous->next = nextNode->next;
                CellDE *temp = nextNode;
                nextNode = nextNode->next;
                free(temp);
            } else {
                nextNode = nextNode->next;
            }
        }
        current = current->next;
    }
}*/

int main(void)
{
    ListaDE *l1 = criar_ListaDE();
    int aux = 0;

    while (1)
    {
        scanf("%d", &aux);
        if (aux == -1)
            break;
        inserir_ultimo(aux, l1);
    }

    remove_rep(l1);
    imprimir(l1);
    // liberar_LE(l1);
}