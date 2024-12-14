
هذا الكود هو تطبيق لقائمة مرتبطة **مزدوجة** (Doubly Linked List)، وهي نوع من أنواع البيانات المتغيرة التي تسمح بالتنقل بين العقد بشكل أمامي وخلفي. القائمة المرتبطة المزدوجة تتكون من عقد (Nodes)، كل عقدة تحتوي على بيانات (data) ومؤشرين: واحد يشير إلى العقدة التالية (`next`) والآخر يشير إلى العقدة السابقة (`prev`).

سنشرح الكود سطرًا بسطر ونفهم كل جزء منه بالتفصيل.

---

### 1. تضمين المكتبات
```c
#include <stdio.h>
#include <stdlib.h>
```
- **`#include <stdio.h>`**: هذه المكتبة تحتوي على الدوال الخاصة بالإدخال والإخراج، مثل `printf` و `scanf`.
- **`#include <stdlib.h>`**: هذه المكتبة تحتوي على الدوال الخاصة بتخصيص الذاكرة، مثل `malloc`.

---

### 2. تعريف الهيكل `Node`
```c
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;
```
- **`typedef struct Node`**: هذا السطر يعرّف نوع بيانات جديد يسمى `Node`، وهو هيكل يمثل عقدة في القائمة المرتبطة.
- **`int data`**: يحتوي كل عقدة على بيانات (في هذه الحالة، عدد صحيح `int`).
- **`struct Node* next`**: يحتوي كل عقدة على مؤشر يشير إلى العقدة التالية في القائمة.
- **`struct Node* prev`**: يحتوي كل عقدة على مؤشر يشير إلى العقدة السابقة في القائمة.

---

### 3. دالة `add_to_head`
```c
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
```
- **الهدف**: إضافة عقدة جديدة إلى بداية القائمة.
- **`Node* new_node = (Node*)malloc(sizeof(Node));`**: يتم تخصيص ذاكرة لعقدة جديدة باستخدام `malloc`.
- **`new_node->data = value;`**: يتم تعيين القيمة المعطاة (`value`) إلى العقدة الجديدة.
- **`new_node->next = (*head);`**: يتم تعيين العقدة الجديدة إلى أن تكون العقدة الأولى في القائمة.
- **`new_node->prev = NULL;`**: يتم تعيين العقدة الجديدة إلى أن تكون العقدة الأولى، لذا ليس لها عقدة سابقة.
- **`if ((*head) != NULL)`**: إذا كانت القائمة ليست فارغة، يتم تحديث العقدة السابقة للعقدة الحالية الأولى لتشير إلى العقدة الجديدة.
- **`else *tail = new_node;`**: إذا كانت القائمة فارغة، يتم تعيين العقدة الجديدة إلى أن تكون العقدة الأخيرة أيضًا.
- **`*head = new_node;`**: يتم تحديث العقدة الأولى في القائمة لتكون العقدة الجديدة.

---

### 4. دالة `add_to_tail`
```c
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
```
- **الهدف**: إضافة عقدة جديدة إلى نهاية القائمة.
- **`Node* new_node = (Node*)malloc(sizeof(Node));`**: يتم تخصيص ذاكرة لعقدة جديدة.
- **`new_node->data = value;`**: يتم تعيين القيمة المعطاة إلى العقدة الجديدة.
- **`new_node->next = NULL;`**: يتم تعيين العقدة الجديدة إلى أن تكون العقدة الأخيرة، لذا ليس لها عقدة تالية.
- **`new_node->prev = *tail;`**: يتم تعيين العقدة الجديدة إلى أن تكون العقدة السابقة لها هي العقدة الحالية الأخيرة.
- **`if (*tail != NULL)`**: إذا كانت القائمة ليست فارغة، يتم تحديث العقدة التالية للعقدة الحالية الأخيرة لتشير إلى العقدة الجديدة.
- **`else *head = new_node;`**: إذا كانت القائمة فارغة، يتم تعيين العقدة الجديدة إلى أن تكون العقدة الأولى أيضًا.
- **`*tail = new_node;`**: يتم تحديث العقدة الأخيرة في القائمة لتكون العقدة الجديدة.

---

### 5. دالة `remove_head`
```c
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
```
- **الهدف**: إزالة العقدة الأولى من القائمة.
- **`if (*head == NULL)`**: إذا كانت القائمة فارغة، لا يتم إجراء أي شيء.
- **`Node* temp = *head;`**: يتم تخزين العقدة الأولى في متغير مؤقت.
- **`*head = (*head)->next;`**: يتم تحديث العقدة الأولى لتكون العقدة التالية.
- **`if (*head != NULL)`**: إذا كانت القائمة ليست فارغة بعد الإزالة، يتم تعيين العقدة السابقة للعقدة الجديدة الأولى إلى `NULL`.
- **`else *tail = NULL;`**: إذا كانت القائمة فارغة بعد الإزالة، يتم تعيين العقدة الأخيرة إلى `NULL`.
- **`free(temp);`**: يتم تحرير الذاكرة التي تم تخصيصها للعقدة المحذوفة.

---

### 6. دالة `remove_tail`
```c
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
```
- **الهدف**: إزالة العقدة الأخيرة من القائمة.
- **`if (*tail == NULL)`**: إذا كانت القائمة فارغة، لا يتم إجراء أي شيء.
- **`Node* temp = *tail;`**: يتم تخزين العقدة الأخيرة في متغير مؤقت.
- **`*tail = (*tail)->prev;`**: يتم تحديث العقدة الأخيرة لتكون العقدة السابقة.
- **`if (*tail != NULL)`**: إذا كانت القائمة ليست فارغة بعد الإزالة، يتم تعيين العقدة التالية للعقدة الجديدة الأخيرة إلى `NULL`.
- **`else *head = NULL;`**: إذا كانت القائمة فارغة بعد الإزالة، يتم تعيين العقدة الأولى إلى `NULL`.
- **`free(temp);`**: يتم تحرير الذاكرة التي تم تخصيصها للعقدة المحذوفة.

---

### 7. دالة `search`
```c
Node* search(Node* head, int value) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == value)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
```
- **الهدف**: البحث عن عقدة تحتوي على القيمة المحددة.
- **`Node* temp = head;`**: يتم بدء البحث من العقدة الأولى.
- **`while (temp != NULL)`**: يتم التكرار عبر القائمة حتى نصل إلى نهايتها.
- **`if (temp->data == value)`**: إذا تم العثور على القيمة، يتم إرجاع العقدة الحالية.
- **`return NULL;`**: إذا لم يتم العثور على القيمة، يتم إرجاع `NULL`.

---

### 8. دالة `print_list`
```c
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
```
- **الهدف**: طباعة القائمة بشكل أمامي وخلفي.
- **`Forward Traversal`**: يتم التنقل من العقدة الأولى إلى العقدة الأخيرة وطباعة البيانات.
- **`Backward Traversal`**: يتم التنقل من العقدة الأخيرة إلى العقدة الأولة وطباعة البيانات.

---

### 9. دالة `main`
```c
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
```
- **الهدف**: تنفيذ العمليات على القائمة المرتبطة بناءً على الأوامر المدخلة.
- **`Node* head = NULL;`**: يتم تهيئة العقدة الأولى لتكون `NULL`.
- **`Node* tail = NULL;`**: يتم تهيئة العقدة الأخيرة لتكون `NULL`.
- **`while (scanf("%s", command) != EOF)`**: يتم قراءة الأوامر من المستخدم حتى نصل إلى نهاية الملف.
- **الشروط المختلفة**: يتم تنفيذ العمليات المناسبة بناءً على الأمر المدخل.

---

### ملخص الكود
هذا الكود يقوم بإنشاء قائمة مرتبطة مزدوجة، ويوفر العمليات الأساسية مثل إضافة عقدة إلى البداية أو النهاية، إزالة عقدة من البداية أو النهاية، البحث عن عقدة، وطباعة القائمة.
