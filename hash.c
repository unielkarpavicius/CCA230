#include <stdio.h>
#include <stdlib.h>

#define LEN 10

typedef struct Celula{
    int valor;
    struct Celula* proxima;
} Celula;

typedef struct Lista{
    int qtde;
    Celula* inicio;
} Lista;

typedef struct Hash{
    Lista* table[LEN];
}Hash;

Hash* inicializa(){
    Hash* hash = malloc(sizeof(Hash));
    for (int i = 0; i < LEN; i++){
        Lista* lista = malloc(sizeof(lista));
        lista->inicio = NULL;
        lista->qtde = 0;
        hash->table[i] = lista;
    }
    
    return hash;
}

void inserir(Hash* hash, int valor){
    Celula* nova = malloc(sizeof(Celula));
    nova->valor = valor;
    nova->proxima = NULL;

    int pos = valor % LEN;
    if(hash->table[pos]->inicio == NULL){
        hash->table[pos]->inicio = nova;
    } else {
        nova->proxima = hash->table[pos]->inicio;
        hash->table[pos]->inicio = nova;
    }

    hash->table[pos]->qtde++;
}

int buscar(Hash* hash, int valor){
    int pos = valor % LEN;

    Celula* anterior = NULL;
    Celula* atual = hash->table[pos]->inicio;
    while(atual != NULL && atual->valor != valor){
        anterior = atual;
        atual = atual->proxima;
    }
    if (atual != NULL){
        return valor;
    }
    return -1;
}

int remover(Hash* hash, int valor){

}

void imprimir(Hash* hash){
    for(int i =0; i < LEN; i++){
        Celula* atual = hash->table[i]->inicio;
        while(atual != NULL){
            printf("%d ", atual->valor);
            atual = atual->proxima;
        }

        printf("\n");
    }

}

int main(){
    printf("tabela hash\n");
    Hash* hash = inicializa();
    inserir(hash, 3);
    inserir(hash, 5);
    inserir(hash, 55);
    inserir(hash, 45);
    imprimir(hash);

    int x = buscar(hash, 5);
    if (x >= 0){
        printf("Valor encotrado: %d\n", x);
    } else {
        printf("Valor não encotrado\n");
    }

    return 0;
}