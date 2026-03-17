#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct list
{
    int item[MAX_SIZE];
    int qtd;
} list;

list *create()
{
    list *l = (list *)(malloc(sizeof(list)));
    l->qtd = 0;

    return l;
}

int empty(list *l)
{
    if (l == NULL || l->qtd == 0)
    {
        return 1;
    }
    return 0;
}

int full(list *l)
{
    if (l->qtd == MAX_SIZE)
    {
        return 1;
    }
    return 0;
}

int insert(list *l, int key)
{
    if (full(l) == 0)
    {
        l->item[l->qtd] = key;
        l->qtd++;
        return 1;
    }
    return 0;
}

int imprint(list *l)
{
    if (empty(l) == 0)
    {
        for (int i = 0; i < (l->qtd); i++)
        {
            printf("%d ", l->item[i]);
        }
        return 1;
    }
    return 0;
}

int buscar(list *l, int key)
{
    int i = -1;

    if (empty(l) == 0)
    {
        do
        {
            i++;
        } while (l->item[i] != key);
        return i;
    }
    return -1;
}

int remove_num(list *l, int key)
{
    if (empty(l) != 0)
    {
        for (int i = buscar(l, key); i < (l->qtd) - 1; i++)
        {
            l->item[i] = l->item[i + 1];
            l->qtd--;
        }
        return 1;
    }
    return 0;
}

int remove_pos(list *l, int j)
{
    if (empty(l) == 0)
    {
        for (int i = j; i < (l->qtd); i++)
        {
            l->item[i] = l->item[i + 1];
        }
        l->qtd--;

        return 1;
    }
    return 0;
}

void verify_rep(list *l)
{
    for (int i = 0; i < (l->qtd); i++)
    {
        for (int j = (i + 1); j < (l->qtd) - 1; j++)
        {
            if (l->item[i] == l->item[j])
            {
                remove_pos(l, j);
            }
        }
    }
}

list *intercal(list *l1, list *l2)
{
    if (empty(l1) == 0 && empty(l2) == 0)
    {
        list *l3 = create();
        int j = l1->qtd, k = l2->qtd;

        for (int i = 0; i < l1->qtd || i < l2->qtd; i++)
        {
            if (j > 0)
            {
                l3->item[l3->qtd] = l1->item[i];
                l3->qtd++;
                j--;
            }
            if (k > 0)
            {
                l3->item[l3->qtd] = l2->item[i];
                l3->qtd++;
                k--;
            }
        }
        return l3;
    }
    return NULL;
}

void read(list *l1, list *l2)
{
    int n = 0;
    while (n != -1)
    {
        scanf("%d", &n);
        if (n != -1)
        {
            insert(l1, n);
        }
    }
    n = 0;
    while (n != -1)
    {
        scanf("%d", &n);
        if (n != -1)
        {
            insert(l2, n);
        }
    }
}

int main(void)
{
    int aux;
    list *l1 = create(), *l2 = create();

    scanf("%d", &aux);
    list *l3[aux];
    for (int i = 0; i < aux; i++)
    {
        l1->qtd = 0;
        l2->qtd = 0;
        read(l1, l2);
        l3[i] = create();
        l3[i] = intercal(l1, l2);
    }

    for (int i = 0; i < aux; i++)
    {
        verify_rep(l3[i]);
        imprint(l3[i]);
        free(l3[i]);
        printf("\n");
    }

    free(l1);
    free(l2);

    return 0;
}