#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int id;
    int e;
    int d;
} tarefa;

void caminho_g(tarefa *tarefas, int n) {
    for (int i = 0; i < n - 1; i++) {
        int troca = 0;
        
        for (int j = 0; j < n - 1 - i; j++) {

            if ((tarefas[j].d - tarefas[j].e) < (tarefas[j + 1].d - tarefas[j + 1].e)) {
                tarefa aux = tarefas[j];
                tarefas[j] = tarefas[j + 1];
                tarefas[j + 1] = aux;
                
                troca = 1;
            }
        }        
        if (troca == 0) {
            break;
        }
    }
}


int main() {
    int n=0, deadline=0, tempo_execucao=0;
    
    scanf("%d", &n);
    tarefa *tarefas = malloc(sizeof(tarefa)*n);;
    
    for (int i = 0; i < n; i++) {
        tarefas[i].id = i;
        scanf("%d %d", &tarefas[i].e, &tarefas[i].d);
    }
    caminho_g(tarefas, n);
    
    for (int i = 0; i < n; i++) {
        tempo_execucao += tarefas[i].e;
        deadline += tarefas[i].d;
        printf("%d ", tarefas[i].id);
    }
    printf("\n");
    
    int atraso = deadline - tempo_execucao;
    if(atraso>=0)
        atraso = 0;
    else
        atraso*=-1;
    
    printf("%d", atraso);
    
    return 0;
}