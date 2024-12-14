#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

struct MinHeapNode* createNode(char data, unsigned freq) {
    struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    minHeap->size++;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

struct MinHeap* buildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = createNode(data[i], freq[i]);
    minHeap->size = size;
    for (int i = (minHeap->size - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
    return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = buildMinHeap(data, freq, size);
    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = createNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void printCodes(struct MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

void HuffmanCodes(char data[], int freq[], int size) {
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int arr[100], top = 0;
    printCodes(root, arr, top);
}

void calculateFrequency(char str[], char data[], int freq[], int *size) {
    int count[MAX_SIZE] = {0};

    for (int i = 0; str[i]; i++)
        count[(int)str[i]]++;

    int j = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (count[i]) {
            data[j] = (char)i;
            freq[j] = count[i];
            j++;
        }
    }
    *size = j;
}

int main() {
    char str[1000];
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;

    char data[MAX_SIZE];
    int freq[MAX_SIZE];
    int size;

    calculateFrequency(str, data, freq, &size);
    HuffmanCodes(data, freq, size);
    return 0;
}
