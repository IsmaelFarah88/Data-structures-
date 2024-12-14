
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

void joinLists(struct Node** headA, struct Node* headB) {
    struct Node* temp = *headA;
    if (temp == NULL) {
        *headA = headB;
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = headB;
}

int isSublist(struct Node* headA, struct Node* headB) {
    struct Node* tempA = headA;
    struct Node* tempB;
    
    while (tempA != NULL) {
        tempB = headB;
        struct Node* start = tempA;
        
        while (tempB != NULL && start != NULL && start->data == tempB->data) {
            start = start->next;
            tempB = tempB->next;
        }
        
        if (tempB == NULL) {
            return 1;
        }
        tempA = tempA->next;
    }
    return 0;
}

int main() {
    struct Node* listA = NULL;
    struct Node* listB = NULL;
    int n, m, value;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        appendNode(&listA, value);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &value);
        appendNode(&listB, value);
    }

    int result = isSublist(listA, listB);
    printf("%d\n", result);

    printList(listA);
    joinLists(&listA, listB);
    printList(listB);

    return 0;
}
