#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
	int valor;
	struct Celula *proximo;
	struct Celula *anterior;
} Celula;

typedef struct {
	Celula *head;
	Celula *tail;
	int qtde;
} Queue;

Celula *cria_celula(int valor){
	Celula *celula = malloc(sizeof(Celula));
	celula->proximo = NULL;
	celula->anterior = NULL;
	celula->valor = valor;

	return celula;
}

Queue *cria_queue(){
	Queue *queue = malloc(sizeof(Queue));
	queue->head = NULL;
	queue->tail = NULL;
	queue->qtde = 0;

	return queue;
}

void enqueue(Queue *queue, int valor){
    Celula *nova = cria_celula(valor);
	if (queue->qtde == 0){
        queue->head = nova;
    } else {
        queue->tail->proximo = nova;
        nova->anterior = queue->tail; 
    }
    queue->tail = nova;
    queue->qtde++;
	}

int dequeue(Queue *queue){
	int valor;
    Celula *aux;

    if(queue->qtde == 0){
        return -1;
    }
    if (queue->qtde == 1){
        valor = queue->head->valor;
        aux = queue->head;
        queue->head = NULL;
        queue->tail = NULL;
    } else {
        valor = queue->head->valor;
        aux = queue->head;
        queue->head = queue->head->proximo;
    }

    queue->qtde--;
    free(aux);
    return valor;
}

void show(Queue *queue){
    Celula *atual = queue->head;
    while (atual != NULL){
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
}

void show_invertido(Queue *queue){
	Celula *atual = queue->tail;
    while (atual!=NULL){
        printf("%d", atual->valor);
        atual = atual->anterior;
    }

}

void soma_fila (Queue *qnum1, Queue *qnum2, Queue *res){
    int resto = 0;

    Celula *atual1 = qnum1->tail;
    Celula *atual2 = qnum2->tail;
    
    while(atual1 != NULL){
        int soma = atual1->valor + atual2->valor + resto; 

        enqueue(res, soma%10);
        resto = soma/10; 

        atual1 = atual1->anterior; 
        atual2 = atual2->anterior;
    }

    if(resto != 0){ 
        enqueue(res, resto);
    }
}

int main(void) {
	Queue *qnum1 = cria_queue();
	Queue *qnum2 = cria_queue();
	Queue *res = cria_queue();
	
	char num1[100];
	char num2[100];
	fgets(num1, sizeof(num1), stdin);
	fgets(num2, sizeof(num2), stdin);

	int i = 0;
	while(num1[i] != '\n'){		
		enqueue(qnum1, (int)(num1[i]) - 48);
		enqueue(qnum2, (int)(num2[i]) - 48);
		i++;
		}

	soma_fila(qnum1, qnum2, res);
    show_invertido(res);
    
    return 0;
}