#include <stdio.h>
#include <stdlib.h>

typedef struct Celula{
	struct Celula *anterior;
	struct Celula *proximo;
	int valor;
}Celula;

typedef struct LDDE{
	Celula *primeiro;
	int qtde;
}LDDE;

LDDE *inicializa_lista(){
	LDDE *lista = malloc(sizeof(LDDE));
	lista->primeiro = NULL;
	lista->qtde = 0;
	return lista;
}

Celula *inicializa_celula(int valor){
	Celula *celula = malloc(sizeof(Celula));
	celula->anterior = NULL;
	celula->proximo = NULL;
	celula->valor = valor;
	return celula;
}

void inserir(LDDE *lista, int valor){
	Celula *novo = inicializa_celula(valor);
	if(lista->qtde == 0){
		lista->primeiro = novo;
	}else{
		Celula *atual = lista->primeiro;
		Celula *anterior = NULL;
		while(atual != NULL && atual->valor <= valor){
			anterior = atual;
			atual = atual->proximo;
		}
		if(anterior == NULL && atual != NULL){
			novo->proximo = atual;
			atual->anterior = novo;
			lista->primeiro = novo;
		}else{
			if(atual == NULL && anterior != NULL){
				anterior->proximo = novo;
				novo->anterior = anterior;
			}else{
				anterior->proximo = novo;
				novo->anterior = anterior;
				novo->proximo = atual;
				atual->anterior = novo;
			}
		}
	}
	lista->qtde++;
}

void imprimir_crescente(LDDE *lista){
	Celula *atual = lista->primeiro;
	while(atual != NULL){
		printf("%d ", atual->valor);
		atual = atual->proximo;
	}
	printf("\n");
}

void imprimir_decrescente(LDDE *lista){
	if (lista == NULL || lista->primeiro == NULL) { // Verifica se a lista está vazia
        return;
    }
    Celula *atual = lista->primeiro;
    // Percorre a lista até a última celula
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->anterior; 
    }
    printf("\n");
}

//Celula *buscar(LDDE *lista, int valor){
	// Implementar
//}

void remover(LDDE *lista, int valor){
	//Celula *atual = buscar(lista, valor);
	if (lista == NULL || lista->primeiro == NULL) { // Verifica se a lista está vazia
        return;
    }
    Celula *anterior = NULL;
    Celula *atual = lista->primeiro;
    //Busca a celula que vai ser removida
    while (atual != NULL && atual->valor < valor) {                                                             
        anterior = atual;                                    
        atual = atual->proximo;
    }
    //Se não encontrar o valor na lista
    if (atual == NULL || atual->valor != valor) {
        return;
    }
    Celula *proximo = atual->proximo; //próxima celula
    //Se for a primeira celula da lista
    if (anterior == NULL) {
        lista->primeiro = proximo;
        if(proximo != NULL){
            proximo->anterior = NULL;
        }
    }
    //Se for uma celula no final
    else if (proximo == NULL) {
        anterior->proximo = NULL; //O anterior passa a ser o último
    } 
    //Remover do meio
    else {
        anterior->proximo = proximo;
        proximo->anterior = anterior;
    }
    free(atual); //Libera a memória
    lista->qtde--;
}

int main(void) {
  LDDE *lista = inicializa_lista();
	int in[] = {2, 3, 9, 6, 7, 4, 1, 8, 0, 5};
	int out[] = {0, 9, 1, 8, 5, 5, 6, 2, 3, 4, 7};
	int len_in = sizeof(in) / sizeof(int);
	int len_out = sizeof(out) / sizeof(int);
	for(int i = 0; i < len_in; i ++){
		inserir(lista, in[i]);
		imprimir_crescente(lista);
		imprimir_decrescente(lista);
	}
	for(int j = 0; j < len_out; j++){
		remover(lista, out[j]);
		imprimir_crescente(lista);
		imprimir_decrescente(lista);
	}
  return 0;
}