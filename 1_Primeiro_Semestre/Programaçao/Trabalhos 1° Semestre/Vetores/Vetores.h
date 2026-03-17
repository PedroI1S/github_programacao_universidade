#include<stdlib.h>
#include<time.h>

void geradorDE(int vetor[], int tamanho, int limite)
{
    int i;

    srand(time(NULL));

    for(i=0; i<tamanho; i++)
    {
        vetor[i] = rand() % (limite+1);
    }
}

void geradorDEcomsinal(int vetor[], int tamanho, int limiteNegativo, int limitePositivo)
{
    int i;

    srand(time(NULL));

    for(i=0; i<tamanho; i++)
    {
        vetor[i] = rand() % (limitePositivo + limiteNegativo + 1) - limiteNegativo;
    }
}

void geradoeDEcomfaixa(int vetor[], int tamanho, int liminf, int limsup)
{
    int i;
    srand(time(NULL));

    for(i=0; i<tamanho; i++)
    {
        vetor[i] = (rand() % ((limsup - liminf) + 1)) + liminf;
    }
}

void geradoeDEcomfaixasemrepeticao(int vetor[], int tamanho, int liminf, int limsup)
{
    int i, j;
    srand(time(NULL));

    for(i=0; i<tamanho; i++)
    {
        vetor[i] = (rand() % ((limsup - liminf) + 1)) + liminf;
        for(j=0; j<i; j++)
        {
            if(vetor[i]==vetor[j])
            {
                vetor[i] = (rand() % ((limsup - liminf) + 1)) + liminf;
            }
        }
    }
}

void mostradorDE (int vetor[], int tamanho)
{
    int i;

    for(i=0; i<tamanho; i++)
    {
        printf("%-8d", vetor[i]);
    }
}

void ordenadorDE (int vetor[], int tamanho)
{
    int i, j, aux;
    for(i=(tamanho-1); i>0; i--)
    {
        for(j=0; j>i; j++);
        {
            if(vetor[j]>vetor[j+1])
            {
                aux=vetor[j];
                vetor[j]= vetor[j+1];
                vetor[j+1]=aux;
            }
        }
    }
}

void mostrarEPares(int vetor[], int tamanho)
{
    int j;

    for(j=2; j<tamanho; j++)
    {
        printf("%-3d", j);
        j+=2;
    }
}

void mostrarEImpares(int vetor[], int tamanho)
{
    int j;

    for(j=1; j<tamanho; j++)
    {
        printf("%-3d", j);
        j+=2;
    }
}

void geradorDEfloatcomcasas(float vetor[], int tamanho, int casas)
{
    int i;
    srand(time(NULL));

    for(i=0; i<tamanho; i++)
    {
        vetor[i] = ((float)(rand()) /RAND_MAX)*casas;
    }
}

void mostradorDEfloat (float vetor[], int tamanho)
{
    int i;

    for(i=0; i<tamanho; i++)
    {
        printf("%-8.2f", vetor[i]);
    }
}

void mostradorDEfloaintrvalo (float vetor[], int tamanho, int comeco)
{
    int i;

    for(i=comeco; i>tamanho; i--)
    {
        printf("%-8.2f", vetor[i]);
    }
}

float somaDEfloat (float vetor[], int tamanho)
{
    int i;
    float soma=0;

    for(i=0; i<tamanho; i++)
    {
        soma+=vetor[i];
    }
    return (soma);
}

int separadorDE (int vetor1[], int vetor2[], int vetor3[], int criterio)
{
    int i, k=(criterio-1), j=0;

    for(i=0; i<criterio; i++)
    {
        if(vetor2[i]<50)
        {
            vetor3[j]=vetor2[i];
            j++;
        }
        else
        {
            vetor3[k]=vetor2[i];
            k--;
        }

    }
    return (j);
}

int separadorDEfloat (float vetor1[], float vetor2[], float vetor3[], int criterio)
{
    int i, k=(criterio-1), j=0;

    for(i=0; i<criterio; i++)
    {
        if(vetor2[i]<criterio)
        {
            vetor3[j]=vetor2[i];
            j++;
        }
        else
        {
            vetor3[k]=vetor2[i];
            k--;
        }

    }
    return (j);
}

void geradorDEchar (int vetor[], int tamanho, int caps)
{
    int i;

    srand(time(NULL));

    for(i=0; i<tamanho; i++)
    {
        if(caps==0)
        {
            vetor[i] = rand() % 26 + 97;
        }
        else
        {
            vetor[i] = rand() % 26 + 65;
        }
    }
}

void mostradorDEchar (int vetor[], int tamanho, int colunas)
{
    int i, j=0;

    for(i=0; i<tamanho; i++)
    {
        printf("%-4c", (char)vetor[i]);
        j++;
        if(j==colunas)
        {
            printf("\n");
            j=0;
        }
    }
}

int Edemaisocorrencia (int vetor[],int tamanho)
{
    int cont=0, maior, i, j, k=0;

    for(i=0; i<tamanho; i++)
    {
        for(j=i; j<tamanho; j++)
        {
            if(vetor[i]==vetor[j])
            {
                cont++;
            }
        }
        if(cont>k)
        {
            maior=vetor[i];
            k=cont;
        }
        cont=0;
    }
    return (maior);
}
