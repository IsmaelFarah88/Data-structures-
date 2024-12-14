#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} CircularArray;

void init(CircularArray* arr) {
    arr->front = -1;
    arr->rear = -1;
}

int isFull(CircularArray* arr) {
    return (arr->front == (arr->rear + 1) % MAX_SIZE);
}

int isEmpty(CircularArray* arr) {
    return (arr->front == -1);
}

void insert(CircularArray* arr, int value) {
    if (isFull(arr)) {
        printf("Array is full, cannot insert %d\n", value);
        return;
    }
    if (isEmpty(arr)) {
        arr->front = 0;
    }
    arr->rear = (arr->rear + 1) % MAX_SIZE;
    arr->items[arr->rear] = value;
}

int delete(CircularArray* arr) {
    if (isEmpty(arr)) {
        printf("Array is empty, cannot delete\n");
        return -1;
    }
    int deletedItem = arr->items[arr->front];
    if (arr->front == arr->rear) {
        arr->front = -1;
        arr->rear = -1;
    } else {
        arr->front = (arr->front + 1) % MAX_SIZE;
    }
    return deletedItem;
}

void display(CircularArray* arr) {
    if (isEmpty(arr)) {
        printf("Circular Array is empty\n");
        return;
    }
    int i = arr->front;
    printf("Final contents of Circular Array:\n");
    while (1) {
        printf("%d ", arr->items[i]);
        if (i == arr->rear) break;
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}

int main() {
    CircularArray arr;
    init(&arr);
    int operationsCount;

    scanf("%d", &operationsCount);

    for (int i = 0; i < operationsCount; i++) {
        char operation;
        int value;
        scanf(" %c", &operation);

        if (operation == 'I') {
            scanf("%d", &value);
            insert(&arr, value);
        } else if (operation == 'D') {
            int deleted = delete(&arr);
            if (deleted != -1) {
                printf("Deleted element: %d\n", deleted);
            }
        }
    }

    display(&arr);
    return 0;
}
