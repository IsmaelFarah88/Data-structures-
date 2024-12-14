include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 5

int deque[MAX];
int front = -1, rear = -1;

bool isFull() {
    return (front == (rear + 1) % MAX);
}

bool isEmpty() {
    return front == -1;
}

void insertFront(int x) {
    if (isFull()) {
        printf("Deque is full, cannot insert at front\n");
        return;
    }
    if (front == -1) {
        front = rear = 0;
    } else if (front == 0) {
        front = MAX - 1;
    } else {
        front--;
    }
    deque[front] = x;
    printf("Element %d inserted at front\n", x);
}

void insertRear(int x) {
    if (isFull()) {
        printf("Deque is full, cannot insert at rear\n");
        return;
    }
    if (front == -1) {
        front = rear = 0;
    } else if (rear == MAX - 1) {
        rear = 0;
    } else {
        rear++;
    }
    deque[rear] = x;
    printf("Element %d inserted at rear\n", x);
}

void deleteFront() {
    if (isEmpty()) {
        printf("Deque is empty, cannot delete from front\n");
        return;
    }
    printf("Element %d removed from front\n", deque[front]);
    if (front == rear) {
        front = rear = -1;
    } else if (front == MAX - 1) {
        front = 0;
    } else {
        front++;
    }
}

void deleteRear() {
    if (isEmpty()) {
        printf("Deque is empty, cannot delete from rear\n");
        return;
    }
    printf("Element %d removed from rear\n", deque[rear]);
    if (front == rear) {
        front = rear = -1;
    } else if (rear == 0) {
        rear = MAX - 1;
    } else {
        rear--;
    }
}

void getFront() {
    if (isEmpty()) {
        printf("Deque is empty, no front element\n");
    } else {
        printf("Front element: %d\n", deque[front]);
    }
}

void getRear() {
    if (isEmpty()) {
        printf("Deque is empty, no rear element\n");
    } else {
        printf("Rear element: %d\n", deque[rear]);
    }
}

void isFullCheck() {
    if (isFull()) {
        printf("Deque is full\n");
    } else {
        printf("Deque is not full\n");
    }
}

void isEmptyCheck() {
    if (isEmpty()) {
        printf("Deque is empty\n");
    } else {
        printf("Deque is not empty\n");
    }
}

int main() {
    char command[20];
    int value;

    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "InsertFront") == 0) {
            scanf("%d", &value);
            insertFront(value);
        } else if (strcmp(command, "InsertRear") == 0) {
            scanf("%d", &value);
            insertRear(value);
        } else if (strcmp(command, "DeleteFront") == 0) {
            deleteFront();
        } else if (strcmp(command, "DeleteRear") == 0) {
            deleteRear();
        } else if (strcmp(command, "GetFront") == 0) {
            getFront();
        } else if (strcmp(command, "GetRear") == 0) {
            getRear();
        } else if (strcmp(command, "IsFull") == 0) {
            isFullCheck();
        } else if (strcmp(command, "IsEmpty") == 0) {
            isEmptyCheck();
        }
    }

    return 0;
}
