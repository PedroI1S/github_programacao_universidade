#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Versão recursiva

int **Alocar_Matriz(int rows, int cols)
{
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL)
    {
        printf("Falha na alocação de memória!\n");
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL)
        {
            printf("Falha na alocação de memória!\n");
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
    char formatar[255];
    printf("\nDeseja remover a formatacao da string, remover os espaços e Case sensibility ('sim' para confirmar): ");
    fgets(formatar, sizeof(formatar), stdin);
    formatar[strcspn(formatar, "\n")] = 0;

    if (strcasecmp(formatar, "sim") == 0)
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
    putchar('\n');
}

void imprime_matriz(int **palindromo, int linha)
{
    printf("Matriz de palindromos:\n");
    for (int i = 0; i < linha; i++)
        printf("[%d, %d]\n", palindromo[i][0], palindromo[i][1]);
    putchar('\n');
}

void imprime_com_espacos(char *string, int **palindromo, int linha)
{
    int pos = 0;
    int i, j;

    for (i = 0; i < linha; i++)
    {
        for (j = pos; j < palindromo[i][0]; j++)
        {
            putchar(string[j]);
        }
        putchar('(');
        for (j = palindromo[i][0]; j <= palindromo[i][1]; j++)
        {
            putchar(string[j]);
        }
        putchar(')');
        pos = palindromo[i][1] + 1;
    }

    for (j = pos; j < strlen(string); j++)
    {
        putchar(string[j]);
    }

    putchar('\n');
    putchar('\n');
}

void imprime_indices(int **palindromo, int linha)
{
    for (int i = 0; i < linha; i++)
        printf("Palindromo de %d a %d\n", palindromo[i][0], palindromo[i][1]);
    putchar('\n');
}

void liberar_matriz(int **palindromo, int tamanho)
{
    for (int i = 0; i < tamanho / 2; i++)
        free(palindromo[i]);
    free(palindromo);
}


void encontra_maiores_palindromos(char *string, int **matriz, int tamanho, int *linha_mat, int n){
    int aux = 0;

    for (int i = tamanho - 1; i > n; i--)
    {
        if (string[i] == string[n])
        {
            for(int j = 0; j <= *linha_mat; j++)
                if(n >= matriz[j][0] && i <= matriz[j][1]){
                    aux = 1;
                    break;
                }
            if(aux == 1)
                break;
            aux = 0;

            int auxc = n, auxf = i;
            while (auxc < auxf && string[auxc] == string[auxf])
            {
                auxc++;
                auxf--;
            }
            if (auxc >= auxf)
            {
                matriz[*linha_mat][0] = n;
                matriz[*linha_mat][1] = i;
                (*linha_mat)++;
                break;
            }
        }
    }
    if (n + 1 < tamanho)
        encontra_maiores_palindromos(string, matriz, tamanho, linha_mat, n + 1);
}

void conta_palindromo(char *string, int tamanho, int *linha, int **palindromo){
    int **matriz = Alocar_Matriz(tamanho, 2);
    int linha_mat = 0;

    encontra_maiores_palindromos(string, matriz, tamanho, &linha_mat, 0);
    for(int i=0; i<linha_mat; i++){

        for(int j=0; j<linha_mat; j++){

            if(((matriz[i][0] < matriz[j][1])) && (matriz[i][1] > matriz[j][1] || ((matriz[i][1] - matriz[i][0]) >= (matriz[j][1] - matriz[j][0])))  ){

                if((matriz[i][1] - matriz[i][0]) > (matriz[j][1] - matriz[j][0])){
                    palindromo[*linha][0] = matriz[i][0];
                    palindromo[*linha][1] = matriz[i][1];
                    (*linha)++;
                    break;
                }else if((matriz[i][1] - matriz[i][0]) == (matriz[j][1] - matriz[j][0])){
                    int k, aux1 = 0, aux2 = 0;
                    
                    for(k=0; k<linha_mat; k++){
                        if((matriz[k][0] < matriz[j][1]) && (matriz[k][1] > matriz[j][1] || ((matriz[k][1] - matriz[k][0]) > (matriz[j][1] - matriz[j][0]))) && (matriz[k][1] - matriz[k][0]) > (matriz[j][1] - matriz[j][0])){
                            aux1++;
                        }
                        if(((matriz[k][0] < matriz[i][1])) && (matriz[k][1] > matriz[i][1] || ((matriz[k][1] - matriz[k][0]) > (matriz[i][1] - matriz[i][0]))) && (matriz[k][1] - matriz[k][0]) > (matriz[i][1] - matriz[i][0])){
                            aux2++;
                        }
                    }
                    if(aux1 == 0){
                        palindromo[*linha][0] = matriz[j][0];
                        palindromo[*linha][1] = matriz[j][1];
                        (*linha)++;
                        break;

                    }else if(aux2 == 0){
                        palindromo[*linha][0] = matriz[i][0];
                        palindromo[*linha][1] = matriz[i][1];
                        (*linha)++;
                        break;

                    }

                }
            }
        }

    }
}

int main(void)
{
    char string[500];
    int tamanho = 0;

    printf("O objetivo dessa aplicacao eh encontrar palindromos em palavras ou frases. \n\n");

    while (1)
    {
        printf("Insira a string a ser analisada (ou 'exit' para sair): ");
        fgets(string, sizeof(string), stdin);
        string[strcspn(string, "\n")] = 0;

        if (strcmp(string, "exit") == 0)
            break;

        padroniza_string(string);
        tamanho = strlen(string);

        int **palindromo = Alocar_Matriz(tamanho / 2, 2);
        if (palindromo == NULL)
            return 1;
        int linha = 0;
        conta_palindromo(string, tamanho, &linha, palindromo);
        imprime_indices(palindromo, linha);
        imprime_matriz(palindromo, linha);
        imprime_com_espacos(string, palindromo, linha);
        liberar_matriz(palindromo, linha);
    }

    return 0;
}
