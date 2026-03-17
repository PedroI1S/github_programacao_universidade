#include <stdio.h>
#include <stdlib.h>

typedef struct NodeVP NodeVP;

struct NodeVP {
    int key;
    int color;
    NodeVP *father;
    NodeVP *left;
    NodeVP *right;
};

NodeVP* criar_AVP(int key) {
    NodeVP* tree = (NodeVP*) malloc(sizeof(NodeVP));
    tree->key = key;
    tree->color = 0;
    tree->left = NULL;
    tree->right = NULL;
    tree->father = NULL;
    return tree;
}

NodeVP* pesquisar(NodeVP *tree, int key) {
    if (tree != NULL) {
        if (key == tree->key)
            return tree;
        else if (key < tree->key)
            return pesquisar(tree->left, key);
        else
            return pesquisar(tree->right, key);
    }
    return NULL;
}

NodeVP* obter_avo(NodeVP *no) {
    if ((no != NULL) && (no->father != NULL)) {
        return no->father->father;
    }
    return NULL;
}

NodeVP* obter_tio(NodeVP *no) {
    NodeVP* avo = obter_avo(no);
    NodeVP* aux = NULL;
    if (avo != NULL) {
        if (avo->left == no->father) {
            aux = avo->right;
        } else
            aux = avo->left;
    }
    return aux;
}

static NodeVP* rotacionar_dir(NodeVP *x) {
    NodeVP *p = x->father;
    NodeVP *a = p->father;
    p->father = a->father;
    if (a->father != NULL) {
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

static NodeVP* rotacionar_esq(NodeVP *x) {
    NodeVP *p = x->father;
    NodeVP * a = p->father;
    p->father = a->father;
    if (a->father != NULL) {
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

static NodeVP* rotacionar_dir_esq(NodeVP *x) {
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

static NodeVP* rotacionar_esq_dir(NodeVP *x) {
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

static NodeVP* balancear(NodeVP *x) {
    NodeVP *pai, *tio;
    if (x->father == NULL) {
        x->color = 1;
    } else {
        pai = x->father;
        if (pai->color == 0) {
            tio = obter_tio(x);
            if ((tio != NULL) && (tio->color == 0)) {
                pai->color = tio->color = 1;
                x = obter_avo(x);
                if (x->father != NULL)
                    x->color = 0;
            } else {
                if (pai->left == x) {
                    if (pai->father->left == pai)
                        x = rotacionar_dir(x);
                    else
                        x = rotacionar_dir_esq(x);
                } else {
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

NodeVP* inserirVP(NodeVP *tree, int key) {
    NodeVP *auxP, *auxF;
    if (tree == NULL) {
        tree = criar_AVP(key);
        tree->color = 1;
    } else {
        auxP = auxF = tree;
        while (auxF != NULL) {
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

NodeVP* encontrar_sucessor(NodeVP* node) {
    NodeVP* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

NodeVP* remover(NodeVP* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = remover(root->left, key);
    else if (key > root->key)
        root->right = remover(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
    NodeVP* temp = root->left ? root->left : root->right;
    if (temp == NULL) {
        if (root->father != NULL) {
            if (root->father->left == root)
                root->father->left = NULL;
            else
                root->father->right = NULL;
        }
        free(root);
        return NULL;
    } else {
        *root = *temp;
        free(temp);
    }
}

    }
    if (root == NULL)
        return root;
    return balancear(root);
}

void imprimir_arvore(NodeVP* root) {
    if (root != NULL) {
        imprimir_arvore(root->left);
        printf("%d ", root->key);
        imprimir_arvore(root->right);
    }
}

int main() {
    NodeVP* tree = NULL;

    // Inserting elements into the tree
    tree = inserirVP(tree, 7);
    tree = inserirVP(tree, 3);
    tree = inserirVP(tree, 18);
    tree = inserirVP(tree, 10);
    tree = inserirVP(tree, 22);
    tree = inserirVP(tree, 8);
    tree = inserirVP(tree, 11);
    tree = inserirVP(tree, 26);
    tree = inserirVP(tree, 2);
    tree = inserirVP(tree, 6);

    printf("Tree before deletion: ");
    imprimir_arvore(tree);
    printf("\n");

    // Deleting a node
    tree = remover(tree, 10);

    printf("Tree after deletion: ");
    imprimir_arvore(tree);
    printf("\n");

    return 0;
}
