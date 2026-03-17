#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


typedef struct NodeVP NodeVP;

struct NodeVP{
    int key;
    int color;
    NodeVP *father;
    NodeVP *left;
    NodeVP *right;
};

typedef struct{
    unsigned int tam;
    NodeVP **buckets;
} HashT;

NodeVP* criar_AVP(int key){
    NodeVP* tree = (NodeVP*) malloc(sizeof(NodeVP));
    tree->key = key;
    tree->color = 0;
    tree->left = NULL;
    tree->right = NULL;
    tree->father = NULL;

    return tree;
}

HashT *criar(unsigned int tam){
    HashT *t = (HashT*) malloc(sizeof(HashT));
    int i;

    t->tam = tam;
    t->buckets = (NodeVP**) malloc(tam * sizeof(NodeVP*));

    for (i = 0; i < tam; i++)
        t->buckets[i] = NULL;

    return t;
}

NodeVP* pesquisar(NodeVP *tree, int key){
    if (tree != NULL){
        if (key == tree->key)
            return tree;
        else if (key < tree->key)
            return pesquisar(tree->left, key);
        else
            return pesquisar(tree->right, key);
    }

    return NULL;
}

static NodeVP* obter_avo(NodeVP *no){
    if ((no != NULL) && (no->father != NULL)){
        return no->father->father;
    }

    return NULL;
}

static NodeVP* obter_tio(NodeVP *no){
    NodeVP* avo = obter_avo(no);
    NodeVP* aux = NULL;
    

    if (avo != NULL){
        if (avo->left == no->father){
            aux = avo->right;
        }else
            aux = avo->left;
    }

    return aux;
}

static NodeVP* rotacionar_dir(NodeVP *x){
    NodeVP *p = x->father;
    NodeVP *a = p->father;
    
    p->father = a->father;
    
    if (a->father != NULL){
        if (a->father->left == a)
            a->father->left = p;
        else
            a->father->right = p;
    }
    
    a->father = p;
    a->left = p->right;
    p->right = a;
    
    x = p;
    
    return x;
}

static NodeVP* rotacionar_esq(NodeVP *x){
    NodeVP *p = x->father;
    NodeVP * a = p->father;
    
    p->father = a->father;
    
    if (a->father != NULL){
        if (a->father->right == a)
            a->father->right = p;
        else
            a->father->left = p;
    }
    
    a->father = p;
    a->right = p->left;
    p->left = a;

    x = p;
    
    return x;
}

static NodeVP* rotacionar_dir_esq(NodeVP *x){
    NodeVP *p = x->father;
    NodeVP *a = p->father;
    
    x->father = a;
    a->left = x;
    p->left = x->right;
    x->right = p;
    p->father = x;
    
    x = rotacionar_esq(p);

    return x;
}

static NodeVP* rotacionar_esq_dir(NodeVP *x){
    NodeVP *p = x->father;
    NodeVP * a = p->father;
    
    x->father = a;
    a->left = x;
    p->father = x;
    p->right = x->left;
    x->left = p;
    
    x = rotacionar_dir(p);

    return x;
}

static NodeVP* balancear(NodeVP *x){
    NodeVP *pai, *tio;

    if (x->father == NULL){
        x->color = 1;
    }else{
        pai = x->father;

        if (pai->color == 0){
            tio = obter_tio(x);

            if ((tio != NULL) && (tio->color == 0)){
                pai->color = tio->color = 1;
                x = obter_avo(x);
        
            if (x->father != NULL)
                x->color = 0;
            }else{
                if (pai->left == x){
                    if (pai->father->left == pai)
                        x = rotacionar_dir(x);
                    else
                        x = rotacionar_dir_esq(x);
                }else{
                    if (pai->father->right == pai)
                        x = rotacionar_esq(x);
                    else
                        x = rotacionar_esq_dir(x);
                }

                x->color = 1;
                
                if (x->left != NULL)
                    x->left->color = 0;
                
                if (x->right != NULL)
                    x->right->color = 0;
            }
        }
    }
    
    return x;
}

NodeVP* inserirVP(NodeVP *tree, int key){
    NodeVP *auxP, *auxF;

    if (tree == NULL){
        tree = criar_AVP(key);
        tree->color = 1;
    }else{
        auxP = auxF = tree;

        while (auxF != NULL){
            auxP = auxF;

            if (key < auxF->key)
                auxF = auxF->left;
            else
                auxF = auxF->right;
        }

        auxF = criar_AVP(key);
        auxF->father = auxP;

        if (auxF->key < auxP->key)
            auxP->left = auxF;
        else
            auxP->right = auxF;

        while ((auxF->father != NULL) && (auxF->color == 0) && (auxF->father->color == 0))
            auxF = balancear(auxF);
        
        while (auxF->father != NULL)
            auxF = auxF->father;

        tree = auxF;
    }
    
    return tree;
}

void imprimirPrefix(NodeVP* tree, int aux){
    if (tree != NULL){
        printf("%i ", tree->key);
        if(tree->left != NULL)
            if(aux != tree->left->key)
                imprimirPrefix(tree->left, aux);
        
        if(tree->right != NULL)
            if(aux != tree->right->key)
                imprimirPrefix(tree->right, aux);
    }
}

static int hashingF(int k, int B, float c){
    float f = (float) k * c;
    f -= (int)f;
    return (int) (f * (float) B);
}

int inserir(int key, HashT *t, float c){
    int x;

    if ((t != NULL) && (key > 0)){
        x = hashingF(key, t->tam, c);
        t->buckets[x] = inserirVP(t->buckets[x], key);
    }

    return 0;
}

void imprimir(HashT *t){
    int i;
    if (t != NULL){
        for (i = 0; i < t->tam; i++) {
            if (t->buckets[i] != NULL) {
                printf("%d: ", i);
                imprimirPrefix(t->buckets[i], t->buckets[i]->key);
                putchar('\n');
            }else
                printf("%d: -\n", i);
        }
    }
}

int liberar(HashT *t){
    if (t != NULL){
        free(t->buckets);
        free(t);
        return 1;
    }

    return 0;
}

int main() {
    float c;
    int n, tamanho, key;
    
    scanf("%f %d", &c, &tamanho);
    scanf("%d", &n);
    
    HashT *t = criar(tamanho);
    
    for(int i = 0; i < n; i++){
        scanf("%d", &key);
        inserir(key, t, c);
    }
    
    imprimir(t);
    liberar(t);
    
    return 0;
}
