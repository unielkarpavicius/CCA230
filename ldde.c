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

void remover(){
    return;
}

void imprimir(Lista *ldde){
    Celula *atual = ldde->primeira;

    printf("[");
    while(atual != NULL){
        printf(" %d ", atual->valor);
        atual = atual->proximo;
    }
    printf("] - %d \n", ldde->qtde);

}

void imprmir_reverso(){
    return;
}

void buscar(){
    return;
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
    
    return 0;
}