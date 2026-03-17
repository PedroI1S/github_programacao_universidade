typedef struct PilhaE PilhaE;
typedef struct CellP CellP;

PilhaE* criar_pilha;

int pilha_vazia(PilhaE *p);

void empilhar(int key, PilhaE *p);

void desempilhar(PilhaE *p);

int valor_topo(PilhaE *p);