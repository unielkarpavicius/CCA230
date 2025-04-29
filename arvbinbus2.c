#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* esq;
    struct No* dir;
    struct No* pai;
} No;

typedef struct {
    No* raiz;
    int qtde;
} Arvore;

No* cria_no(int valor) {
    No* vertice = malloc(sizeof(No));
    vertice->esq = NULL;
    vertice->dir = NULL;
    vertice->pai = NULL;
    vertice->valor = valor;

    return vertice;
}

Arvore* cria_arvore() {
    Arvore* arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    arvore->qtde = 0;

    return arvore;
}

No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        return cria_no(valor);
    }

    if (valor <= raiz->valor) {
        No* filho = inserir(raiz->esq, valor);
        raiz->esq = filho;
        if (filho != NULL) {
            filho->pai = raiz;
        }
    } else {
        No* filho = inserir(raiz->dir, valor);
        raiz->dir = filho;
        if (filho != NULL) {
            filho->pai = raiz;
        }
    }

    return raiz;
}

// Função para buscar um valor na árvore
No* buscar(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }
    if (valor < raiz->valor) {
        return buscar(raiz->esq, valor);
    } else {
        return buscar(raiz->dir, valor);
    }
}

// Função auxiliar para encontrar o maior elemento da subárvore esquerda
No* encontrar_maximo(No* raiz) {
    while (raiz->dir != NULL) {
        raiz = raiz->dir;
    }
    return raiz;
}

// Função para remover um valor da árvore
No* remover(No* raiz, int valor) {
    if (raiz == NULL) {
        return NULL;
    }

    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        // Encontrou o nó a ser removido
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }
        else if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            temp->pai = raiz->pai;
            free(raiz);
            return temp;
        }
        else if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            temp->pai = raiz->pai;
            free(raiz);
            return temp;
        }
        else {
            No* max_esq = encontrar_maximo(raiz->esq);
            raiz->valor = max_esq->valor;
            raiz->esq = remover(raiz->esq, max_esq->valor);
        }
    }

    return raiz;
}

void in_order(No* raiz) {
    if (raiz != NULL) {
        in_order(raiz->esq);
        printf("%d ", raiz->valor);
        in_order(raiz->dir);
    }
}

void pre_order(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        pre_order(raiz->esq);
        pre_order(raiz->dir);
    }
}

void pos_order(No* raiz) {
    if (raiz != NULL) {
        pos_order(raiz->esq);
        pos_order(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

int main() {
    printf("Árvore Binária de Busca\n");

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

    printf("In-order: ");
    in_order(tree->raiz);
    printf("\n");

    printf("Pre-order: ");
    pre_order(tree->raiz);
    printf("\n");

    printf("Pos-order: ");
    pos_order(tree->raiz);
    printf("\n");

    // Testando busca
    int valor_busca = 10;
    No* encontrado = buscar(tree->raiz, valor_busca);
    if (encontrado) {
        printf("Valor %d encontrado na árvore.\n", valor_busca);
    } else {
        printf("Valor %d não encontrado.\n", valor_busca);
    }

    // Testando remover
    tree->raiz = remover(tree->raiz, 8);

    printf("In-order após remoção: ");
    in_order(tree->raiz);
    printf("\n");

    return 0;
}
