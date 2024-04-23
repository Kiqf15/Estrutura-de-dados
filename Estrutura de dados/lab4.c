#include <stdio.h>

#define LEN 100

typedef struct {
  char data[LEN];
  int head;
  int tail;
  int qtde;
} Queue;

int isFull(Queue *queue) { return queue->qtde == LEN; }

int isEmpty(Queue *queue) { return queue->qtde == 0; }

void enqueue(Queue *queue, char caracter) {
  // implementar
  if (!isFull(queue)) {
    caracter = queue->data[queue->tail % LEN] = caracter;
    queue->tail++;
    queue->qtde++;
  }
}

char dequeue(Queue *queue) {
  // implementar
  if (!isEmpty(queue)) {
    char caracter = queue->data[queue->head % LEN];
    queue->head++;
    queue->qtde--;
    return caracter;

  } 
  else {
    return -1;
  }
}

void show(Queue *queue) {
  // implementar
  for (int i = queue->head; i < queue->tail; i++) {
    printf("%c ", queue->data[i % LEN]);
  }
}

void start_queue(Queue *queue) {
  // implementar
  queue->head = 0;
  queue->tail = 0;
  queue->qtde = 0;
}

int main(void) {
  char s[LEN];
  Queue queue;
  Queue queue2;
  int cont = 0;
  fgets(s, sizeof(s), stdin);

  // implementar
  start_queue(&queue);
  start_queue(&queue2);
  for (int i = 0; s[i] != '\0'; i++) {
    enqueue(&queue, s[i]);
    
  }
  for (int i = queue.head; i < queue.tail; i++) {
    if (s[i] == '(') {
      enqueue(&queue2, '(');
      cont++;
    } else if (s[i] == ')') {
      dequeue(&queue2);
      cont--;
      if(cont < 0){
        printf("incorreto");
        return 0;
      }
    }
    dequeue(&queue);
    show(&queue);
    }
  if (isEmpty(&queue2)) {
    printf("correto");
    return 0;
  } else if (!isEmpty(&queue2)) {
    printf("incorreto");
    return 0;
  }

  return 0;
}
