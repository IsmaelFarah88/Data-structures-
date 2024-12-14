هذا الكود يقوم بتنفيذ بنية بيانات **المصفوفة الدائرية** (Circular Array)، وهي بنية بيانات تُستخدم لتنفيذ الطوابير (Queues) بشكل فعال. المصفوفة الدائرية تسمح باستخدام المصفوفة بشكل دائري، مما يعني أنه عندما يصل المؤشر `rear` إلى نهاية المصفوفة، يمكنه العودة إلى البداية.

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

### 2. تعريف الثوابت والهياكل
```c
#define MAX_SIZE 5

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} CircularArray;
```
- **`#define MAX_SIZE 5`**: يحدد الحد الأقصى لعدد العناصر التي يمكن تخزينها في المصفوفة الدائرية.
- **`typedef struct`**: يعرّف نوع بيانات جديد يسمى `CircularArray`، وهو هيكل يمثل المصفوفة الدائرية.
- **`int items[MAX_SIZE];`**: يمثل المصفوفة التي ستُستخدم لتخزين عناصر المصفوفة الدائرية.
- **`int front;`**: يمثل مؤشر العنصر الأول (الأمامي) في المصفوفة الدائرية.
- **`int rear;`**: يمثل مؤشر العنصر الأخير (الخلفي) في المصفوفة الدائرية.

---

### 3. دالة `init`
```c
void init(CircularArray* arr) {
    arr->front = -1;
    arr->rear = -1;
}
```
- **الهدف**: تهيئة المصفوفة الدائرية.
- **`arr->front = -1;`**: يتم تعيين مؤشر العنصر الأول إلى `-1` للإشارة إلى أن المصفوفة الدائرية فارغة.
- **`arr->rear = -1;`**: يتم تعيين مؤشر العنصر الأخير إلى `-1` للإشارة إلى أن المصفوفة الدائرية فارغة.

---

### 4. دالة `isFull`
```c
int isFull(CircularArray* arr) {
    return (arr->front == (arr->rear + 1) % MAX_SIZE);
}
```
- **الهدف**: التحقق مما إذا كانت المصفوفة الدائرية ممتلئة.
- **`return (arr->front == (arr->rear + 1) % MAX_SIZE);`**: إذا كان مؤشر العنصر الأول يساوي المؤشر الأخير بعد إضافة 1 (باستخدام الحساب الدائري `% MAX_SIZE`)، فإن المصفوفة الدائرية ممتلئة.

---

### 5. دالة `isEmpty`
```c
int isEmpty(CircularArray* arr) {
    return (arr->front == -1);
}
```
- **الهدف**: التحقق مما إذا كانت المصفوفة الدائرية فارغة.
- **`return (arr->front == -1);`**: إذا كان مؤشر العنصر الأول يساوي `-1`، فإن المصفوفة الدائرية فارغة.

---

### 6. دالة `insert`
```c
void insert(CircularArray* arr, int value) {
    if (isFull(arr)) {
        printf("Array is full, cannot insert %d\n", value);
        return;
    }
    if (isEmpty(arr)) {
        arr->front = 0;
    }
    arr->rear = (arr->rear + 1) % MAX_SIZE;
    arr->items[arr->rear] = value;
}
```
- **الهدف**: إضافة عنصر إلى المصفوفة الدائرية.
- **`if (isFull(arr))`**: إذا كانت المصفوفة الدائرية ممتلئة، يتم طباعة رسالة خطأ.
- **`if (isEmpty(arr))`**: إذا كانت المصفوفة الدائرية فارغة، يتم تعيين مؤشر العنصر الأول إلى `0`.
- **`arr->rear = (arr->rear + 1) % MAX_SIZE;`**: يتم تحديث مؤشر العنصر الأخير باستخدام الحساب الدائري.
- **`arr->items[arr->rear] = value;`**: يتم إضافة العنصر `value` إلى المصفوفة الدائرية.

---

### 7. دالة `delete`
```c
int delete(CircularArray* arr) {
    if (isEmpty(arr)) {
        printf("Array is empty, cannot delete\n");
        return -1;
    }
    int deletedItem = arr->items[arr->front];
    if (arr->front == arr->rear) {
        arr->front = -1;
        arr->rear = -1;
    } else {
        arr->front = (arr->front + 1) % MAX_SIZE;
    }
    return deletedItem;
}
```
- **الهدف**: حذف عنصر من المصفوفة الدائرية.
- **`if (isEmpty(arr))`**: إذا كانت المصفوفة الدائرية فارغة، يتم طباعة رسالة خطأ.
- **`int deletedItem = arr->items[arr->front];`**: يتم تخزين العنصر الذي سيتم حذفه.
- **`if (arr->front == arr->rear)`**: إذا كان هناك عنصر واحد فقط في المصفوفة الدائرية، يتم تعيين مؤشرات العنصر الأول والأخير إلى `-1`.
- **`else`**: إذا كان هناك أكثر من عنصر واحد، يتم تحديث مؤشر العنصر الأول باستخدام الحساب الدائري.
- **`return deletedItem;`**: يتم إرجاع العنصر الذي تم حذفه.

---

### 8. دالة `display`
```c
void display(CircularArray* arr) {
    if (isEmpty(arr)) {
        printf("Circular Array is empty\n");
        return;
    }
    int i = arr->front;
    printf("Final contents of Circular Array:\n");
    while (1) {
        printf("%d ", arr->items[i]);
        if (i == arr->rear) break;
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}
```
- **الهدف**: طباعة محتويات المصفوفة الدائرية.
- **`if (isEmpty(arr))`**: إذا كانت المصفوفة الدائرية فارغة، يتم طباعة رسالة خطأ.
- **`int i = arr->front;`**: يتم بدء الطباعة من مؤشر العنصر الأول.
- **`while (1)`**: يتم التكرار عبر المصفوفة الدائرية.
- **`printf("%d ", arr->items[i]);`**: يتم طباعة العنصر الحالي.
- **`if (i == arr->rear) break;`**: إذا تم الوصول إلى مؤشر العنصر الأخير، يتم إنهاء التكرار.
- **`i = (i + 1) % MAX_SIZE;`**: يتم تحديث المؤشر باستخدام الحساب الدائري.

---

### 9. دالة `main`
```c
int main() {
    CircularArray arr;
    init(&arr);
    int operationsCount;

    scanf("%d", &operationsCount);

    for (int i = 0; i < operationsCount; i++) {
        char operation;
        int value;
        scanf(" %c", &operation);

        if (operation == 'I') {
            scanf("%d", &value);
            insert(&arr, value);
        } else if (operation == 'D') {
            int deleted = delete(&arr);
            if (deleted != -1) {
                printf("Deleted element: %d\n", deleted);
            }
        }
    }

    display(&arr);
    return 0;
}
```
- **الهدف**: بدء تنفيذ البرنامج ومعالجة الأوامر.
- **`CircularArray arr;`**: يتم إنشاء مصفوفة دائرية.
- **`init(&arr);`**: يتم تهيئة المصفوفة الدائرية.
- **`scanf("%d", &operationsCount);`**: يتم قراءة عدد العمليات من المستخدم.
- **`for (int i = 0; i < operationsCount; i++)`**: يتم تكرار العمليات المدخلة من المستخدم.
- **`if (operation == 'I')`**: إذا كانت العملية هي `I`، يتم قراءة القيمة وإضافتها إلى المصفوفة الدائرية.
- **`else if (operation == 'D')`**: إذا كانت العملية هي `D`، يتم حذف العنصر الأول من المصفوفة الدائرية وطباعته.
- **`display(&arr);`**: يتم طباعة محتويات المصفوفة الدائرية بعد اكتمال العمليات.

---

### ملخص الكود
هذا الكود يقوم بتنفيذ بنية بيانات **المصفوفة الدائرية**، وهي بنية بيانات تُستخدم لتنفيذ الطوابير بشكل فعال. يوفر العمليات الأساسية مثل إضافة عنصر إلى المصفوفة الدائرية (`insert`)، حذف عنصر من المصفوفة الدائرية (`delete`)، وطباعة محتويات المصفوفة الدائرية (`display`). يتم التحكم في المصفوفة الدائرية باستخدام مؤشرين: `front` و `rear`.
