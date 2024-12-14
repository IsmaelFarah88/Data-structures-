#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Stack {
    int data[MAX];
    int top;
} Stack;

void createStack(Stack *s) {
    s->top = -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack overflow!\n");
        return;
    }
    s->data[++s->top] = value;
}

void pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow!\n");
    } else {
        printf("%d\n", s->data[s->top--]);
    }
}

void peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
    } else {
        printf("%d\n", s->data[s->top]);
    }
}

int main() {
    Stack s;
    createStack(&s);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char operation[10];
        scanf("%s", operation);

        if (strcmp(operation, "push") == 0) {
            int value;
            scanf("%d", &value);
            push(&s, value);
        } else if (strcmp(operation, "pop") == 0) {
            pop(&s);
        } else if (strcmp(operation, "peek") == 0) {
            peek(&s);
        }
    }

    return 0;
}
