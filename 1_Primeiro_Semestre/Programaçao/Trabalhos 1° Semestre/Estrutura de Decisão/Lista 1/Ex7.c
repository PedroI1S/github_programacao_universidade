#include<stdio.h>

int main (void)
{
    char ch;

    printf("insira um caractere: \n");
    scanf("%c", &ch);

    if ((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
    {
            switch (ch)
        {
        case 'a':
            printf("vogal");
            break;
        case 'e':
            printf("vogal");
            break;
        case 'i':
            printf("vogal");
            break;
        case 'o':
            printf("vogal");
            break;
        case 'u':
            printf("vogal");
            break;
        case 'A':
            printf("vogal");
            break;
        case 'E':
            printf("vogal");
            break;
        case 'I':
            printf("vogal");
            break;
        case 'O':
            printf("vogal");
            break;
        case 'U':
            printf("vogal");
            break;
        default:
            printf("consoante");
            break;
        }
    }
    else
    {
        printf("Nao pertence ao alfabeto\n");
    }
    return 0;
}
/*
#include<stdio.h>
#include<ctype.h>

int main (void)
{
    char ch;

    printf("insira um caractere: \n");
    scanf("%c", &ch);

    if ((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
    {
            switch (tolower(ch))
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            printf("vogal");
            break;
        default:
            printf("consoante");
            break;
        }
    }
    else
    {
        printf("Nao pertence ao alfabeto\n");
    }
    return 0;
}
*/
