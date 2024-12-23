هذا الكود يقوم بتنفيذ خوارزمية **DFS (Depth First Search)** للتنقل في جراف (Graph) ممثل كمصفوفة مجاورة (Adjacency Matrix). الخوارزمية DFS هي إحدى خوارزميات التنقل في الجرافات، وتعمل بالتنقل عميقًا (أي تتابع الروابط إلى أقصى عمق ممكن قبل العودة إلى العقد الأخرى).

سنشرح الكود سطرًا بسطر ونفهم كل جزء منه بالتفصيل.

---

### 1. تضمين المكتبات
```c
#include <stdio.h>
#include <stdbool.h>
```
- **`#include <stdio.h>`**: هذه المكتبة تحتوي على الدوال الخاصة بالإدخال والإخراج، مثل `printf` و `scanf`.
- **`#include <stdbool.h>`**: هذه المكتبة تسمح باستخدام القيم المنطقية (`bool`).

---

### 2. تعريف الثوابت والمتغيرات
```c
#define MAX 100

int adjMatrix[MAX][MAX];
bool visited[MAX];
int numVertices;
```
- **`#define MAX 100`**: يحدد الحد الأقصى لعدد العقد (Vertices) في الجراف.
- **`int adjMatrix[MAX][MAX];`**: يمثل مصفوفة المجاورة التي ستُستخدم لتخزين الجراف.
- **`bool visited[MAX];`**: يمثل مصفوفة منطقية تُستخدم لتتبع العقد التي تمت زيارتها.
- **`int numVertices;`**: يمثل عدد العقد في الجراف.

---

### 3. دالة `dfs`
```c
void dfs(int vertex) {
    printf("%d ", vertex);
    visited[vertex] = true;

    for (int i = 0; i < numVertices; i++) {
        if (adjMatrix[vertex][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}
```
- **الهدف**: تنفيذ خوارزمية DFS للتنقل في الجراف.
- **`printf("%d ", vertex);`**: يتم طباعة العقدة الحالية التي تمت زيارتها.
- **`visited[vertex] = true;`**: يتم تحديث المصفوفة `visited` لتشير إلى أن العقدة الحالية تمت زيارتها.
- **`for (int i = 0; i < numVertices; i++)`**: يتم التكرار عبر جميع العقد في الجراف.
- **`if (adjMatrix[vertex][i] == 1 && !visited[i])`**: إذا كانت هناك حافة (Edge) بين العقدة `vertex` والعقدة `i`، ولم تتم زيارة العقدة `i`، يتم استدعاء دالة `dfs` مرة أخرى للعقدة `i`.

---

### 4. دالة `main`
```c
int main() {
    int numEdges, u, v;

    scanf("%d %d", &numVertices, &numEdges);

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            adjMatrix[i][j] = 0;
        }
        visited[i] = false;
    }

    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d", &u, &v);
        adjMatrix[u][v] = 1;
    }

    dfs(0);

    return 0;
}
```
- **الهدف**: بدء تنفيذ البرنامج ومعالجة الأوامر.
- **`scanf("%d %d", &numVertices, &numEdges);`**: يتم قراءة عدد العقد وعدد الحواف من المستخدم.
- **`for (int i = 0; i < numVertices; i++)`**: يتم تهيئة مصفوفة المجاورة بالقيمة `0` ومصفوفة `visited` بالقيمة `false`.
- **`for (int i = 0; i < numEdges; i++)`**: يتم قراءة الحواف من المستخدم وتحديث مصفوفة المجاورة.
- **`dfs(0);`**: يتم بدء تنفيذ خوارزمية DFS من العقدة `0`.

---

### ملخص الكود
هذا الكود يقوم بتنفيذ خوارزمية **DFS** للتنقل في جراف ممثل كمصفوفة مجاورة. يتم استخدام مصفوفة المجاورة لتخزين الجراف، ومصفوفة منطقية لتتبع العقد التي تمت زيارتها. الخوارزمية تبدأ من عقدة محددة (في هذه الحالة، العقدة `0`) وتتابع الروابط إلى أقصى عمق ممكن قبل العودة إلى العقد الأخرى.
