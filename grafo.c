#include<stdio.h>

#define V 6
#define E 12

int get_index(char x){
    return x - 97;
}

void inicia_arestas(int arestas [V] [V]){
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            arestas [i] [j] = 0;
        }
    }
}

void cria_arestas(int arestas [V] [V], int v, int u){
    arestas [v] [u] = 1;
}

void mostra_arestas(int arestas [V] [V]){
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            printf("%d ", arestas [i] [j]);
        }
        printf("\n");
    }
}

void mostra_adjacentes(int arestas [V] [V], char v){
    //implementar
}

void mostra_distancias(int arestas [V] [V], char v){
    //implementar
}

int main(){
    printf("grafos\n");
    int matriz [V] [V];
    inicia_arestas(matriz);

    cria_arestas(matriz, get_index('a'), get_index('b'));
    cria_arestas(matriz, get_index('b'), get_index('a'));
    cria_arestas(matriz, get_index('b'), get_index('c'));
    cria_arestas(matriz, get_index('c'), get_index('b'));
    cria_arestas(matriz, get_index('b'), get_index('f'));
    cria_arestas(matriz, get_index('f'), get_index('b'));
    cria_arestas(matriz, get_index('e'), get_index('f'));
    cria_arestas(matriz, get_index('f'), get_index('e'));
    cria_arestas(matriz, get_index('a'), get_index('e'));
    cria_arestas(matriz, get_index('e'), get_index('a'));
    cria_arestas(matriz, get_index('a'), get_index('d'));
    cria_arestas(matriz, get_index('d'), get_index('a'));

    mostra_arestas(matriz);

    return 0;
}