#include <stdio.h>
#include <stdlib.h>

#define LEN 10

typedef struct {
    int valores[LEN];
    int qtde;
} Heap;

int filho_esquerda(int pai) {
    return (2 * pai + 1);
}

int filho_direita(int pai) {
    return (2 * pai + 2);
}

int pai(int filho) {
    return ((filho - 1) / 2);
}

int ultimo_pai(Heap *h) {
    return ((h->qtde / 2) - 1);
}

// Reorganiza para manter max-heap (heapify down)
void peneirar(Heap *h, int pai) {
    int fe = filho_esquerda(pai);
    int fd = filho_direita(pai);
    int maior = pai;

    if (fe < h->qtde && h->valores[fe] > h->valores[maior]) {
        maior = fe;
    }
    if (fd < h->qtde && h->valores[fd] > h->valores[maior]) {
        maior = fd;
    }

    if (maior != pai) {
        int aux = h->valores[pai];
        h->valores[pai] = h->valores[maior];
        h->valores[maior] = aux;
        peneirar(h, maior);
    }
}

// Constroi heap a partir do vetor atual
void construir(Heap *h) {
    for (int i = ultimo_pai(h); i >= 0; i--) {
        peneirar(h, i);
    }
}

void inserir(Heap *h, int valor) {
    if (h->qtde >= LEN) {
        printf("Heap cheia!\n");
        return;
    }

    h->valores[h->qtde] = valor;
    h->qtde++;

    construir(h);  // <<<<< Aqui está o uso da função construir
}

void remover(Heap *h) {
    if (h->qtde == 0) {
        printf("Heap vazia!\n");
        return;
    }

    int removido = h->valores[0];
    h->valores[0] = h->valores[h->qtde - 1];
    h->qtde--;

    construir(h); // <<<<< Também usa construir após remover

    printf("Removido: %d\n", removido);
}

void imprimir(Heap *h) {
    printf("Heap: ");
    for (int i = 0; i < h->qtde; i++) {
        printf("%d ", h->valores[i]);
    }
    printf("\n");
}

int main() {
    Heap h;
    h.qtde = 0;

    inserir(&h, 20);
    inserir(&h, 15);
    inserir(&h, 30);
    inserir(&h, 10);
    inserir(&h, 5);

    imprimir(&h); // Deve mostrar o maior no topo (30)

    remover(&h);  // Remove 30
    imprimir(&h);

    inserir(&h, 40); // Novo maior
    imprimir(&h);

    return 0;
}