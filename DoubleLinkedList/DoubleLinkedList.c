#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

void add_to_head(Node** head, Node** tail, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = (*head);
    new_node->prev = NULL;
    if ((*head) != NULL)
        (*head)->prev = new_node;
    else
        *tail = new_node;
    *head = new_node;
}

void add_to_tail(Node** head, Node** tail, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = *tail;
    if (*tail != NULL)
        (*tail)->next = new_node;
    else
        *head = new_node;
    *tail = new_node;
}

void remove_head(Node** head, Node** tail) {
    if (*head == NULL)
        return;
    Node* temp = *head;
    *head = (*head)->next;
    if (*head != NULL)
        (*head)->prev = NULL;
    else
        *tail = NULL;
    free(temp);
}

void remove_tail(Node** head, Node** tail) {
    if (*tail == NULL)
        return;
    Node* temp = *tail;
    *tail = (*tail)->prev;
    if (*tail != NULL)
        (*tail)->next = NULL;
    else
        *head = NULL;
    free(temp);
}

Node* search(Node* head, int value) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == value)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void print_list(Node* head, Node* tail) {
    printf("Forward Traversal:\n");
    Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL)
            printf(" -> ");
        temp = temp->next;
    }
    printf(" -> NULL\n");

    printf("Backward Traversal:\n");
    temp = tail;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->prev != NULL)
            printf(" -> ");
        temp = temp->prev;
    }
    printf(" -> NULL\n");
}

int main() {
    Node* head = NULL;
    Node* tail = NULL;
    char command[20];
    int value;

    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "addHead") == 0) {
            scanf("%d", &value);
            add_to_head(&head, &tail, value);
        } else if (strcmp(command, "addTail") == 0) {
            scanf("%d", &value);
            add_to_tail(&head, &tail, value);
        } else if (strcmp(command, "removeHead") == 0) {
            remove_head(&head, &tail);
        } else if (strcmp(command, "removeTail") == 0) {
            remove_tail(&head, &tail);
        } else if (strcmp(command, "search") == 0) {
            scanf("%d", &value);
            Node* result = search(head, value);
            if (result != NULL)
                printf("Found: %d\n", result->data);
            else
                printf("Not Found\n");
        } else if (strcmp(command, "printList") == 0) {
            print_list(head, tail);
        }
    }

    return 0;
}
