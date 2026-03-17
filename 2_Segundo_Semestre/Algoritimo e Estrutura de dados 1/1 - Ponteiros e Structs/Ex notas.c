#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/* RPG- Structs
typedef struct{
    char nome[50];
    int eng, def, forc;
}cartilha;

int main (){

    int partidas, i=0, dmg;
    cartilha p1;
    cartilha p2;

    scanf("%s %d %d %d", &p1.nome, &p1.eng, &p1.def, &p1.forc);
    scanf("%s %d %d %d", &p2.nome, &p2.eng, &p2.def, &p2.forc);
    scanf("%d", &partidas);

    for(i=0; i<partidas; i++){

        if(p1.forc>p2.def){

            dmg=0;
            dmg=p1.forc;
            dmg-=p2.def;
            p2.eng-=dmg;

        }

        if(p2.forc>p1.def){

            dmg=0;
            dmg=p2.forc;
            dmg-=p1.def;
            p1.eng-=dmg;

        }
    }

    if(p1.eng<0){
        p1.eng=0;
    }

    if(p2.eng<0){
        p2.eng=0;
    }


    printf("%s %d\n", p1.nome, p1.eng);
    printf("%s %d\n", p2.nome, p2.eng);
    if(p1.eng>p2.eng){
        printf("%s", p1.nome);
    }
    else if(p2.eng>p1.eng){
        printf("%s", p2.nome);
    }
    else{
        printf("empate");
    }

}
*/

typedef struct {
    char nome[255];
    int saquesTotal;
    int bloqueiosTotal;
    int ataquesTotal;
    int saquesSucesso;
    int bloqueiosSucesso;
    int ataquesSucesso;
}jogador;

void alocacao (jogador *a)
{
    scanf("%s", &a->nome);
    scanf("%d %d %d", &a->saquesTotal, &a->bloqueiosTotal, &a->ataquesTotal);
    scanf("%d %d %d", &a->saquesSucesso, &a->bloqueiosSucesso, &a->ataquesSucesso);

}

int main (void){
    int jogadores;
    float psaques=0, pbloqueios=0, pataques=0;

    scanf("%d", &jogadores);

    for(int i=0; i<jogadores; i++){
        jogador na;
        alocacao(&na);
        psaques+= (na.saquesTotal/na.saquesSucesso);
        pbloqueios+= (na.bloqueiosTotal/na.bloqueiosSucesso);
        pataques+= (na.ataquesTotal/na.ataquesSucesso);
    }
    psaques = psaques/jogadores;
    pbloqueios = pbloqueios/jogadores;
    pataques = pataques/jogadores;

    printf("Pontos de Saque: %.2f%% \nPontos de Bloqueio: %.2f%% \nPontos de Ataque: %.2f%%", 100*psaques, 100*pbloqueios, 100*pataques);
}



