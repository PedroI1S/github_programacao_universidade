#include<stdio.h>
#include<locale.h>

int main(void)
{
    int i=0, num;

    printf("Quantos numeros ímpares quer mostrar? \nR:");
    scanf("%d", &num);

    for(i=1; i<=(num*2); i++)
    {
        if(i%2==0)
        {

        }
        else
        {
            printf("%d \n",i);
        }
    }
    return 0;
}
