#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int subsequencia_maxima(int n, int vetor[]) {
    int max_soma = INT_MIN;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int soma_atual = 0;

            for (int k = i; k <= j; k++) {
                soma_atual += vetor[k];
            }

            if (soma_atual > max_soma) {
                max_soma = soma_atual;
            }
        }
    }
    
    return max_soma;
}

int main() {
    int n;
    

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);
    
    int vetor[n];
    

    printf("Digite os elementos do vetor separados por espaço: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }
    

    int resultado = subsequencia_maxima(n, vetor);
    printf("O somatório da subsequência máxima é: %d\n", resultado);
    
    return 0;
}
