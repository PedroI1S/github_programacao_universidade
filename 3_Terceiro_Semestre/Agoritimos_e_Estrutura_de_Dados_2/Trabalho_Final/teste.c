#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h> // Para usar o tipo 'bool'
#include <limits.h>  // Para usar INT_MAX

// Função para limpar a string (idêntica à sua)
void padroniza_string(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ' ')
            str[j++] = tolower(str[i]);
        i++;
    }
    str[j] = '\0';
}

// Função principal que resolve o problema com DP
void solve_and_print(const char *str, FILE *arq_saida) {
    int n = strlen(str);
    if (n == 0) {
        fputc('\n', arq_saida);
        return;
    }

    // --- FASE 1: Pré-computar todos os palíndromos em O(n²) ---
    // is_palindrome[i][j] é true se a substring str[i...j] for um palíndromo.
    bool is_palindrome[n][n];
    memset(is_palindrome, 0, sizeof(is_palindrome)); // Inicializa com false

    // Todo caractere sozinho é um palíndromo
    for (int i = 0; i < n; i++) {
        is_palindrome[i][i] = true;
    }

    // Verifica palíndromos de tamanho 2
    for (int i = 0; i < n - 1; i++) {
        if (str[i] == str[i + 1]) {
            is_palindrome[i][i + 1] = true;
        }
    }

    // Verifica palíndromos de tamanho 3 a n
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            // É um palíndromo se as pontas forem iguais e o miolo também for.
            if (str[i] == str[j] && is_palindrome[i + 1][j - 1]) {
                is_palindrome[i][j] = true;
            }
        }
    }

    // --- FASE 2: Encontrar a partição ótima (com menos cortes) em O(n²) ---
    if (!is_palindrome[0][n - 1]) { // Otimização: se a string inteira não for palíndromo, parta-a.
        int cuts[n + 1];  // cuts[i] = o mínimo de palíndromos para o prefixo str[0...i-1]
        int parent[n + 1]; // parent[i] = onde começa o último palíndromo da partição ótima de str[0...i-1]

        for (int i = 0; i <= n; i++) {
            cuts[i] = INT_MAX;
        }
        cuts[0] = 0;
        parent[0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                // Se str[j...i-1] for um palíndromo...
                if (is_palindrome[j][i - 1]) {
                    // ...e se usar essa partição resulta em menos cortes...
                    if (cuts[j] != INT_MAX && cuts[j] + 1 < cuts[i]) {
                        // ...atualizamos para esta solução melhor.
                        cuts[i] = cuts[j] + 1;
                        parent[i] = j;
                    }
                }
            }
        }
        
        // --- FASE 3: Reconstruir e imprimir o resultado em O(n) ---
        int end_indices[n];
        int count = 0;
        int current = n;
        while(current > 0) {
            end_indices[count++] = current;
            current = parent[current];
        }

        int pos = 0;
        for(int i = count - 1; i >= 0; i--) {
            int start = parent[end_indices[i]];
            int end = end_indices[i] - 1;
            
            for(int k = pos; k < start; k++) fputc(str[k], arq_saida);
            fputc('(', arq_saida);
            for(int k = start; k <= end; k++) fputc(str[k], arq_saida);
            fputc(')', arq_saida);
            pos = end + 1;
        }

    } else { // Se a string inteira for um palíndromo, a solução é trivial
        fputc('(', arq_saida);
        fputs(str, arq_saida);
        fputc(')', arq_saida);
    }
    
    fputc('\n', arq_saida);
}


int main(void) {
    char string[500];
    FILE *entrada;
    FILE *saida;

    entrada = fopen("entrada.txt", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    saida = fopen("saida.txt", "w");
    if (saida == NULL) {
        printf("Erro ao abrir o arquivo de saida.\n");
        fclose(entrada);
        return 1;
    }

    while (fgets(string, sizeof(string), entrada) != NULL) {
        // Remove a quebra de linha que fgets pode ler
        string[strcspn(string, "\n")] = 0;

        padroniza_string(string);
        solve_and_print(string, saida);
    }

    fclose(entrada);
    fclose(saida);
    return 0;
}