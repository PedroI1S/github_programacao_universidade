#include<math.h>
#include<stdio.h>

int main (void)
{
    float n, i=1;
    int j=1;

    printf("Informe o valor de n: ");
    scanf("%f", &n);

    while(j<=n)
    {
        if(sqrt(i)==j)
        {
            printf("Raiz quadrada de %-4.0f ==> %d\n", i, j);
            j++;
        }
        i++;
    }
}
