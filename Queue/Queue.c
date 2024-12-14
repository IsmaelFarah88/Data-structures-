#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

void initialize(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue* q) {
    return q->front == -1;
}

int isFull(Queue* q) {
    return q->rear == MAX - 1;
}

void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->items[++q->rear] = value;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int value = q->items[q->front];
    if (q->front >= q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return value;
}

int peek(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->items[q->front];
}

int main() {
    Queue q;
    initialize(&q);
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char command[10];
        int value;
        scanf("%s", command);

        if (strcmp(command, "enqueue") == 0) {
            scanf("%d", &value);
            enqueue(&q, value);
        } else if (strcmp(command, "dequeue") == 0) {
            printf("%d\n", dequeue(&q));
        } else if (strcmp(command, "peek") == 0) {
            printf("%d\n", peek(&q));
        }
    }

    return 0;
}
