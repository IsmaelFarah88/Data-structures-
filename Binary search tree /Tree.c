#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

void search(struct Node* root, int data) {
    if (root == NULL) {
        printf("Not Found\n");
        return;
    }
    if (root->data == data) {
        printf("Found\n");
        return;
    }
    if (data < root->data)
        search(root->left, data);
    else
        search(root->right, data);
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL) return root;
    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void printInOrder(struct Node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->data);
        printInOrder(root->right);
    }
}

void printPreOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

void printPostOrder(struct Node* root) {
    if (root != NULL) {
        printPostOrder(root->left);
        printPostOrder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    struct Node* root = NULL;
    int n, value;
    char operation[20];

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s", operation);

        if (strcmp(operation, "insert") == 0) {
            scanf("%d", &value);
            root = insert(root, value);
        } else if (strcmp(operation, "delete") == 0) {
            scanf("%d", &value);
            root = deleteNode(root, value);
        } else if (strcmp(operation, "search") == 0) {
            scanf("%d", &value);
            search(root, value);
        } else if (strcmp(operation, "printInOrder") == 0) {
            printInOrder(root);
            printf("\n");
        } else if (strcmp(operation, "printPreOrder") == 0) {
            printPreOrder(root);
            printf("\n");
        } else if (strcmp(operation, "printPostOrder") == 0) {
            printPostOrder(root);
            printf("\n");
        }
    }

    return 0;
}
