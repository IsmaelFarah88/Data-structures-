#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node* next;
};

struct LinkedList {
    struct Node* head;
    struct Node* tail;
};

struct Node* createNode(int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    return new_node;
}

void addToHead(struct LinkedList* list, int new_data) {
    struct Node* new_node = createNode(new_data);
    new_node->next = list->head;
    list->head = new_node;
    if (list->tail == NULL) {
        list->tail = new_node;
    }
}

void removeFromHead(struct LinkedList* list) {
    if (list->head == NULL) return;
    struct Node* temp = list->head;
    list->head = list->head->next;
    if (list->head == NULL) {
        list->tail = NULL;
    }
    free(temp);
}

void addToTail(struct LinkedList* list, int new_data) {
    struct Node* new_node = createNode(new_data);
    
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

void removeFromTail(struct LinkedList* list) {
    if (list->head == NULL) return;

    if (list->head == list->tail) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        return;
    }
    
    struct Node* temp = list->head;
    while (temp->next != list->tail) {
        temp = temp->next;
    }
    
    free(list->tail);
    list->tail = temp;
    list->tail->next = NULL;
}

void addAtPosition(struct LinkedList* list, int position, int new_data) {
    if (position == 0) {
        addToHead(list, new_data);
        return;
    }

    struct Node* new_node = createNode(new_data);
    struct Node* temp = list->head;

    for (int i = 0; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        free(new_node);
        return;
    }

    new_node->next = temp->next;
    temp->next = new_node;

    if (new_node->next == NULL) {
        list->tail = new_node;
    }
}

void removeAtPosition(struct LinkedList* list, int position) {
    if (list->head == NULL) return;

    struct Node* temp = list->head;
    
    if (position == 0) {
        removeFromHead(list);
        return;
    }
    
    struct Node* prev = NULL;
    for (int i = 0; i < position && temp != NULL; i++) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) return;
    
    prev->next = temp->next;
    if (temp == list->tail) {
        list->tail = prev;
    }
    free(temp);
}

int search(struct Node* head, int value) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == value) return 1;
        temp = temp->next;
    }
    return 0;
}

void edit(struct Node* head, int old_value, int new_value) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == old_value) {
            temp->data = new_value;
            return;
        }
        temp = temp->next;
    }
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

void processCommands() {
    struct LinkedList list = {NULL, NULL};
    char command[20];
    int value, position;

    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "addHead") == 0) {
            scanf("%d", &value);
            addToHead(&list, value);
        } else if (strcmp(command, "addTail") == 0) {
            scanf("%d", &value);
            addToTail(&list, value);
        } else if (strcmp(command, "removeHead") == 0) {
            removeFromHead(&list);
        } else if (strcmp(command, "removeTail") == 0) {
            removeFromTail(&list);
        } else if (strcmp(command, "addAtPosition") == 0) {
            scanf("%d %d", &position, &value);
            addAtPosition(&list, position, value);
        } else if (strcmp(command, "removeAtPosition") == 0) {
            scanf("%d", &position);
            removeAtPosition(&list, position);
        } else if (strcmp(command, "search") == 0) {
            scanf("%d", &value);
            if (search(list.head, value)) {
                printf("Found\n");
            } else {
                printf("Not Found\n");
            }
        } else if (strcmp(command, "editValue") == 0) {
            int old_value, new_value;
            scanf("%d %d", &old_value, &new_value);
            edit(list.head, old_value, new_value);
        } else if (strcmp(command, "printList") == 0) {
            printList(list.head);
        }
    }
}

int main() {
    processCommands();
    return 0;
}
