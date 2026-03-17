#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Fila.h"

int read(Fila *f)
{
    if (!fila_cheia(f))
    {
        int aux;
        do
        {
            scanf("%d", &aux);
            if (aux != -1)
            {
                enfileirar(f, aux);
            }
        } while (aux != -1);
        return 1;
    }
    return 0;
}

Fila *intercalar(Fila *f1, Fila *f2, Fila *f3)
{
    if (!fila_vazia(f1) && !fila_vazia(f2))
    {
        while (!fila_vazia(f1) || !fila_vazia(f2))
        {
            if (verificar_inicio(f1) > verificar_inicio(f2))
            {
                if (!fila_vazia(f1))
                {
                    enfileirar(f3, desenfileirar(f1));
                }
                if (!fila_vazia(f2))
                {
                    enfileirar(f3, desenfileirar(f2));
                }
            }
            else
            {
                if (!fila_vazia(f2))
                {
                    enfileirar(f3, desenfileirar(f2));
                }
                if (!fila_vazia(f1))
                {
                    enfileirar(f3, desenfileirar(f1));
                }
            }
        }
        return f3;
    }
    return NULL;
}

int main(void)
{
    Fila *f1, *f2, *f3;

    f1 = criar_fila();
    f2 = criar_fila();
    f3 = criar_fila();

    read(f1);
    read(f2);

    imprimir_fila(intercalar(f1, f2, f3));

    liberar_fila(f1);
    liberar_fila(f2);
    liberar_fila(f3);

    return 0;
}
