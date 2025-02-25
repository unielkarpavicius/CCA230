#include <stdio.h>
#include <stdlib.h>

typedef struct Lista{
    int qtde;
    struct Celula *primeira;
}Lista;

typedef struct Celula{
    int valor;
    struct Celula *proximo;
    struct Celula *anterior;
}Celula;

Lista *inicializa(){
    Lista *ldde = malloc(sizeof(Lista));
    ldde->qtde = 0;
    ldde->primeira = NULL;
    
    return ldde;
}

void inserir(Lista *ldde, int valor){
    Celula *novo = malloc(sizeof(Celula));
    novo->valor = valor;
    novo->proximo = NULL;
    novo->anterior = NULL;

    Celula *anterior = NULL;
    Celula *atual = ldde->primeira;

    while(atual != NULL && atual->valor < valor){
        anterior = atual;
        atual = atual->proximo;
    } 
    //lista vazia
    if (atual == NULL && anterior == NULL){
        ldde->primeira = novo; 
    }
    //primeiro da lista
    else if (atual != NULL && anterior == NULL){
        ldde->primeira = novo; 
        novo->proximo = atual;
        atual->anterior = novo;
    }
    //ultimo da lista
    else if (atual == NULL && anterior != NULL){
        anterior->proximo = novo;
        novo->anterior = anterior;
    }
    // meio da lista
    else if (atual != NULL && anterior!= NULL){
        anterior->proximo = novo;
        novo->anterior = anterior;
        atual->anterior = novo;
        novo->proximo = atual;
    }
   
    ldde->qtde++;
}

void remover(Lista *ldde, int valor){
    if (ldde == NULL || ldde->primeira == NULL) { // Verifica se a lista está vazia
        printf("A lista está vazia.\n");
        return;
    }
    Celula *anterior = NULL;
    Celula *atual = ldde->primeira;
    // Busca o celula a ser removido
    while (atual != NULL && atual->valor < valor) {                                                             
        anterior = atual;                                    
        atual = atual->proximo;
    }
    // Se não encontrou o valor na lista
    if (atual == NULL || atual->valor != valor) {
        printf("Valor %d não encontrado na lista.\n", valor);
        return;
    }
    Celula *proximo = atual->proximo; // Obtém o próximo celula
    // Se for o primeiro celula da lista
    if (anterior == NULL) {
        ldde->primeira = proximo;
        proximo->anterior = NULL;
    }
    // Se for um celula no final
    else if (proximo == NULL) {
        anterior->proximo = NULL; // O anterior passa a ser o último
    } 
    //Remover do meio
    else {
        anterior->proximo = proximo;
        proximo->anterior = anterior;
    }

    free(atual); // Libera a memória
    ldde->qtde--;
}

void imprimir(Lista *ldde){
    if (ldde == NULL || ldde->primeira == NULL) { // Verifica se a lista está vazia
        printf("A lista está vazia.\n");
        return;
    }
    Celula *atual = ldde->primeira;

    printf("[");
    while(atual != NULL){
        printf(" %d ", atual->valor);
        atual = atual->proximo;
    }
    printf("] - %d \n", ldde->qtde);

}

void imprmir_reverso(Lista *ldde){
    if (ldde == NULL || ldde->primeira == NULL) { // Verifica se a lista está vazia
        printf("A lista está vazia.\n");
        return;
    }
    Celula *atual = ldde->primeira;
    // Percorre a lista até a última celula
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    printf("[");
    while (atual != NULL) {
        printf(" %d ", atual->valor);
        atual = atual->anterior; 
    }
    printf("] - %d \n", ldde->qtde);
}

void buscar(Lista *ldde, int valor){
    if (ldde == NULL || ldde->primeira == NULL) { // Verifica se a lista está vazia
        printf("A lista está vazia.\n");
        return;
    }
    Celula *atual = ldde->primeira;
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

int main(){

    printf("Lista Duplamente Encadeada\n");
    Lista *ldde = inicializa();

    inserir(ldde, 56);
    imprimir(ldde);
    inserir(ldde, 30);
    imprimir(ldde);
    inserir(ldde, 70);
    imprimir(ldde);
    inserir(ldde, 50);
    imprimir(ldde);

    //imprmir_reverso(ldde);

    buscar(ldde, 56);
    remover(ldde, 30);
    remover(ldde, 56);
    remover(ldde, 70);
    imprimir(ldde);
    
    return 0;
}