#include <stdio.h>
#include <stdlib.h>

typedef struct Lista{
    int qtde;
    struct Celula *primeira;
}Lista;

typedef struct Celula{
    int valor;
    struct Celula *proximo;
}Celula;

Lista *inicializa(){
    Lista *lde = malloc(sizeof(Lista));
    lde->qtde = 0;
    lde->primeira = NULL;
    
    return lde;
}

void inserir(Lista *lde, int valor){
    Celula *novo = malloc(sizeof(Celula));
    novo->valor = valor;
    novo->proximo = NULL;

    Celula *anterior = NULL;
    Celula *atual = lde->primeira;

    while(atual != NULL && atual->valor < valor){
        anterior = atual;
        atual = atual->proximo;
    } 
    
    
    if(anterior == NULL){
        novo->proximo = lde->primeira;
        lde->primeira = novo;
    } else {
        anterior->proximo = novo;
        novo->proximo = atual;
    }

    lde->qtde++;

}

void remover(Lista *lde, int valor){
    if (lde == NULL || lde->primeira == NULL) { // Verifica se a lista está vazia
        printf("Lista vazia, impossível remover.\n");
        return;
    }
    Celula *anterior = NULL;
    Celula *atual = lde->primeira;
    // Busca o nó a ser removido
    while (atual != NULL && atual->valor < valor) {                                                             
        anterior = atual;                                    
        atual = atual->proximo;
    }
    // Se não encontrou o valor na lista
    if (atual == NULL || atual->valor != valor) {
        printf("Valor %d não encontrado na lista.\n", valor);
        return;
    }
    // Se o nó a ser removido é o primeiro da lista
    if (anterior == NULL) {
        lde->primeira = atual->proximo;                                                             
    } else {
        anterior->proximo = atual->proximo; 
    }
    free(atual); // Libera a memória do nó removido
    lde->qtde--; // Atualiza a quantidade de elementos
}

void buscar(Lista *lde, int valor){
    if (lde == NULL || lde->primeira == NULL) { // Verifica se a lista está vazia
        printf("A lista está vazia.\n");
        return;
    }
    Celula *atual = lde->primeira;
    int posicao = 0;
    while (atual != NULL) {
        if (atual->valor == valor) { // Se encontrou o valor
            printf("O número %d está na posição %d.\n", valor, posicao);
            return;
        }
        atual = atual->proximo;
        posicao++;
    }
    printf("O número %d não está na lista.\n", valor); // Se o valor não foi encontrado
}

void imprimir(Lista *lde){
    Celula *atual = lde->primeira;

    printf("[");
    while(atual != NULL){
        printf(" %d ", atual->valor);
        atual = atual->proximo;
    }
    printf("] - %d \n", lde->qtde);

}

int main(){
    Lista *lde = inicializa();
    inserir(lde, 56);
    imprimir(lde);
    inserir(lde, 50);
    imprimir(lde);
    inserir(lde, 30);
    imprimir(lde);
    inserir(lde, 52);
    imprimir(lde);
    inserir(lde, 70);
    imprimir(lde);
    remover(lde, 52);
    imprimir(lde);
    buscar(lde, 50);
    buscar(lde, 70);
    buscar(lde, 52);

    return 0;
}