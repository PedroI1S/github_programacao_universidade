#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void conta_palindromo(char *string, int comeco, int fim, int **palindromo, int *linha){
    int i, aux_c, aux_f;
    int aux = 0;

    for (int intervalo = fim - comeco; intervalo >= 1; intervalo--)
    {
        for (i = comeco; i + intervalo <= fim; i++)
        {
            if (string[i] == string[i + intervalo])
            {
                aux_c = i + 1;
                aux_f = i + intervalo - 1;
                aux = 1;

                while (aux_c < aux_f)
                {
                    if (string[aux_c] != string[aux_f])
                    {
                        aux = 0;
                        break;
                    }
                    aux_c++;
                    aux_f--;
                }

                if (aux)
                {
                    palindromo[*linha][0] = i;
                    palindromo[*linha][1] = i + intervalo;
                    (*linha)++;

                    if (i > comeco)
                    {
                        conta_palindromo(string, comeco, i - 1, palindromo, linha);
                    }
                    if (i + intervalo + 1 < fim)
                    {
                        conta_palindromo(string, i + intervalo + 1, fim, palindromo, linha);
                    }

                    return;
                }
            }
        }
    }
}

int **Alocar_Matriz(int rows, int cols){
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL)
        {
            printf("Memory allocation failed!\n");
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

void padroniza_string(char *str)
{
        int i = 0, j = 0;
        while (str[i])
        {
            if (str[i] != ' ')
                str[j++] = tolower(str[i]);
            i++;
        }
        str[j] = '\0';
}

void imprime_matriz(int **palindromo, int linha, FILE *arq)
{
    char aux[20];
    fputs("Matriz de palindromos\n", arq);
    for (int i = 0; i < linha; i++){
    
        fprintf(arq, "[%d, ", palindromo[i][0]);
        fprintf(arq, "%d]", palindromo[i][1]);
        fputc('\n', arq);
    }
    fputc('\n', arq);
}

void imprime_com_espacos(char *string, int **palindromo, int linha, FILE *arq)
{
    int pos = 0;
    int i, j, aux;

    for (i = 0; i < linha; i++)
    {
        for (j = pos; j < palindromo[i][0]; j++)
        {
            fputc(string[j], arq);
        }
        fputc('(', arq);
        for (j = palindromo[i][0]; j <= palindromo[i][1]; j++)
        {
            fputc(string[j], arq);
        }
        fputc(')', arq);
        pos = palindromo[i][1] + 1;
    }
    aux = strlen(string);
    for (j = pos; j < aux; j++)
    {
        fputc(string[j], arq);
    }
    fputc('\n', arq);
    fputc('\n', arq);
}

void imprime_indices(int **palindromo, int linha, FILE *arq)
{
    for (int i = 0; i < linha; i++){
        fprintf(arq, "Palindromo de %d a %d\n", palindromo[i][0], palindromo[i][1]);
        
    }
    fputc('\n', arq);
}

void liberar_matriz(int **palindromo, int tamanho){
    for (int i = 0; i < tamanho / 2; i++)
        free(palindromo[i]);
    free(palindromo);
}

int compare(const void *a, const void *b){
    int *palindromoA = *(int **)a;
    int *palindromoB = *(int **)b;

    return palindromoA[0] - palindromoB[0];
}

void ordenar_palindromos(int **palindromo, int linha){
    qsort(palindromo, linha, sizeof(int *), compare);
}

int main(void){
    char string[500];
    int tamanho = 0;
    FILE *entrada;
    FILE *saida;

    entrada = fopen("entrada.txt", "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }
    
    saida = fopen("saida.txt", "w");
    if (saida == NULL) {
        fclose(entrada);
        return 1;
    }

    while (fgets(string, sizeof(string), entrada) != NULL)
    {
        if (strlen(string) < 2)
            continue;

        padroniza_string(string);
        tamanho = strlen(string);

        int **palindromo = Alocar_Matriz(tamanho / 2, 2);
        if (palindromo == NULL)
            return 1;

        int linha = 0;

        conta_palindromo(string, 0, tamanho - 1, palindromo, &linha);
        ordenar_palindromos(palindromo, linha);

        //imprime_matriz(palindromo, linha, saida);
        imprime_com_espacos(string, palindromo, linha, saida);

        liberar_matriz(palindromo, tamanho);
    }
    fclose(entrada);
    fclose(saida);
    return 0;
}
