#include <iostream>
#include <cmath>
#define num_quadros 3
using namespace std;

struct Pagina
{
    int id;
};

struct Memoria
{
    Pagina quadros[num_quadros];
};

int menor_valor(int vetor[], int tamanho)
{
    int menor = vetor[0];
    int menor_indice = 0;
    for (int i = 1; i < tamanho; ++i)
    {
        if (vetor[i] < menor)
        {
            menor = vetor[i];
            menor_indice = i;
        }
    }
    return menor_indice;
}

int proxima_posicao_de_memoria(Pagina vetor[], int tamanho, int inicio, int target)
{
    for (int i = inicio; i < tamanho; ++i)
    {
        if (vetor[i].id == target)
        {
            return i;
        }
    }
    return tamanho;
}

void escreve_evolução(Pagina memoria_quadros[], int falta_de_pagina, int tamanho)
{
    for (int i = 0; i < tamanho; ++i)
    {
        if (falta_de_pagina != -1 && i == falta_de_pagina)
        {
            cout << "[" << memoria_quadros[i].id << "] ";
        }
        else
        {
            cout << memoria_quadros[i].id << " ";
        }
    }
    cout << endl;
}

int FIFO(Memoria memoria, Pagina paginas_novas[], int quantidade_paginas)
{

    int fila_circular = 0;
    int falta_de_paginas = 0;
    int esta_na_memoria = 0; // 0 -> não esta na memoria // 1 -> esta na memoria

    cout << "Evolução da memória (FIFO):" << endl;
    for (int i = 0; i < quantidade_paginas; ++i)
    {
        for (int j = 0; j < num_quadros; ++j)
        {
            if (memoria.quadros[j].id == paginas_novas[i].id)
            {
                esta_na_memoria = 1;

                escreve_evolução(memoria.quadros, -1, num_quadros);
                j = num_quadros; // sai do for
            }
            else
            {
                esta_na_memoria = 0;
            }
        }
        if (esta_na_memoria == 0)
        {
            if (memoria.quadros[fila_circular].id == -1)
            {
                memoria.quadros[fila_circular] = paginas_novas[i];

                escreve_evolução(memoria.quadros, fila_circular, num_quadros);
                falta_de_paginas++;
                if (fila_circular >= num_quadros - 1)
                {
                    fila_circular = 0;
                }
                else
                {
                    fila_circular++;
                }
            }
            else
            {
                memoria.quadros[fila_circular] = paginas_novas[i];

                escreve_evolução(memoria.quadros, fila_circular, num_quadros);
                falta_de_paginas++;

                if (fila_circular >= num_quadros - 1)
                {
                    fila_circular = 0;
                }
                else
                {
                    fila_circular++;
                }
            }
        }
    }

    return falta_de_paginas;
}

// instante de tempo que a pagina foi utilizada é a chave desse algoritmo

int LRU(Memoria memoria, Pagina paginas_novas[], int quantidade_paginas)
{
    int tempo_de_uso[num_quadros];
    int falta_de_paginas = 0;
    int esta_na_memoria = 0; // 0 -> não esta na memoria // 1 -> esta na memoria
    int posicao_memoria = 0;

    cout << "Evolução da memória (LRU):" << endl;
    for (int i = 0; i < quantidade_paginas; ++i)
    {
        for (int j = 0; j < num_quadros; ++j)
        {

            if (memoria.quadros[j].id == paginas_novas[i].id)
            {
                esta_na_memoria = 1;
                posicao_memoria = j;
                j = num_quadros; // sai do for
            }
            else
            {
                esta_na_memoria = 0;
            }
        }

        if (esta_na_memoria == 1)
        {
            tempo_de_uso[posicao_memoria] = i + 1;
            escreve_evolução(memoria.quadros, -1, num_quadros);
        }
        else
        {

            if (i < num_quadros && memoria.quadros[i].id == -1)
            {
                memoria.quadros[i] = paginas_novas[i];
                tempo_de_uso[i] = i + 1;
                escreve_evolução(memoria.quadros, i, num_quadros);
                falta_de_paginas++;
            }
            else
            {
                int menor_indice = menor_valor(tempo_de_uso, num_quadros);
                memoria.quadros[menor_indice] = paginas_novas[i];
                tempo_de_uso[menor_indice] = i + 1;
                escreve_evolução(memoria.quadros, menor_indice, num_quadros);

                falta_de_paginas++;
            }
        }
    }

    return falta_de_paginas;
}

int algoritmo_otimo(Memoria memoria, Pagina paginas_novas[], int quantidade_paginas)
{
    int falta_de_paginas = 0;
    int esta_na_memoria = 0;

    cout << "Evolução da memória (Ótimo):" << endl;
    for (int i = 0; i < quantidade_paginas; ++i)
    {
        for (int k = 0; k < num_quadros; ++k)
        {
            if (memoria.quadros[k].id == paginas_novas[i].id)
            {
                esta_na_memoria = 1;
                escreve_evolução(memoria.quadros, -1, num_quadros);
                k = num_quadros; // sai do for
            }
            else
            {
                esta_na_memoria = 0;
            }
        }
        if (esta_na_memoria == 0)
        {
            if (i < num_quadros && memoria.quadros[i].id == -1)
            {
                memoria.quadros[i] = paginas_novas[i];
                escreve_evolução(memoria.quadros, i, num_quadros);
                falta_de_paginas++;
            }
            else
            {
                int proximo_uso = 0;
                int index_substituir = 0;
                for (int j = 0; j < num_quadros; ++j)
                {
                    if (proximo_uso < proxima_posicao_de_memoria(paginas_novas, quantidade_paginas, i + 1, memoria.quadros[j].id))
                    {
                        proximo_uso = proxima_posicao_de_memoria(paginas_novas, quantidade_paginas, i + 1, memoria.quadros[j].id);
                        index_substituir = j;
                    }
                }

                memoria.quadros[index_substituir] = paginas_novas[i];
                escreve_evolução(memoria.quadros, index_substituir, num_quadros);
                falta_de_paginas++;
            }
        }
    }

    return falta_de_paginas;
}

int main()
{
    Memoria memoria;

    for (int i = 0; i < num_quadros; ++i)
    {
        memoria.quadros[i].id = -1;
    }

    Pagina paginas[] = {{7}, {0}, {1}, {2}, {0}, {3}, {0}, {4}, {2}, {3}, {0}, {3}, {2}, {1}, {2}, {0}, {1}, {7}, {0}, {1}};
    int num_paginas = 20;

    cout << "Iniciando teste FIFO..." << endl;

    int faltas = FIFO(memoria, paginas, num_paginas);
    cout << "Total de faltas de pagina (FIFO): " << faltas << endl;
    faltas = LRU(memoria, paginas, num_paginas);
    cout << "Total de faltas de paginas (LRU): " << faltas << endl;
    faltas = algoritmo_otimo(memoria, paginas, num_paginas);
    cout << "Total de faltas de paginas (Ótimo): " << faltas << endl;

    return 0;
}