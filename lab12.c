#include <stdio.h>

#define V 8
#define E 20

int get_index(char x){
	return x - 114;
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
	for(int i = 0; i < V; i++){
		for(int j = 0; j < V; j++){
			printf("%d ", arestas[i][j]);
		}
		printf("\n");
	}
}

void mostra_adjacentes(int arestas[V][V], char v){
	int c = get_index(v);
    for(int i = 0; i< V; i++){
        if(arestas[c][i] == 1){
            printf("%c -> %c\n", v, i + 114);
        }
    }
}

void mostra_distancias(int arestas[V][V], char v){
    int fila[V], visitado[V], distancia[V];
    int inicio, fim;

    int origem_idx = get_index(v);
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


int main(void) {
	char lista_de_vertices[V] = {'r', 's', 't', 'u', 'v', 'w', 'x', 'y'};
	char lista_de_arestas[E][2] = {"vr", "rv", "rs", "sr", "sw", "ws", "wt", "tw", "wx", "xw", "tx", "xt", "tu", "ut", "xu", "ux", "xy", "yx", "uy", "yu"};
  	int arestas[V][V];
	inicia_arestas(arestas);
	printf("Matriz de adjacências\n");
	for(int i = 0; i < E; i++){
		cria_arestas(arestas, get_index(lista_de_arestas[i][0]), get_index(lista_de_arestas[i][1]));
	}
	mostra_arestas(arestas);
	printf("Lista de adjacências\n");
	for(int i = 0; i < V; i++){
		mostra_adjacentes(arestas, lista_de_vertices[i]);
	}
	printf("Matriz de distâncias\n");
	for(int i = 0; i < V; i++){
		mostra_distancias(arestas, lista_de_vertices[i]);
	}		
  return 0;
}