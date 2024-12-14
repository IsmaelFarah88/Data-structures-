هذا الكود يقوم بتنفيذ بنية بيانات **Deque** (Double-Ended Queue)، وهي نوع من أنواع الطوابير (Queues) التي تسمح بإضافة وحذف العناصر من طرفي الطابور (الأمام والخلف). يتم تنفيذ هذه البنية باستخدام مصفوفة دائرية (Circular Array) لتحسين استخدام الذاكرة.

سنشرح الكود سطرًا بسطر ونفهم كل جزء منه بالتفصيل.

---

### 1. تضمين المكتبات
```c
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
```
- **`#include <stdio.h>`**: هذه المكتبة تحتوي على الدوال الخاصة بالإدخال والإخراج، مثل `printf` و `scanf`.
- **`#include <stdbool.h>`**: هذه المكتبة تسمح باستخدام القيم المنطقية (`bool`).
- **`#include <string.h>`**: هذه المكتبة تحتوي على الدوال الخاصة بالتعامل مع السلاسل النصية، مثل `strcmp`.

---

### 2. تعريف الثوابت والمتغيرات
```c
#define MAX 5

int deque[MAX];
int front = -1, rear = -1;
```
- **`#define MAX 5`**: يحدد حجم الـ Deque بـ 5 عناصر.
- **`int deque[MAX];`**: يمثل المصفوفة التي ستُستخدم لتخزين عناصر الـ Deque.
- **`int front = -1, rear = -1;`**: يمثلان مؤشرات للعنصر الأول (`front`) والعنصر الأخير (`rear`) في الـ Deque. تم تهيئتهما بـ `-1` للإشارة إلى أن الـ Deque فارغة.

---

### 3. دالة `isFull`
```c
bool isFull() {
    return (front == (rear + 1) % MAX);
}
```
- **الهدف**: التحقق مما إذا كان الـ Deque ممتلئًا.
- **`return (front == (rear + 1) % MAX);`**: يتم التحقق من أن المؤشر `front` يساوي المؤشر `rear` بعد إضافة 1 (باستخدام الحساب الدائري `% MAX`). إذا تحقق هذا، فإن الـ Deque ممتلئ.

---

### 4. دالة `isEmpty`
```c
bool isEmpty() {
    return front == -1;
}
```
- **الهدف**: التحقق مما إذا كان الـ Deque فارغًا.
- **`return front == -1;`**: إذا كان المؤشر `front` يساوي `-1`، فإن الـ Deque فارغ.

---

### 5. دالة `insertFront`
```c
void insertFront(int x) {
    if (isFull()) {
        printf("Deque is full, cannot insert at front\n");
        return;
    }
    if (front == -1) {
        front = rear = 0;
    } else if (front == 0) {
        front = MAX - 1;
    } else {
        front--;
    }
    deque[front] = x;
    printf("Element %d inserted at front\n", x);
}
```
- **الهدف**: إضافة عنصر إلى بداية الـ Deque.
- **`if (isFull())`**: إذا كان الـ Deque ممتلئًا، يتم طباعة رسالة خطأ.
- **`if (front == -1)`**: إذا كان الـ Deque فارغًا، يتم تعيين `front` و `rear` إلى 0.
- **`else if (front == 0)`**: إذا كان المؤشر `front` في بداية المصفوفة، يتم نقله إلى نهاية المصفوفة (`MAX - 1`).
- **`else`**: إذا لم يكن المؤشر `front` في بداية المصفوفة، يتم نقله إلى اليسار بمقدار 1.
- **`deque[front] = x;`**: يتم إضافة العنصر `x` إلى الموضع الجديد للمؤشر `front`.

---

### 6. دالة `insertRear`
```c
void insertRear(int x) {
    if (isFull()) {
        printf("Deque is full, cannot insert at rear\n");
        return;
    }
    if (front == -1) {
        front = rear = 0;
    } else if (rear == MAX - 1) {
        rear = 0;
    } else {
        rear++;
    }
    deque[rear] = x;
    printf("Element %d inserted at rear\n", x);
}
```
- **الهدف**: إضافة عنصر إلى نهاية الـ Deque.
- **`if (isFull())`**: إذا كان الـ Deque ممتلئًا، يتم طباعة رسالة خطأ.
- **`if (front == -1)`**: إذا كان الـ Deque فارغًا، يتم تعيين `front` و `rear` إلى 0.
- **`else if (rear == MAX - 1)`**: إذا كان المؤشر `rear` في نهاية المصفوفة، يتم نقله إلى بداية المصفوفة (`0`).
- **`else`**: إذا لم يكن المؤشر `rear` في نهاية المصفوفة، يتم نقله إلى اليمين بمقدار 1.
- **`deque[rear] = x;`**: يتم إضافة العنصر `x` إلى الموضع الجديد للمؤشر `rear`.

---

### 7. دالة `deleteFront`
```c
void deleteFront() {
    if (isEmpty()) {
        printf("Deque is empty, cannot delete from front\n");
        return;
    }
    printf("Element %d removed from front\n", deque[front]);
    if (front == rear) {
        front = rear = -1;
    } else if (front == MAX - 1) {
        front = 0;
    } else {
        front++;
    }
}
```
- **الهدف**: حذف عنصر من بداية الـ Deque.
- **`if (isEmpty())`**: إذا كان الـ Deque فارغًا، يتم طباعة رسالة خطأ.
- **`printf("Element %d removed from front\n", deque[front]);`**: يتم طباعة العنصر الذي سيتم حذفه.
- **`if (front == rear)`**: إذا كان هناك عنصر واحد فقط في الـ Deque، يتم تعيين `front` و `rear` إلى `-1`.
- **`else if (front == MAX - 1)`**: إذا كان المؤشر `front` في نهاية المصفوفة، يتم نقله إلى بداية المصفوفة (`0`).
- **`else`**: إذا لم يكن المؤشر `front` في نهاية المصفوفة، يتم نقله إلى اليمين بمقدار 1.

---

### 8. دالة `deleteRear`
```c
void deleteRear() {
    if (isEmpty()) {
        printf("Deque is empty, cannot delete from rear\n");
        return;
    }
    printf("Element %d removed from rear\n", deque[rear]);
    if (front == rear) {
        front = rear = -1;
    } else if (rear == 0) {
        rear = MAX - 1;
    } else {
        rear--;
    }
}
```
- **الهدف**: حذف عنصر من نهاية الـ Deque.
- **`if (isEmpty())`**: إذا كان الـ Deque فارغًا، يتم طباعة رسالة خطأ.
- **`printf("Element %d removed from rear\n", deque[rear]);`**: يتم طباعة العنصر الذي سيتم حذفه.
- **`if (front == rear)`**: إذا كان هناك عنصر واحد فقط في الـ Deque، يتم تعيين `front` و `rear` إلى `-1`.
- **`else if (rear == 0)`**: إذا كان المؤشر `rear` في بداية المصفوفة، يتم نقله إلى نهاية المصفوفة (`MAX - 1`).
- **`else`**: إذا لم يكن المؤشر `rear` في بداية المصفوفة، يتم نقله إلى اليسار بمقدار 1.

---

### 9. دالة `getFront`
```c
void getFront() {
    if (isEmpty()) {
        printf("Deque is empty, no front element\n");
    } else {
        printf("Front element: %d\n", deque[front]);
    }
}
```
- **الهدف**: طباعة العنصر الموجود في بداية الـ Deque.
- **`if (isEmpty())`**: إذا كان الـ Deque فارغًا، يتم طباعة رسالة خطأ.
- **`printf("Front element: %d\n", deque[front]);`**: يتم طباعة العنصر الموجود في المؤشر `front`.

---

### 10. دالة `getRear`
```c
void getRear() {
    if (isEmpty()) {
        printf("Deque is empty, no rear element\n");
    } else {
        printf("Rear element: %d\n", deque[rear]);
    }
}
```
- **الهدف**: طباعة العنصر الموجود في نهاية الـ Deque.
- **`if (isEmpty())`**: إذا كان الـ Deque فارغًا، يتم طباعة رسالة خطأ.
- **`printf("Rear element: %d\n", deque[rear]);`**: يتم طباعة العنصر الموجود في المؤشر `rear`.

---

### 11. دالة `isFullCheck`
```c
void isFullCheck() {
    if (isFull()) {
        printf("Deque is full\n");
    } else {
        printf("Deque is not full\n");
    }
}
```
- **الهدف**: التحقق مما إذا كان الـ Deque ممتلئًا.
- **`if (isFull())`**: إذا كان الـ Deque ممتلئًا، يتم طباعة رسالة.
- **`else`**: إذا لم يكن الـ Deque ممتلئًا، يتم طباعة رسالة أخرى.

---

### 12. دالة `isEmptyCheck`
```c
void isEmptyCheck() {
    if (isEmpty()) {
        printf("Deque is empty\n");
    } else {
        printf("Deque is not empty\n");
    }
}
```
- **الهدف**: التحقق مما إذا كان الـ Deque فارغًا.
- **`if (isEmpty())`**: إذا كان الـ Deque فارغًا، يتم طباعة رسالة.
- **`else`**: إذا لم يكن الـ Deque فارغًا، يتم طباعة رسالة أخرى.

---

### 13. دالة `main`
```c
int main() {
    char command[20];
    int value;

    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "InsertFront") == 0) {
            scanf("%d", &value);
            insertFront(value);
        } else if (strcmp(command, "InsertRear") == 0) {
            scanf("%d", &value);
            insertRear(value);
        } else if (strcmp(command, "DeleteFront") == 0) {
            deleteFront();
        } else if (strcmp(command, "DeleteRear") == 0) {
            deleteRear();
        } else if (strcmp(command, "GetFront") == 0) {
            getFront();
        } else if (strcmp(command, "GetRear") == 0) {
            getRear();
        } else if (strcmp(command, "IsFull") == 0) {
            isFullCheck();
        } else if (strcmp(command, "IsEmpty") == 0) {
            isEmptyCheck();
        }
    }

    return 0;
}
```
- **الهدف**: بدء تنفيذ البرنامج ومعالجة الأوامر.
- **`while (scanf("%s", command) != EOF)`**: يتم قراءة الأوامر من المستخدم حتى نصل إلى نهاية الملف.
- **الشروط المختلفة**: يتم تنفيذ العمليات المناسبة بناءً على الأمر المدخل.

---

### ملخص الكود
هذا الكود يقوم بتنفيذ بنية بيانات **Deque** باستخدام مصفوفة دائرية، ويوفر العمليات الأساسية مثل إضافة عنصر إلى بداية أو نهاية الـ Deque، حذف عنصر من بداية أو نهاية الـ Deque، التحقق مما إذا كان الـ Deque ممتلئًا أو فارغًا، وطباعة العنصر الموجود في بداية أو نهاية الـ Deque.
