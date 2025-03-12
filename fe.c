#include<stdio.h>

#define LEN 5

typedef struct {
    char data[LEN];
    int head;
    int tail;
    int qtde;
}Fila;

void inicializa(Fila *fila){
    fila->qtde = 0;
    fila->head = 0;
    fila->tail = 0;
}

int isFull(Fila *fila){
    if (((fila->tail + 1)%LEN) == (fila->head)){
        return 1;
    } else {
        return 0;
    }
}

int isEmpty(Fila *fila){
    if ((fila->tail) == (fila->head)){
        return 1;
    } else {
        return 0;
    }
}

void inserir(Fila *fila, char valor){
    if(isFull(fila)){
        printf("Fila cheia\n");
        return;
    }
    fila->data[fila->tail] = valor;
    fila->tail = ((fila->tail + 1) % LEN);
    fila->qtde++;
}

char remover(Fila *fila){
    if(isEmpty(fila)){
        printf("Fila vazia\n");
        return -1;
    }
    char valor = fila->data[fila->head];
    fila->head = ((fila->head + 1) % LEN);
    fila->qtde--;
    return valor;
}

void imprimir(Fila *fila){
    printf("[ ");
    int i;
    for(i = fila->head; i < fila->tail; i++){
        printf("%c ", fila->data[i]);
    }
    printf("]\n");
}

int main(){
    printf("Fila estática\n");

    Fila fila;
    inicializa(&fila);
    inserir(&fila, 'a');
    imprimir(&fila);
    inserir(&fila, 'b');
    imprimir(&fila);
    char valor = remover(&fila);
    printf("%c \n", valor);
    imprimir(&fila);

    return 0;
}