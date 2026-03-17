#include<stdio.h>
#include<locale.h>

int main (void)
{
    setlocale(LC_ALL, "Portuguese");
    int id, tb=0, te=0, tbcs=0, tbs=0, tes=0, tecs=0, mie=100, mib=100;
    char n, cs;
    float mebs=0, mebcs=0, mees=0, meecs=0;

    do
    {
        fflush(stdin);
        printf("Informe a idade: ");
        scanf("%d", &id);

        fflush(stdin);
        printf("Informe a nacionalidade (B - Brasileiro ou E - Estrangeiro): ");
        scanf("%c", &n);

        fflush(stdin);
        printf("Possui curso superior (S - Sim ou N - Não): ");
        scanf("%c", &cs);


        if(n=='b' || n=='B')
        {
            tb++;

            if(cs=='s'||'S')
            {
                tbcs++;

                if(id>=mie)
                {
                    mebcs +=id;
                }
            }
            else
            {
                tbs++;

                if(id>=mie)
                {
                    mebs += id;
                }
            }
        }
        else
        {
            te++;
            if(cs=='s'||'S')
            {
                tecs++;

                if(id>=mie)
                {
                    meecs += id;
                }
            }
            else
            {
                tes++;

                if(id>=mie)
                {
                    mie=id;
                }
                mees += id;
            }
        }



    }
    while(id!=0);

    printf("\n\nQuantidade de brasileiros: %d", tb);

    printf("\n\nIdade média de brasileiros sem curso superior: %d", mebs/tbs);
    printf("\nIdade média de brasileiros com curso superior: %d", mebcs/tbcs);
    printf("\nMenor idade de Brasileiros com curso superior: %d", mib);

    printf("\n\nQuantidade de Estrangeiros: %d", te);
    printf("\n\nIdade média de estrangeiros sem curso superior: %d", mees/tes);
    printf("\nIdade média de estrangeiros com curso superior: %d", meecs/tecs);
    printf("\nMenor idade de Estrangeiros com curso superior: %d", mie);



    return 0;
}
