#include <stdio.h>

#define V 6

int get_index(char x){
    return x - 97; // 'a' = 0, 'b' = 1, ...
}

void inicia_arestas(int arestas[V][V]){
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            arestas[i][j] = 0;
        }
    }
}

void cria_arestas(int arestas[V][V], int v, int u){
    arestas[v][u] = 1;
}

void mostra_arestas(int arestas[V][V]){
    printf("Matriz de Adjacências:\n");
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            printf("%d ", arestas[i][j]);
        }
        printf("\n");
    }
}

void mostra_adjacentes(int arestas[V][V], char v){
    int idx = get_index(v);
    printf("Adjacências de %c:\n", v);
    for(int j = 0; j < V; j++){
        if(arestas[idx][j] == 1){
            printf("%c -> %c\n", v, j + 97);
        }
    }
}

void mostra_distancias(int arestas[V][V], char origem){
    int fila[V], visitado[V], distancia[V];
    int inicio, fim;

    int origem_idx = get_index(origem);
    for(int i = 0; i < V; i++) {
        fila[i] = 0;
        visitado[i] = 0;
        distancia[i] = -1;
    }

    inicio = 0;
    fim = 0;
    fila[fim++] = origem_idx;
    visitado[origem_idx] = 1;
    distancia[origem_idx] = 0;

    while(inicio < fim){
        int atual = fila[inicio++];
        for(int i = 0; i < V; i++){
            if(arestas[atual][i] == 1 && !visitado[i]){
                fila[fim++] = i;
                visitado[i] = 1;
                distancia[i] = distancia[atual] + 1;
            }
        }
    }

    for(int i = 0; i < V; i++){
        printf("%d ", distancia[i]);
    }
    printf("\n");
}

void mostra_todas_distancias(int arestas[V][V]){
    printf("Matriz de Distâncias:\n");
    for(char v = 'a'; v < 'a' + V; v++){
        mostra_distancias(arestas, v);
    }
}

int main(){
    printf("Grafos - Laboratório\n");
    int matriz[V][V];
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
    printf("\n");

    printf("Adjacências:\n");
    for(char v = 'a'; v < 'a' + V; v++){
        mostra_adjacentes(matriz, v);
    }
    printf("\n");

    mostra_todas_distancias(matriz);

    return 0;
}
