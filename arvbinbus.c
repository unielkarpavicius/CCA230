#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No* esq;
    struct No* dir;
    struct No* pai;
}No;

typedef struct{
    No* raiz;
    int qtde;
}Arvore;

No* cria_no(int valor){
    No* vertice = malloc(sizeof(No));
    vertice->esq = NULL;
    vertice->dir = NULL;
    vertice->pai = NULL;
    vertice->valor = valor;

    return vertice;
}

Arvore* cria_arvore(){
    Arvore* arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    arvore->qtde = 0;

    return arvore;
}

No* inserir(No* raiz, int valor){
    if (raiz == NULL){
        return cria_no(valor);
    }
    if (valor <= raiz->valor){
        raiz->esq = inserir(raiz->esq, valor);
    } else if (valor > raiz->valor){
        raiz->dir = inserir(raiz->dir, valor);
    }

    return raiz;
}



void in_order(No* raiz){
    if(raiz != NULL){
        in_order(raiz->esq);
        printf("%d ", raiz->valor);
        in_order(raiz->dir);
    }
}

void pre_order(No* raiz){
    if(raiz != NULL){
        printf("%d ", raiz->valor);
        pre_order(raiz->esq);
        pre_order(raiz->dir);
    }
}

void pos_order(No* raiz){
    if(raiz != NULL){
        pos_order(raiz->esq);
        pos_order(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

int main(){
    printf("Arvore binária de busca\n");
    Arvore* tree = cria_arvore();
    tree->raiz = inserir(tree->raiz, 8);
    tree->raiz = inserir(tree->raiz, 5);
    tree->raiz = inserir(tree->raiz, 4);
    tree->raiz = inserir(tree->raiz, 2);
    tree->raiz = inserir(tree->raiz, 6);
    tree->raiz = inserir(tree->raiz, 15);
    tree->raiz = inserir(tree->raiz, 10);
    tree->raiz = inserir(tree->raiz, 9);
    tree->raiz = inserir(tree->raiz, 20);
    in_order(tree->raiz);
    printf("\n");
    pre_order(tree->raiz);
    printf("\n");
    pos_order(tree->raiz);
    printf("\n");
    
    return 0;
}