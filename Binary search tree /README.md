هذا الكود يقوم بتنفيذ بنية بيانات **شجرة بحث ثنائية** (Binary Search Tree - BST)، وهي بنية بيانات تسمح بتخزين البيانات بشكل هرمي، حيث يكون كل عقدة تحتوي على قيمة، وقد تحتوي على عقدة فرعية يسارية وعقدة فرعية أخرى يمينية. تتبع الشجرة البحث الثنائية قواعد معينة تسمح بإجراء عمليات البحث والإدراج والحذف بكفاءة.

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
- **`#include <string.h>`**: هذه المكتبة تحتوي على الدوال الخاصة بالتعامل مع السلاسل النصية، مثل `strcmp`.

---

### 2. تعريف الهيكل `Node`
```c
struct Node {
    int data;
    struct Node *left, *right;
};
```
- **`struct Node`**: هذا السطر يعرّف هيكلًا يمثل عقدة في الشجرة.
- **`int data`**: يحتوي كل عقدة على بيانات (في هذه الحالة، عدد صحيح `int`).
- **`struct Node *left, *right`**: يحتوي كل عقدة على مؤشرين: واحد يشير إلى العقدة الفرعية اليسارية (`left`) والآخر يشير إلى العقدة الفرعية اليمينية (`right`).

---

### 3. دالة `createNode`
```c
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}
```
- **الهدف**: إنشاء عقدة جديدة.
- **`struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));`**: يتم تخصيص ذاكرة لعقدة جديدة باستخدام `malloc`.
- **`newNode->data = data;`**: يتم تعيين القيمة المعطاة (`data`) إلى العقدة الجديدة.
- **`newNode->left = newNode->right = NULL;`**: يتم تعيين العقدة الجديدة إلى أن تكون عقدة ورقة (ليس لها عقد فرعية).
- **`return newNode;`**: يتم إرجاع العقدة الجديدة.

---

### 4. دالة `insert`
```c
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}
```
- **الهدف**: إضافة عقدة جديدة إلى الشجرة.
- **`if (root == NULL)`**: إذا كانت الشجرة فارغة، يتم إنشاء عقدة جديدة وإرجاعها.
- **`if (data < root->data)`**: إذا كانت القيمة المراد إدراجها أصغر من قيمة العقدة الحالية، يتم إدراجها في الفرع الأيسر.
- **`else if (data > root->data)`**: إذا كانت القيمة المراد إدراجها أكبر من قيمة العقدة الحالية، يتم إدراجها في الفرع الأيمن.
- **`return root;`**: يتم إرجاع العقدة الجذرية بعد الإدراج.

---

### 5. دالة `search`
```c
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
```
- **الهدف**: البحث عن قيمة معينة في الشجرة.
- **`if (root == NULL)`**: إذا وصلنا إلى نهاية الشجرة دون العثور على القيمة، يتم طباعة "Not Found".
- **`if (root->data == data)`**: إذا تم العثور على القيمة، يتم طباعة "Found".
- **`if (data < root->data)`**: إذا كانت القيمة المراد البحث عنها أصغر من قيمة العقدة الحالية، يتم البحث في الفرع الأيسر.
- **`else`**: إذا كانت القيمة المراد البحث عنها أكبر من قيمة العقدة الحالية، يتم البحث في الفرع الأيمن.

---

### 6. دالة `minValueNode`
```c
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}
```
- **الهدف**: العثور على العقدة ذات القيمة الأصغر في الشجرة.
- **`while (current && current->left != NULL)`**: يتم التنقل عبر الفروع اليسارية حتى نصل إلى العقدة الورقية اليسرى.
- **`return current;`**: يتم إرجاع العقدة التي تحتوي على القيمة الأصغر.

---

### 7. دالة `deleteNode`
```c
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
```
- **الهدف**: حذف عقدة معينة من الشجرة.
- **`if (root == NULL)`**: إذا كانت الشجرة فارغة، يتم إرجاعها كما هي.
- **`if (data < root->data)`**: إذا كانت القيمة المراد حذفها أصغر من قيمة العقدة الحالية، يتم البحث عنها في الفرع الأيسر.
- **`else if (data > root->data)`**: إذا كانت القيمة المراد حذفها أكبر من قيمة العقدة الحالية، يتم البحث عنها في الفرع الأيمن.
- **`else`**: إذا تم العثور على العقدة المراد حذفها:
  - **`if (root->left == NULL)`**: إذا كانت العقدة ليس لها فرع أيسر، يتم استبدالها بالفرع الأيمن.
  - **`else if (root->right == NULL)`**: إذا كانت العقدة ليس لها فرع أيمن، يتم استبدالها بالفرع الأيسر.
  - **`else`**: إذا كانت العقدة لها فرعين، يتم استبدالها بأصغر عقدة في الفرع الأيمن، ثم حذف هذه العقدة.

---

### 8. دالة `printInOrder`
```c
void printInOrder(struct Node* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->data);
        printInOrder(root->right);
    }
}
```
- **الهدف**: طباعة الشجرة بترتيب **In-Order** (الفرع الأيسر، الجذر، الفرع الأيمن).
- **`printInOrder(root->left);`**: يتم طباعة الفرع الأيسر.
- **`printf("%d ", root->data);`**: يتم طباعة قيمة العقدة الحالية.
- **`printInOrder(root->right);`**: يتم طباعة الفرع الأيمن.

---

### 9. دالة `printPreOrder`
```c
void printPreOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}
```
- **الهدف**: طباعة الشجرة بترتيب **Pre-Order** (الجذر، الفرع الأيسر، الفرع الأيمن).
- **`printf("%d ", root->data);`**: يتم طباعة قيمة العقدة الحالية.
- **`printPreOrder(root->left);`**: يتم طباعة الفرع الأيسر.
- **`printPreOrder(root->right);`**: يتم طباعة الفرع الأيمن.

---

### 10. دالة `printPostOrder`
```c
void printPostOrder(struct Node* root) {
    if (root != NULL) {
        printPostOrder(root->left);
        printPostOrder(root->right);
        printf("%d ", root->data);
    }
}
```
- **الهدف**: طباعة الشجرة بترتيب **Post-Order** (الفرع الأيسر، الفرع الأيمن، الجذر).
- **`printPostOrder(root->left);`**: يتم طباعة الفرع الأيسر.
- **`printPostOrder(root->right);`**: يتم طباعة الفرع الأيمن.
- **`printf("%d ", root->data);`**: يتم طباعة قيمة العقدة الحالية.

---

### 11. دالة `main`
```c
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
```
- **الهدف**: بدء تنفيذ البرنامج ومعالجة الأوامر.
- **`struct Node* root = NULL;`**: يتم تهيئة الجذر ليكون فارغًا.
- **`scanf("%d", &n);`**: يتم قراءة عدد العمليات من المستخدم.
- **`for (int i = 0; i < n; i++)`**: يتم تكرار العمليات المدخلة من المستخدم.
- **`if (strcmp(operation, "insert") == 0)`**: إذا كانت العملية هي `insert`، يتم قراءة القيمة وإدراجها في الشجرة.
- **`else if (strcmp(operation, "delete") == 0)`**: إذا كانت العملية هي `delete`، يتم قراءة القيمة وحذفها من الشجرة.
- **`else if (strcmp(operation, "search") == 0)`**: إذا كانت العملية هي `search`، يتم قراءة القيمة والبحث عنها في الشجرة.
- **`else if (strcmp(operation, "printInOrder") == 0)`**: إذا كانت العملية هي `printInOrder`، يتم طباعة الشجرة بترتيب In-Order.
- **`else if (strcmp(operation, "printPreOrder") == 0)`**: إذا كانت العملية هي `printPreOrder`، يتم طباعة الشجرة بترتيب Pre-Order.
- **`else if (strcmp(operation, "printPostOrder") == 0)`**: إذا كانت العملية هي `printPostOrder`، يتم طباعة الشجرة بترتيب Post-Order.

---

### ملخص الكود
هذا الكود يقوم بتنفيذ بنية بيانات **شجرة بحث ثنائية**، ويوفر العمليات الأساسية مثل إضافة عقدة إلى الشجرة (`insert`)، حذف عقدة من الشجرة (`delete`)، البحث عن قيمة في الشجرة (`search`)، وطباعة الشجرة بترتيبات مختلفة (In-Order, Pre-Order, Post-Order).
