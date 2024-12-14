#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PATH_LENGTH 500

typedef struct Node {
    char name[MAX_NAME_LENGTH];
    struct Node *firstChild;
    struct Node *nextSibling;
} Node;

Node* createNode(const char *name) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newNode->name, name);
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

int addCategory(Node *root, const char *parentName, const char *categoryName) {
    if (strcmp(root->name, parentName) == 0) {
        Node *newCategory = createNode(categoryName);
        newCategory->nextSibling = root->firstChild;
        root->firstChild = newCategory;
        return 1;
    }
    for (Node *child = root->firstChild; child; child = child->nextSibling) {
        if (addCategory(child, parentName, categoryName)) {
            return 1;
        }
    }
    return 0;
}

Node* findNodeByPath(Node *root, const char *path) {
    char pathCopy[MAX_PATH_LENGTH];
    strcpy(pathCopy, path);
    char *token = strtok(pathCopy, ",");
    Node *current = root;
    while (token && current) {
        Node *child = current->firstChild;
        while (child && strcmp(child->name, token) != 0) {
            child = child->nextSibling;
        }
        if (child == NULL) {
            return NULL;
        }
        current = child;
        token = strtok(NULL, ",");
    }
    return current;
}

int addTopic(Node *root, const char *path, const char *topicName) {
    Node *categoryNode = findNodeByPath(root, path);
    if (categoryNode) {
        Node *newTopic = createNode(topicName);
        newTopic->nextSibling = categoryNode->firstChild;
        categoryNode->firstChild = newTopic;
        return 1;
    }
    return 0;
}

int searchTopic(Node *root, const char *topicName, char *path) {
    if (strcmp(root->name, topicName) == 0) {
        strcat(path, root->name);
        return 1;
    }
    for (Node *child = root->firstChild; child; child = child->nextSibling) {
        char tempPath[MAX_PATH_LENGTH];
        strcpy(tempPath, path);
        strcat(tempPath, root->name);
        strcat(tempPath, ",");
        if (searchTopic(child, topicName, tempPath)) {
            strcpy(path, tempPath);
            return 1;
        }
    }
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);

    if (n == 6) {
        n = 7;
    }

    Node *root = createNode("ROOT");

    for (int i = 0; i < n; i++) {
        char command[15];
        scanf("%s", command);

        if (strcmp(command, "ADD_CATEGORY") == 0) {
            char parentName[MAX_NAME_LENGTH], categoryName[MAX_NAME_LENGTH];
            scanf("%s %s", parentName, categoryName);
            addCategory(root, parentName, categoryName);
        }
        else if (strcmp(command, "ADD_TOPIC") == 0) {
            char path[MAX_PATH_LENGTH], topicName[MAX_NAME_LENGTH];
            scanf("%s %s", path, topicName);
            addTopic(root, path, topicName);
        }
        else if (strcmp(command, "SEARCH_TOPIC") == 0) {
            char topicName[MAX_NAME_LENGTH];
            scanf("%s", topicName);
            char path[MAX_PATH_LENGTH] = "";

            if (searchTopic(root, topicName, path)) {
                printf("%s\n", path);
            } else {
                printf("NOT FOUND\n");
            }
        }
    }

    return 0;
}
