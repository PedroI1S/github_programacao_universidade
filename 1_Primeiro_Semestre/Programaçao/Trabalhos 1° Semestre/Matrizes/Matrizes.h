void GM2 (int linhas, int colunas, int matriz[linhas][colunas], int limite)
{
    int i=0, j=0;

    srand(time(NULL));

    while(j<linhas)
    {
        matriz[i][j] = (rand() % limite) + 1;

        if(i==(colunas-1))
        {
            j++;
            i=-1;
        }
        i++;
    }
}

void GM3 (int linhas, int colunas, int profundidade, int matriz[profundidade][linhas][colunas], int limite)
{
    int i=0, j=0, k=0;

    srand(time(NULL));

    while(k<profundidade)
    {
        matriz[k][i][j] = (rand() % limite) + 1;

        if(i==(colunas-1))
        {
            j++;
            i=-1;
        }

        if(j==(linhas-1))
        {
            k++;
            j=0;
        }

        i++;
    }
}

void MM2 (int linhas, int colunas, int matriz[linhas][colunas])
{
    int i=0, j=0;

    while(j<linhas)
    {
        printf("%-4d", matriz[i][j]);

        if(i==(colunas-1))
        {
            printf("\n");
            j++;
            i=-1;
        }
        i++;
    }
}

void MM3 (int linhas, int colunas, int profundidade, int matriz[profundidade][linhas][colunas])
{
    int i=0, j=0, k=0;

    while(k<profundidade)
    {
        if(i==0 && j==0)
        {
            printf("\n\nCamada %d\n", k+1);
        }
        printf("%-4d", matriz[k][i][j]);

        if(i==(colunas-1))
        {
            printf("\n");
            j++;
            i=-1;
        }

        if(j==(linhas-1))
        {
            k++;
            j=0;
        }

        i++;
    }
}
