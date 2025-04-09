#include<stdio.h>
#include <stdlib.h>

#define LEN 10

typedef struct{
    int valores[LEN];
    int qtde;
}Heap;

void peneirar(Heap *h, int pai){
    int fe = filho_esquerdo(pai);
    int fd = filho_direito(pai);
    int maior = pai;

    if (fe <= h->qtde && h->valores[fe] <= h->valores[pai]){
        maior = fe;  
    }
    if (fd <= h->qtde && h->valores[fd] <= h->valores[maior]) {
        maior = fd; 
    }

    if (maior != pai){
        int aux = h->valores[pai];
        h->valores[pai] = h->valores[maior];
        h->valores[maior] = aux;
        peneirar(h, maior);
    }

    return;
}

void construir(Heap *h){

}

int filho_esquerda(int pai){
    return (2*pai + 1);
}

int filho_direita(int pai){
    return (2*pai + 2);
}

int ultimo_pai(Heap *h){
    return ((h->qtde/2) - 1);
}

int pai(int filho){
    return ((filho - 1)/2);
}

void imprimir(Heap *h){

}

void inserir(Heap *h, int valor){

    h->qtde++;

}

void remover(Heap *h){

    h->qtde--;

}

int main() {

}