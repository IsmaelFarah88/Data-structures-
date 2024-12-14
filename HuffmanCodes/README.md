هذا الكود يقوم بتنفيذ خوارزمية **Huffman Coding**، وهي خوارزمية لضغط البيانات باستخدام الشجرة الثنائية. تعتمد الخوارزمية على توليد رموز مختصرة لكل حرف بناءً على تكراره في النص. يتم استخدام **Min Heap** لبناء شجرة هوفمان بكفاءة.

سنشرح الكود سطرًا بسطر ونفهم كل جزء منه بالتفصيل.

---

### 1. تضمين المكتبات
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```
- **`#include <stdio.h>`**: هذه المكتبة تحتوي على الدوال الخاصة بالإدخال والإخراج، مثل `printf` و `scanf`.
- **`#include <stdlib.h>`**: هذه المكتبة تحتوي على الدوال الخاصة بتخصيص الذاكرة، مثل `malloc`.
- **`#include <string.h>`**: هذه المكتبة تحتوي على الدوال الخاصة بالتعامل مع السلاسل النصية، مثل `strcspn`.

---

### 2. تعريف الثوابت والهياكل
```c
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
```
- **`#define MAX_SIZE 256`**: يحدد الحد الأقصى لعدد العناصر في المصفوفات.
- **`struct MinHeapNode`**: يعرّف هيكلًا يمثل عقدة في الشجرة.
  - **`char data`**: يحتوي على الحرف.
  - **`unsigned freq`**: يحتوي على تكرار الحرف.
  - **`struct MinHeapNode *left, *right`**: يحتوي على مؤشرين للعقد الفرعية (اليسار واليمين).
- **`struct MinHeap`**: يعرّف هيكلًا يمثل الـ Min Heap.
  - **`unsigned size`**: يحتوي على حجم الـ Min Heap.
  - **`unsigned capacity`**: يحتوي على السعة القصوى للـ Min Heap.
  - **`struct MinHeapNode** array`**: يحتوي على مصفوفة من العقد.

---

### 3. دالة `createNode`
```c
struct MinHeapNode* createNode(char data, unsigned freq) {
    struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}
```
- **الهدف**: إنشاء عقدة جديدة.
- **`struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));`**: يتم تخصيص ذاكرة لعقدة جديدة.
- **`node->data = data;`**: يتم تعيين الحرف.
- **`node->freq = freq;`**: يتم تعيين التكرار.
- **`node->left = node->right = NULL;`**: يتم تعيين العقد الفرعية إلى `NULL`.
- **`return node;`**: يتم إرجاع العقدة الجديدة.

---

### 4. دالة `createMinHeap`
```c
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
```
- **الهدف**: إنشاء Min Heap جديد.
- **`struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));`**: يتم تخصيص ذاكرة للـ Min Heap.
- **`minHeap->size = 0;`**: يتم تعيين حجم الـ Min Heap إلى `0`.
- **`minHeap->capacity = capacity;`**: يتم تعيين السعة القصوى.
- **`minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));`**: يتم تخصيص ذاكرة لمصفوفة العقد.
- **`return minHeap;`**: يتم إرجاع الـ Min Heap الجديد.

---

### 5. دالة `swapMinHeapNode`
```c
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}
```
- **الهدف**: تبديل عقدتين في الـ Min Heap.
- **`struct MinHeapNode* temp = *a;`**: يتم تخزين العقدة الأولى في متغير مؤقت.
- **`*a = *b;`**: يتم تبديل العقدة الأولى بالعقدة الثانية.
- **`*b = temp;`**: يتم تبديل العقدة الثانية بالعقدة الأولى.

---

### 6. دالة `minHeapify`
```c
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
```
- **الهدف**: ترتيب الـ Min Heap بعد إزالة عقدة.
- **`int smallest = idx;`**: يتم تعيين الفهرس الأصغر إلى الفهرس الحالي.
- **`int left = 2 * idx + 1;`**: يتم حساب فهرس العقدة اليسرى.
- **`int right = 2 * idx + 2;`**: يتم حساب فهرس العقدة اليمنى.
- **`if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)`**: إذا كانت العقدة اليسرى أصغر، يتم تحديث الفهرس الأصغر.
- **`if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)`**: إذا كانت العقدة اليمنى أصغر، يتم تحديث الفهرس الأصغر.
- **`if (smallest != idx)`**: إذا لم يكن الفهرس الأصغر هو الفهرس الحالي، يتم تبديل العقدتين واستدعاء `minHeapify` مرة أخرى.

---

### 7. دالة `extractMin`
```c
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}
```
- **الهدف**: إزالة أصغر عقدة من الـ Min Heap.
- **`struct MinHeapNode* temp = minHeap->array[0];`**: يتم تخزين العقدة الأصغر في متغير مؤقت.
- **`minHeap->array[0] = minHeap->array[minHeap->size - 1];`**: يتم استبدال العقدة الأصغر بالعقدة الأخيرة.
- **`minHeap->size--;`**: يتم تقليل حجم الـ Min Heap.
- **`minHeapify(minHeap, 0);`**: يتم ترتيب الـ Min Heap.
- **`return temp;`**: يتم إرجاع العقدة الأصغر.

---

### 8. دالة `insertMinHeap`
```c
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    minHeap->size++;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}
```
- **الهدف**: إضافة عقدة جديدة إلى الـ Min Heap.
- **`minHeap->size++;`**: يتم زيادة حجم الـ Min Heap.
- **`int i = minHeap->size - 1;`**: يتم تعيين الفهرس إلى العقدة الجديدة.
- **`while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)`**: إذا كانت العقدة الجديدة أصغر من العقدة الأصلية، يتم تبديلهما.
- **`minHeap->array[i] = minHeapNode;`**: يتم إضافة العقدة الجديدة إلى الـ Min Heap.

---

### 9. دالة `buildMinHeap`
```c
struct MinHeap* buildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = createNode(data[i], freq[i]);
    minHeap->size = size;
    for (int i = (minHeap->size - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
    return minHeap;
}
```
- **الهدف**: بناء Min Heap من مصفوفة الحروف وتكراراتها.
- **`struct MinHeap* minHeap = createMinHeap(size);`**: يتم إنشاء Min Heap جديد.
- **`for (int i = 0; i < size; ++i)`**: يتم إنشاء عقدة لكل حرف وتكراره.
- **`minHeap->size = size;`**: يتم تعيين حجم الـ Min Heap.
- **`for (int i = (minHeap->size - 1) / 2; i >= 0; --i)`**: يتم ترتيب الـ Min Heap.
- **`return minHeap;`**: يتم إرجاع الـ Min Heap.

---

### 10. دالة `buildHuffmanTree`
```c
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
```
- **الهدف**: بناء شجرة هوفمان.
- **`struct MinHeapNode *left, *right, *top;`**: يتم تعريف مؤشرات للعقد اليسرى واليمنى والعلوية.
- **`struct MinHeap* minHeap = buildMinHeap(data, freq, size);`**: يتم بناء Min Heap.
- **`while (minHeap->size != 1)`**: حتى يتبقى عقدة واحدة فقط في الـ Min Heap.
  - **`left = extractMin(minHeap);`**: يتم إزالة أصغر عقدة.
  - **`right = extractMin(minHeap);`**: يتم إزالة أصغر عقدة أخرى.
  - **`top = createNode('$', left->freq + right->freq);`**: يتم إنشاء عقدة جديدة بتكرار مجموع العقدتين.
  - **`top->left = left;`**: يتم تعيين العقدة اليسرى.
  - **`top->right = right;`**: يتم تعيين العقدة اليمنى.
  - **`insertMinHeap(minHeap, top);`**: يتم إضافة العقدة الجديدة إلى الـ Min Heap.
- **`return extractMin(minHeap);`**: يتم إرجاع العقدة الأخيرة في الـ Min Heap.

---

### 11. دالة `printCodes`
```c
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
```
- **الهدف**: طباعة رموز هوفمان لكل حرف.
- **`if (root->left)`**: إذا كانت هناك عقدة يسرى، يتم إضافة `0` إلى المصفوفة.
- **`if (root->right)`**: إذا كانت هناك عقدة يمنى، يتم إضافة `1` إلى المصفوفة.
- **`if (!(root->left) && !(root->right))`**: إذا كانت العقدة هي عقدة ورقة، يتم طباعة الحرف ورمزه.

---

### 12. دالة `HuffmanCodes`
```c
void HuffmanCodes(char data[], int freq[], int size) {
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int arr[100], top = 0;
    printCodes(root, arr, top);
}
```
- **الهدف**: تنفيذ خوارزمية هوفمان وطباعة الرموز.
- **`struct MinHeapNode* root = buildHuffmanTree(data, freq, size);`**: يتم بناء شجرة هوفمان.
- **`int arr[100], top = 0;`**: يتم تعريف مصفوفة لتخزين الرموز.
- **`printCodes(root, arr, top);`**: يتم طباعة الرموز.

---

### 13. دالة `calculateFrequency`
```c
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
```
- **الهدف**: حساب تكرار كل حرف في النص.
- **`int count[MAX_SIZE] = {0};`**: يتم تهيئة مصفوفة لحساب التكرارات.
- **`for (int i = 0; str[i]; i++)`**: يتم حساب تكرار كل حرف.
- **`for (int i = 0; i < MAX_SIZE; i++)`**: يتم تخزين الحروف وتكراراتها في مصفوفتين.
- **`*size = j;`**: يتم تعيين حجم المصفوفة.

---

### 14. دالة `main`
```c
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
```
- **الهدف**: بدء تنفيذ البرنامج ومعالجة الأوامر.
- **`char str[1000];`**: يتم تعريف مصفوفة لتخزين النص.
- **`fgets(str, sizeof(str), stdin);`**: يتم قراءة النص من المستخدم.
- **`str[strcspn(str, "\n")] = 0;`**: يتم إزالة السطر الجديد من نهاية النص.
- **`char data[MAX_SIZE];`**: يتم تعريف مصفوفة لتخزين الحروف.
- **`int freq[MAX_SIZE];`**: يتم تعريف مصفوفة لتخزين التكرارات.
- **`int size;`**: يتم تعريف متغير لتخزين حجم المصفوفة.
- **`calculateFrequency(str, data, freq, &size);`**: يتم حساب تكرار كل حرف.
- **`HuffmanCodes(data, freq, size);`**: يتم تنفيذ خوارزمية هوفمان وطباعة الرموز.

---

### ملخص الكود
هذا الكود يقوم بتنفيذ خوارزمية **Huffman Coding** لضغط البيانات. يتم استخدام **Min Heap** لبناء شجرة هوفمان بكفاءة، ثم يتم طباعة رموز هوفمان لكل حرف بناءً على تكراره في النص.
