هذا الكود هو تطبيق لقائمة مرتبطة **أحادية** (Singly Linked List)، وهي نوع من أنواع البيانات المتغيرة التي تسمح بالتنقل بين العقد بشكل أمامي فقط. القائمة المرتبطة الأحادية تتكون من عقد (Nodes)، كل عقدة تحتوي على بيانات (data) ومؤشر يشير إلى العقدة التالية (`next`).

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
    struct Node* next;
};
```
- **`struct Node`**: هذا السطر يعرّف هيكلًا يمثل عقدة في القائمة المرتبطة.
- **`int data`**: يحتوي كل عقدة على بيانات (في هذه الحالة، عدد صحيح `int`).
- **`struct Node* next`**: يحتوي كل عقدة على مؤشر يشير إلى العقدة التالية في القائمة.

---

### 3. تعريف الهيكل `LinkedList`
```c
struct LinkedList {
    struct Node* head;
    struct Node* tail;
};
```
- **`struct LinkedList`**: هذا السطر يعرّف هيكلًا يمثل القائمة المرتبطة بأكملها.
- **`struct Node* head`**: يشير إلى العقدة الأولى في القائمة.
- **`struct Node* tail`**: يشير إلى العقدة الأخيرة في القائمة.

---

### 4. دالة `createNode`
```c
struct Node* createNode(int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    return new_node;
}
```
- **الهدف**: إنشاء عقدة جديدة.
- **`struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));`**: يتم تخصيص ذاكرة لعقدة جديدة باستخدام `malloc`.
- **`new_node->data = new_data;`**: يتم تعيين القيمة المعطاة (`new_data`) إلى العقدة الجديدة.
- **`new_node->next = NULL;`**: يتم تعيين العقدة الجديدة إلى أن تكون العقدة الأخيرة، لذا ليس لها عقدة تالية.
- **`return new_node;`**: يتم إرجاع العقدة الجديدة.

---

### 5. دالة `addToHead`
```c
void addToHead(struct LinkedList* list, int new_data) {
    struct Node* new_node = createNode(new_data);
    new_node->next = list->head;
    list->head = new_node;
    if (list->tail == NULL) {
        list->tail = new_node;
    }
}
```
- **الهدف**: إضافة عقدة جديدة إلى بداية القائمة.
- **`struct Node* new_node = createNode(new_data);`**: يتم إنشاء عقدة جديدة.
- **`new_node->next = list->head;`**: يتم تعيين العقدة الجديدة إلى أن تكون العقدة الأولى في القائمة.
- **`list->head = new_node;`**: يتم تحديث العقدة الأولى في القائمة لتكون العقدة الجديدة.
- **`if (list->tail == NULL)`**: إذا كانت القائمة فارغة، يتم تعيين العقدة الجديدة إلى أن تكون العقدة الأخيرة أيضًا.

---

### 6. دالة `removeFromHead`
```c
void removeFromHead(struct LinkedList* list) {
    if (list->head == NULL) return;
    struct Node* temp = list->head;
    list->head = list->head->next;
    if (list->head == NULL) {
        list->tail = NULL;
    }
    free(temp);
}
```
- **الهدف**: إزالة العقدة الأولى من القائمة.
- **`if (list->head == NULL)`**: إذا كانت القائمة فارغة، لا يتم إجراء أي شيء.
- **`struct Node* temp = list->head;`**: يتم تخزين العقدة الأولى في متغير مؤقت.
- **`list->head = list->head->next;`**: يتم تحديث العقدة الأولى لتكون العقدة التالية.
- **`if (list->head == NULL)`**: إذا كانت القائمة فارغة بعد الإزالة، يتم تعيين العقدة الأخيرة إلى `NULL`.
- **`free(temp);`**: يتم تحرير الذاكرة التي تم تخصيصها للعقدة المحذوفة.

---

### 7. دالة `addToTail`
```c
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
```
- **الهدف**: إضافة عقدة جديدة إلى نهاية القائمة.
- **`struct Node* new_node = createNode(new_data);`**: يتم إنشاء عقدة جديدة.
- **`if (list->head == NULL)`**: إذا كانت القائمة فارغة، يتم تعيين العقدة الجديدة إلى أن تكون العقدة الأولى والأخيرة.
- **`else`**: إذا كانت القائمة ليست فارغة، يتم إضافة العقدة الجديدة إلى نهاية القائمة.

---

### 8. دالة `removeFromTail`
```c
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
```
- **الهدف**: إزالة العقدة الأخيرة من القائمة.
- **`if (list->head == NULL)`**: إذا كانت القائمة فارغة، لا يتم إجراء أي شيء.
- **`if (list->head == list->tail)`**: إذا كانت القائمة تحتوي على عقدة واحدة فقط، يتم إزالتها.
- **`while (temp->next != list->tail)`**: يتم التنقل عبر القائمة حتى نصل إلى العقدة قبل الأخيرة.
- **`free(list->tail);`**: يتم تحرير الذاكرة التي تم تخصيصها للعقدة الأخيرة.
- **`list->tail = temp;`**: يتم تحديث العقدة الأخيرة لتكون العقدة السابقة.

---

### 9. دالة `addAtPosition`
```c
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
```
- **الهدف**: إضافة عقدة جديدة في موضع محدد.
- **`if (position == 0)`**: إذا كان الموضع هو البداية، يتم استدعاء دالة `addToHead`.
- **`for (int i = 0; i < position - 1 && temp != NULL; i++)`**: يتم التنقل عبر القائمة حتى نصل إلى الموضع المحدد.
- **`if (temp == NULL)`**: إذا كان الموضع غير صالح، يتم تحرير العقدة الجديدة والخروج.
- **`new_node->next = temp->next;`**: يتم تعيين العقدة الجديدة إلى أن تكون العقدة التالية للعقدة الحالية.
- **`temp->next = new_node;`**: يتم تعيين العقدة الجديدة إلى أن تكون العقدة التالية للعقدة السابقة.

---

### 10. دالة `removeAtPosition`
```c
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
```
- **الهدف**: إزالة عقدة من موضع محدد.
- **`if (position == 0)`**: إذا كان الموضع هو البداية، يتم استدعاء دالة `removeFromHead`.
- **`for (int i = 0; i < position && temp != NULL; i++)`**: يتم التنقل عبر القائمة حتى نصل إلى الموضع المحدد.
- **`prev->next = temp->next;`**: يتم تحرير العقدة المحددة.
- **`if (temp == list->tail)`**: إذا كانت العقدة المحذوفة هي العقدة الأخيرة، يتم تحديث العقدة الأخيرة.

---

### 11. دالة `search`
```c
int search(struct Node* head, int value) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == value) return 1;
        temp = temp->next;
    }
    return 0;
}
```
- **الهدف**: البحث عن قيمة معينة في القائمة.
- **`while (temp != NULL)`**: يتم التنقل عبر القائمة حتى نصل إلى نهايتها.
- **`if (temp->data == value)`**: إذا تم العثور على القيمة، يتم إرجاع `1`.
- **`return 0;`**: إذا لم يتم العثور على القيمة، يتم إرجاع `0`.

---

### 12. دالة `edit`
```c
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
```
- **الهدف**: تعديل قيمة عقدة معينة.
- **`while (temp != NULL)`**: يتم التنقل عبر القائمة حتى نصل إلى نهايتها.
- **`if (temp->data == old_value)`**: إذا تم العثور على القيمة القديمة، يتم تحديثها إلى القيمة الجديدة.

---

### 13. دالة `printList`
```c
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}
```
- **الهدف**: طباعة القائمة.
- **`while (node != NULL)`**: يتم التنقل عبر القائمة حتى نصل إلى نهايتها.
- **`printf("%d -> ", node->data);`**: يتم طباعة قيمة كل عقدة.
- **`printf("NULL\n");`**: يتم طباعة `NULL` للإشارة إلى نهاية القائمة.

---

### 14. دالة `processCommands`
```c
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
```
- **الهدف**: معالجة الأوامر المدخلة من المستخدم.
- **`struct LinkedList list = {NULL, NULL};`**: يتم تهيئة القائمة المرتبطة.
- **`while (scanf("%s", command) != EOF)`**: يتم قراءة الأوامر من المستخدم حتى نصل إلى نهاية الملف.
- **الشروط المختلفة**: يتم تنفيذ العمليات المناسبة بناءً على الأمر المدخل.

---

### 15. دالة `main`
```c
int main() {
    processCommands();
    return 0;
}
```
- **الهدف**: بدء تنفيذ البرنامج.
- **`processCommands();`**: يتم استدعاء دالة معالجة الأوامر.

---

### ملخص الكود
هذا الكود يقوم بإنشاء قائمة مرتبطة أحادية، ويوفر العمليات الأساسية مثل إضافة عقدة إلى البداية أو النهاية، إزالة عقدة من البداية أو النهاية، إضافة عقدة في موضع محدد، إزالة عقدة من موضع محدد، البحث عن قيمة، تعديل قيمة عقدة، وطباعة القائمة.
