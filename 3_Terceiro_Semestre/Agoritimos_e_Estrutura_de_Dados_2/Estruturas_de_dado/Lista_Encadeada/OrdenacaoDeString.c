#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct Cell Cell;

typedef struct ListaE ListaE;

struct Cell
{
    char *item;

    Cell *next;
};

struct ListaE
{
    Cell *head;
};

Cell *criar_celula(char *key)
{
    Cell *c = (Cell *)malloc(sizeof(Cell));
    c->item = malloc(strlen(key) + 1);
    strcpy(c->item, key);

    c->next = NULL;

    return c;
}


ListaE *criar_listaE()
{
    ListaE *l = (ListaE *)malloc(sizeof(ListaE));

    l->head = NULL;

    return l;
}

int listaE_vazia(ListaE *l)
{
    return (l == NULL) || (l->head == NULL);
}

void inserir_primeiro(char *key, ListaE *l)
{
    Cell *aux;

    if (l == NULL)
        l = criar_listaE();

    aux = criar_celula(key);

    aux->next = l->head;

    l->head = aux;
    
}

void imprimir(ListaE *l)
{
    Cell *aux;

    if (!listaE_vazia(l))
    {
        aux = l->head;

        while (aux != NULL)
        {
            printf("%s ", aux->item);

            aux = aux->next;
        }

        printf("\n");
    }
}

int liberar_LE(ListaE *l)
{
    Cell *aux = NULL;

    if (l != NULL)
    {
        while (l->head != NULL)
        {
            aux = l->head;

            l->head = aux->next;

            free(aux->item);
            free(aux);
        }

        free(l);

        return 1;
    }

    return 0;
}

int tamanho_LE(ListaE *l)
{
    Cell *aux;
    int tam = 0;

    if (!listaE_vazia(l))
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

void bubblesort(ListaE *l)
{
    int tam = tamanho_LE(l);

    Cell *auxA, *auxB;
    char *vAux;
    int i;

    while (tam > 1)
    {
        i = 0;
        auxA = l->head;
        auxB = auxA->next;

        while ((auxB != NULL) && (i < tam))
        {
            int aux = strcmp(auxA->item, auxB->item);
            if (aux > 0)
            {
                vAux = auxA->item;
                auxA->item = auxB->item;
                auxB->item = vAux;
            }

            auxA = auxB;
            auxB = auxA->next;
            i++;
        }
        tam--;
    }
}


int main(){
    ListaE *l = criar_listaE();
    char *item = malloc(sizeof(char)*255); 
    int x=0;

    scanf("%d", &x);
    
    while(x>0){
        scanf("%s ", item);
        
        inserir_primeiro(item, l);

        x--; 
    }
    
    bubblesort(l);
    
    imprimir(l);
    
    liberar_LE(l);
    
    return 0;
}