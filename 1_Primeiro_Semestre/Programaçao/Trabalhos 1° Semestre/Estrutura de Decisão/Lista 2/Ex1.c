#include <stdio.h>

int main (void)
{
    int L1, L2, L3, A, B, C;

    printf("indique tres lados de um triangulo:\n");
    scanf("%d %d %d", &L1, &L2, &L3);

    if(L1<L2 && L1>L3 || L1>L2 && L1<L3)
    {
        B=L1;
        if(L2>L3)
        {
            A=L2;
            C=L3;
        }
        else
        {
            A=L3;
            C=L2;
        }
    }
    else if(L2<L1 && L2>L3 || L2>L1 && L2<L3)
    {
        B=L2;
        if(L1>L3)
        {
            A=L1;
            C=L3;
        }
        else
        {
            A=L3;
            C=L1;
        }
    }
    else
    {
        B=L3;
        if(L1>L2)
        {
            A=L1;
            C=L2;
        }
        else
        {
            A=L2;
            C=L1;
        }
    }

    printf("\n\nOrdem: %d, %d, %d\n\n", A, B, C);


    if ((A*A)>(B*B)+(C*C))
    {
        printf("Triangulo obtusangulo");
    }
    else if ((A*A)<(B*B)+(C*C))
    {
        printf("Triangulo acutangulo");
    }
    else
    {
        printf("Nao Forma tringulo\n");
        printf("Ordem decrescente: %d, %d, %d", C, B, A);
    }


    if ((A==B)&&(A!=C) || (A==C)&&(A!=B) || (B==C)&&(C!=A))
    {
        printf("\ntriangulo isoceles");
    }
    else if ((A==B) && (C==B))
    {
        printf("\ntriangulo equilatero");
    }
    else if ((A*A)==(B*B)+(C*C))
    {
        printf("\ntriangulo retangulo");
    }

    return 0;
}
