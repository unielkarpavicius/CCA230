#include<stdio.h>
#include <stdlib.h>

typedef struct Celula{
    int valor;
    struct Celula *proximo;
    struct Celula *anterior;
}Celula;

typedef struct Fila{
    int qtde;
    struct Celula *head;
    struct Celula *tail;
}Fila;

Fila *inicializa(){
    Fila *fila = malloc(sizeof(Fila));
    fila->qtde = 0;
    fila->head = NULL;
    fila->tail = NULL;
    
    return fila;
}

void inserir(Fila *fila, int valor){
    Celula *nova = (Celula*)malloc(sizeof(Celula)); // Celula *nova = cria_celular(valor)

    nova->valor = valor;
    nova->proximo = NULL; 
    nova->anterior = NULL; //tudo pra cima pode virar uma função cria_celula(int valor)

    if (fila->qtde == 0){
        fila->head = nova;
    } else {
        fila->tail->proximo = nova;
        nova->anterior = fila->tail; 
    }
    fila->tail = nova;
    fila->qtde++;
}

int remover(Fila *fila){
    int valor;
    Celula *aux;

    if(fila->qtde == 0){
        return -1;
    }
    if (fila->qtde == 1){
        valor = fila->head->valor;
        aux = fila->head;
        fila->head = NULL;
        fila->tail = NULL;
    } else {
        valor = fila->head->valor;
        aux = fila->head;
        fila->head->proximo == NULL;
        fila->head = fila->head->proximo;
    }

    fila->qtde--;
    free(aux);
    return valor;
}

void imprimir(Fila *fila){
    Celula *atual = fila->head;
    printf("HEAD -> ");
    while (atual != NULL){
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf(" <- TAIL \n");
}

int main(){
    Fila *fila = inicializa();
    inserir(fila, 12);
    imprimir(fila);
    inserir(fila, 8);
    imprimir(fila);
    inserir(fila, 15);
    imprimir(fila);
    remover(fila);
    imprimir(fila);
    remover(fila);
    imprimir(fila);
    remover(fila);
    imprimir(fila);

    return 1;
}