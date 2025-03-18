#include <stdio.h>

#define LEN 100

typedef struct {
  char data[LEN];
  int head;
  int tail;
  int qtde;
} Queue;

void enqueue(Queue *queue, char caracter) { //adicionar
    if (queue->tail < LEN) {
      queue->data[queue->tail++] = caracter;
      queue->qtde++;
    } 
}

int dequeue(Queue *queue) { //remover
    if (queue->tail > queue->head) {
      queue->qtde--;
      return queue->data[queue->head++];
    } else {
      return -1;
    }
}

void show(Queue *queue) { //imprimi
    for (int i = queue->head; i < queue->tail; i++) {
        printf("%c", queue->data[i]);
    }
}

void start_queue(Queue *queue) { //inicializa
    queue->tail = 0;
    queue->head = 0;
    queue->qtde = 0;
}

int main(void) {
    char s[LEN];

    fgets(s, sizeof(s), stdin);

    Queue queue;
    Queue queue2;

    start_queue(&queue);
    start_queue(&queue2);

    for (int i = 0; s[i] != '\0'; i++) {
        enqueue(&queue, s[i]);
    }

    int verificacao = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        char saida = dequeue(&queue);
        if (saida == '('){
            enqueue(&queue2, saida);
        }
        if (saida == ')'){
            int valor = dequeue(&queue2);
            if (valor == -1){
                verificacao = 1;
                printf("incorreto\n");
                break;
            }
        }
        show(&queue);
    }

    if (verificacao == 0 && queue2.qtde != 0){
        printf("incorreto\n");
    }
    if (verificacao == 0 && queue2.qtde == 0){
        printf("correto\n");
    }



    return 0;
}
