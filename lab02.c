#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
    int valor;
    struct Celula *proximo;
} Celula;

typedef struct Lista {
    int qtde;
    Celula *primeiro;
} Lista;

Lista *inicializa_lista() {
    Lista *l = (Lista *)malloc(sizeof(Lista));
    l->primeiro = NULL;
    l->qtde = 0;
    return l;
}

void inserir(Lista *l, int valor) {
    Celula *novo = (Celula *)malloc(sizeof(Celula));
    novo->valor = valor;
    novo->proximo = NULL;

    Celula *atual = l->primeiro;
    Celula *anterior = NULL;

    while (atual != NULL && atual->valor < valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    novo->proximo = atual;

    if (anterior == NULL) {
        l->primeiro = novo;
    } else {
        anterior->proximo = novo;
    }

    l->qtde++;
}

void remover(Lista *l, int valor) {
    if (l == NULL || l->primeiro == NULL) { 
        return;
    }
    Celula *anterior = NULL;
    Celula *atual = l->primeiro;
    while (atual != NULL && atual->valor < valor) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL || atual->valor != valor) {
        return;
    }
    if (anterior == NULL) {
        l->primeiro = atual->proximo; 
    } else {
        anterior->proximo = atual->proximo; 
    }
    free(atual); 
    l->qtde--; 
}

void imprimir(const Lista *l) {
    Celula *atual = l->primeiro;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

int main(void) {
    Lista *l = inicializa_lista();

    inserir(l, 10);
    imprimir(l);
    
    inserir(l, 20);
    inserir(l, 30);
    imprimir(l);
   
    inserir(l, 5);
    imprimir(l);

    inserir(l, 15);
    imprimir(l);
    
    remover(l, 5);
    imprimir(l);

    remover(l, 30);
    imprimir(l);

    remover(l, 15);
    imprimir(l);

    remover(l, 50);
    imprimir(l);

    remover(l, 10);
    remover(l, 20);
    imprimir(l);

    remover(l, 10);
    imprimir(l);

    return 0;
}