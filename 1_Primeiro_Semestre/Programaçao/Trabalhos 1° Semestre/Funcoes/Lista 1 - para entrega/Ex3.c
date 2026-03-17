void desenho (int linhas, int colunas, int caractere)
{
    while (linhas>0)
    {
        int i=colunas;

        while(i>0)
        {
            printf("%-3c", (char)caractere);
            i--;
        }
        printf("\n");
        linhas--;
    }
}

int main (void)
{
    int linhas, colunas;
    char caractere, ch;
    do
    {
        printf("Informe um numero de linhas: ");
        scanf("%d", &linhas);
        printf("Informe um numero de colunas: ");
        scanf("%d", &colunas);
        printf("Informe um caracter: ");
        scanf(" %c", &caractere);

        desenho(linhas, colunas, caractere);

        printf("\n\nDeseja continuar o programa (S/N): ");
        scanf(" %c", &ch);
        printf("\n\n\n");
    }
    while (ch != 'n' && ch != 'N');
}

