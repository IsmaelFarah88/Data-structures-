هذا الكود يقوم بتحويل تعبير **متسلسل مركزي** (Infix) إلى تعبير **متسلسل خلفي** (Postfix)، ثم يقوم بتقييم التعبير المتسلسل الخلفي. يستخدم الكود بنية بيانات **المكدس** (Stack) لإدارة العمليات والأقواس أثناء التحويل والتقييم.

سنشرح الكود سطرًا بسطر ونفهم كل جزء منه بالتفصيل.

---

### 1. تضمين المكتبات
```c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
```
- **`#include <stdio.h>`**: هذه المكتبة تحتوي على الدوال الخاصة بالإدخال والإخراج، مثل `printf` و `scanf`.
- **`#include <stdlib.h>`**: هذه المكتبة تحتوي على الدوال الخاصة بتخصيص الذاكرة، مثل `malloc`.
- **`#include <ctype.h>`**: هذه المكتبة تحتوي على الدوال الخاصة بالتعامل مع الأحرف، مثل `isdigit`.
- **`#include <string.h>`**: هذه المكتبة تحتوي على الدوال الخاصة بالتعامل مع السلاسل النصية، مثل `strlen`.

---

### 2. تعريف الثوابت والهياكل
```c
#define MAX 100

typedef struct Stack {
    float data[MAX];
    int top;
} Stack;
```
- **`#define MAX 100`**: يحدد الحد الأقصى لعدد العناصر التي يمكن تخزينها في المكدس.
- **`typedef struct Stack`**: يعرّف نوع بيانات جديد يسمى `Stack`، وهو هيكل يمثل المكدس.
- **`float data[MAX];`**: يمثل المصفوفة التي ستُستخدم لتخزين عناصر المكدس.
- **`int top;`**: يمثل مؤشر العنصر العلوي (الأخير) في المكدس.

---

### 3. دالة `createStack`
```c
void createStack(Stack *s) {
    s->top = -1;
}
```
- **الهدف**: تهيئة المكدس.
- **`s->top = -1;`**: يتم تعيين مؤشر العنصر العلوي إلى `-1` للإشارة إلى أن المكدس فارغ.

---

### 4. دالة `isEmpty`
```c
int isEmpty(Stack *s) {
    return s->top == -1;
}
```
- **الهدف**: التحقق مما إذا كان المكدس فارغًا.
- **`return s->top == -1;`**: إذا كان مؤشر العنصر العلوي يساوي `-1`، فإن المكدس فارغ.

---

### 5. دالة `push`
```c
void push(Stack *s, float value) {
    s->data[++s->top] = value;
}
```
- **الهدف**: إضافة عنصر إلى المكدس.
- **`s->data[++s->top] = value;`**: يتم إضافة العنصر `value` إلى المكدس وزيادة مؤشر العنصر العلوي بمقدار 1.

---

### 6. دالة `pop`
```c
float pop(Stack *s) {
    return s->data[s->top--];
}
```
- **الهدف**: إزالة عنصر من المكدس.
- **`return s->data[s->top--];`**: يتم إرجاع العنصر العلوي في المكدس ثم إزالته بتقليل مؤشر العنصر العلوي بمقدار 1.

---

### 7. دالة `precedence`
```c
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
```
- **الهدف**: تحديد أولوية العمليات الحسابية.
- **`if (op == '+' || op == '-') return 1;`**: إذا كانت العملية هي `+` أو `-`، يتم إرجاع القيمة 1.
- **`if (op == '*' || op == '/') return 2;`**: إذا كانت العملية هي `*` أو `/`، يتم إرجاع القيمة 2.
- **`return 0;`**: إذا لم تكن العملية من العمليات الحسابية، يتم إرجاع القيمة 0.

---

### 8. دالة `infixToPostfix`
```c
void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    createStack(&s);
    int k = 0;
    for (int i = 0; infix[i]; i++) {
        if (isdigit(infix[i])) {
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';
            i--;
        } else if (infix[i] == '(') {
            push(&s, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(&s) && s.data[s.top] != '(')
                postfix[k++] = pop(&s);
            pop(&s);
        } else {
            while (!isEmpty(&s) && precedence(s.data[s.top]) >= precedence(infix[i]))
                postfix[k++] = pop(&s);
            push(&s, infix[i]);
        }
    }
    while (!isEmpty(&s))
        postfix[k++] = pop(&s);
    postfix[k] = '\0';
}
```
- **الهدف**: تحويل تعبير متسلسل مركزي إلى تعبير متسلسل خلفي.
- **`for (int i = 0; infix[i]; i++)`**: يتم التكرار عبر التعبير المتسلسل المركزي.
- **`if (isdigit(infix[i]))`**: إذا كان الحرف رقمًا، يتم نسخه إلى التعبير المتسلسل الخلفي.
- **`else if (infix[i] == '(')`**: إذا كان الحرف هو `(`، يتم إدخاله إلى المكدس.
- **`else if (infix[i] == ')')`**: إذا كان الحرف هو `)`، يتم إخراج العمليات من المكدس إلى التعبير المتسلسل الخلفي حتى يتم العثور على `(`.
- **`else`**: إذا كان الحرف عملية حسابية، يتم مقارنة أولويتها مع أولوية العمليات في المكدس وإخراجها إلى التعبير المتسلسل الخلفي إذا كانت أولويتها أقل.
- **`while (!isEmpty(&s))`**: يتم إخراج أي عمليات متبقية في المكدس إلى التعبير المتسلسل الخلفي.
- **`postfix[k] = '\0';`**: يتم إضافة نهاية السلسلة إلى التعبير المتسلسل الخلفي.

---

### 9. دالة `evaluatePostfix`
```c
float evaluatePostfix(char* postfix) {
    Stack s;
    createStack(&s);
    for (int i = 0; postfix[i]; i++) {
        if (isdigit(postfix[i])) {
            float num = 0;
            while (isdigit(postfix[i]) || postfix[i] == '.') {
                if (postfix[i] == '.') {
                    i++;
                    float decimal = 0.1;
                    while (isdigit(postfix[i])) {
                        num += (postfix[i++] - '0') * decimal;
                        decimal /= 10;
                    }
                } else {
                    num = num * 10 + (postfix[i++] - '0');
                }
            }
            push(&s, num);
        } else if (postfix[i] != ' ') {
            float val2 = pop(&s);
            float val1 = pop(&s);
            switch (postfix[i]) {
                case '+': push(&s, val1 + val2); break;
                case '-': push(&s, val1 - val2); break;
                case '*': push(&s, val1 * val2); break;
                case '/': push(&s, val1 / val2); break;
            }
        }
    }
    return pop(&s);
}
```
- **الهدف**: تقييم تعبير متسلسل خلفي.
- **`for (int i = 0; postfix[i]; i++)`**: يتم التكرار عبر التعبير المتسلسل الخلفي.
- **`if (isdigit(postfix[i]))`**: إذا كان الحرف رقمًا، يتم تحويله إلى رقم وإدخاله إلى المكدس.
- **`else if (postfix[i] != ' ')`**: إذا كان الحرف عملية حسابية، يتم إخراج أول رقمين من المكدس وتنفيذ العملية الحسابية ثم إدخال النتيجة إلى المكدس.
- **`return pop(&s);`**: يتم إرجاع النتيجة النهائية من المكدس.

---

### 10. دالة `main`
```c
int main() {
    char infix[MAX];
    fgets(infix, MAX, stdin);

    char postfix[MAX];
    infixToPostfix(infix, postfix);
    printf("%.2f\n", evaluatePostfix(postfix));

    return 0;
}
```
- **الهدف**: بدء تنفيذ البرنامج ومعالجة الأوامر.
- **`char infix[MAX];`**: يتم تعريف مصفوفة لتخزين التعبير المتسلسل المركزي.
- **`fgets(infix, MAX, stdin);`**: يتم قراءة التعبير المتسلسل المركزي من المستخدم.
- **`char postfix[MAX];`**: يتم تعريف مصفوفة لتخزين التعبير المتسلسل الخلفي.
- **`infixToPostfix(infix, postfix);`**: يتم تحويل التعبير المتسلسل المركزي إلى تعبير متسلسل خلفي.
- **`printf("%.2f\n", evaluatePostfix(postfix));`**: يتم تقييم التعبير المتسلسل الخلفي وطباعة النتيجة.

---

### ملخص الكود
هذا الكود يقوم بتحويل تعبير متسلسل مركزي إلى تعبير متسلسل خلفي باستخدام بنية بيانات المكدس، ثم يقوم بتقييم التعبير المتسلسل الخلفي. يتم استخدام المكدس لإدارة العمليات والأقواس أثناء التحويل والتقييم.
