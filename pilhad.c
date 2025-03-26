#include<stdio.h>
#include <stdlib.h>

typedef struct Celula{
    char valor;
    struct Celula *proximo;
    struct Celula *anterior;
}Celula;

typedef struct Pilha{ //stack
    int qtde;
    struct Celula *topo;
}Pilha;

Pilha *inicializa(){
    Pilha *pilha = malloc(sizeof(pilha));
    pilha->qtde = 0;
    pilha->topo = NULL;
    
    return pilha;
}

Celula *inicializa_celula(char valor){
    Celula *celula = malloc(sizeof(Celula));
    celula->proximo = NULL;
    celula->anterior = NULL;
    celula->valor = valor;

    return celula;
}

void inserir(Pilha *pilha, char valor){
    Celula *nova = inicializa_celula(valor);

    if (pilha->qtde != 0){ //tem elemento na pilha
        nova->anterior = pilha->topo;
        pilha->topo->proximo = nova;
    }
    pilha->topo = nova;
    pilha->qtde++;
}

char remover(Pilha *pilha){
    if (pilha->qtde == 0){
        return -1;
    }

    char valor = pilha->topo->valor;
    Celula *aux = pilha->topo;

    if (pilha->qtde == 1){
        pilha->topo = NULL;
    } else {
        pilha->topo = pilha->topo->anterior;
        pilha->topo->proximo == NULL;
    }

    pilha->qtde--;
    free(aux);
    return valor;
}

void imprimir(Pilha *pilha){
    Celula *atual = pilha->topo;
    printf("[ ");
    while (atual != NULL){
        printf("%c ", atual->valor);
        atual = atual->anterior;
    }
    printf("] \n");
}


int main(){
    printf("Pilha dinâmica\n");

    Pilha *pilha = inicializa();
    inserir(pilha, 'a');
    imprimir(pilha);
    inserir(pilha, 'n');
    imprimir(pilha);
    inserir(pilha, 'a');
    imprimir(pilha);
    inserir(pilha, 'u');
    imprimir(pilha);
    inserir(pilha, 'l');
    imprimir(pilha);
    remover(pilha);
    imprimir(pilha);
    remover(pilha);
    imprimir(pilha);
    remover(pilha);
    imprimir(pilha);
    remover(pilha);
    imprimir(pilha);
    remover(pilha);
    imprimir(pilha);


    return 0;
}