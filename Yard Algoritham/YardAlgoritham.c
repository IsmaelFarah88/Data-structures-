#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct Stack {
    float data[MAX];
    int top;
} Stack;

void createStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, float value) {
    s->data[++s->top] = value;
}

float pop(Stack *s) {
    return s->data[s->top--];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    createStack(&s);
    int k = 0;
    for (int i = 0; infix[i]; i++) {
        if (isdigit(infix[i])) {
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';
            i--;
        } else if (infix[i] == '(') {
            push(&s, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(&s) && s.data[s.top] != '(')
                postfix[k++] = pop(&s);
            pop(&s);
        } else {
            while (!isEmpty(&s) && precedence(s.data[s.top]) >= precedence(infix[i]))
                postfix[k++] = pop(&s);
            push(&s, infix[i]);
        }
    }
    while (!isEmpty(&s))
        postfix[k++] = pop(&s);
    postfix[k] = '\0';
}

float evaluatePostfix(char* postfix) {
    Stack s;
    createStack(&s);
    for (int i = 0; postfix[i]; i++) {
        if (isdigit(postfix[i])) {
            float num = 0;
            while (isdigit(postfix[i]) || postfix[i] == '.') {
                if (postfix[i] == '.') {
                    i++;
                    float decimal = 0.1;
                    while (isdigit(postfix[i])) {
                        num += (postfix[i++] - '0') * decimal;
                        decimal /= 10;
                    }
                } else {
                    num = num * 10 + (postfix[i++] - '0');
                }
            }
            push(&s, num);
        } else if (postfix[i] != ' ') {
            float val2 = pop(&s);
            float val1 = pop(&s);
            switch (postfix[i]) {
                case '+': push(&s, val1 + val2); break;
                case '-': push(&s, val1 - val2); break;
                case '*': push(&s, val1 * val2); break;
                case '/': push(&s, val1 / val2); break;
            }
        }
    }
    return pop(&s);
}

int main() {
    char infix[MAX];
    fgets(infix, MAX, stdin);

    char postfix[MAX];
    infixToPostfix(infix, postfix);
    printf("%.2f\n", evaluatePostfix(postfix));

    return 0;
}
