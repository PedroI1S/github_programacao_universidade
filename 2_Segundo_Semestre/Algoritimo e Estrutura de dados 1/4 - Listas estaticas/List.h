#define MAX_SIZE 100

typedef struct{
    int item[MAX_SIZE];
    int qtd;
}list;

list* create();

int empty(list *l);

int full(list *l);

int insert(list *l, int key);

int buscar(list *l, int key);

int remover(list *l, int key);

int imprint(list *l);

int invert(list *l);