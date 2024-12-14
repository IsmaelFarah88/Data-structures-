هذا الكود يقوم بتنفيذ خوارزمية **BFS (Breadth First Search)** للتنقل في جراف (Graph) ممثل كمصفوفة مجاورة (Adjacency Matrix). الخوارزمية BFS هي إحدى خوارزميات التنقل في الجرافات، وتعمل بالتنقل عرضيًا (أي تتابع الروابط على نفس المستوى قبل الانتقال إلى المستويات الأعمق).

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
#define MAX 100

struct Queue {
    int items[MAX];
    int front;
    int rear;
};

struct Graph {
    int numVertices;
    int adjMatrix[MAX][MAX];
};
```
- **`#define MAX 100`**: يحدد الحد الأقصى لعدد العقد (Vertices) في الجراف.
- **`struct Queue`**: يعرّف هيكلًا يمثل الطابور (Queue)، وهو بنية بيانات تُستخدم لتنفيذ خوارزمية BFS.
- **`struct Graph`**: يعرّف هيكلًا يمثل الجراف، ويحتوي على عدد العقد ومصفوفة المجاورة.

---

### 3. دالة `initQueue`
```c
void initQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}
```
- **الهدف**: تهيئة الطابور.
- **`q->front = -1;`**: يتم تعيين مؤشر العنصر الأول إلى `-1` للإشارة إلى أن الطابور فارغ.
- **`q->rear = -1;`**: يتم تعيين مؤشر العنصر الأخير إلى `-1` للإشارة إلى أن الطابور فارغ.

---

### 4. دالة `isEmpty`
```c
int isEmpty(struct Queue* q) {
    return q->front == -1;
}
```
- **الهدف**: التحقق مما إذا كان الطابور فارغًا.
- **`return q->front == -1;`**: إذا كان مؤشر العنصر الأول يساوي `-1`، فإن الطابور فارغ.

---

### 5. دالة `enqueue`
```c
void enqueue(struct Queue* q, int value) {
    if (q->rear == MAX - 1) return;
    if (isEmpty(q)) q->front = 0;
    q->items[++q->rear] = value;
}
```
- **الهدف**: إضافة عنصر إلى الطابور.
- **`if (q->rear == MAX - 1)`**: إذا كان الطابور ممتلئًا، يتم الخروج من الدالة.
- **`if (isEmpty(q)) q->front = 0;`**: إذا كان الطابور فارغًا، يتم تعيين مؤشر العنصر الأول إلى `0`.
- **`q->items[++q->rear] = value;`**: يتم إضافة العنصر `value` إلى الطابور وزيادة مؤشر العنصر الأخير بمقدار 1.

---

### 6. دالة `dequeue`
```c
int dequeue(struct Queue* q) {
    if (isEmpty(q)) return -1;
    int item = q->items[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}
```
- **الهدف**: إزالة عنصر من الطابور.
- **`if (isEmpty(q)) return -1;`**: إذا كان الطابور فارغًا، يتم إرجاع `-1`.
- **`int item = q->items[q->front];`**: يتم تخزين العنصر الذي سيتم حذفه.
- **`if (q->front == q->rear)`**: إذا كان هناك عنصر واحد فقط في الطابور، يتم تعيين مؤشرات العنصر الأول والأخير إلى `-1`.
- **`else q->front++;`**: إذا كان هناك أكثر من عنصر واحد، يتم زيادة مؤشر العنصر الأول بمقدار 1.
- **`return item;`**: يتم إرجاع العنصر الذي تم حذفه.

---

### 7. دالة `createGraph`
```c
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
    
    return graph;
}
```
- **الهدف**: إنشاء جراف جديد.
- **`struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));`**: يتم تخصيص ذاكرة للجراف.
- **`graph->numVertices = vertices;`**: يتم تعيين عدد العقد في الجراف.
- **`for (int i = 0; i < vertices; i++)`**: يتم تهيئة مصفوفة المجاورة بالقيمة `0`.
- **`return graph;`**: يتم إرجاع الجراف الجديد.

---

### 8. دالة `addEdge`
```c
void addEdge(struct Graph* graph, int u, int v) {
    graph->adjMatrix[u][v] = 1;
    graph->adjMatrix[v][u] = 1;
}
```
- **الهدف**: إضافة حافة (Edge) بين عقدتين في الجراف.
- **`graph->adjMatrix[u][v] = 1;`**: يتم تعيين القيمة `1` في مصفوفة المجاورة للإشارة إلى وجود حافة بين العقدة `u` والعقدة `v`.
- **`graph->adjMatrix[v][u] = 1;`**: يتم تعيين القيمة `1` في مصفوفة المجاورة للإشارة إلى وجود حافة بين العقدة `v` والعقدة `u`.

---

### 9. دالة `bfs`
```c
void bfs(struct Graph* graph, int startVertex) {
    int visited[MAX] = {0};
    struct Queue q;
    initQueue(&q);

    visited[startVertex] = 1;
    enqueue(&q, startVertex);

    while (!isEmpty(&q)) {
        int currentVertex = dequeue(&q);
        printf("%d ", currentVertex);

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
    }
}
```
- **الهدف**: تنفيذ خوارزمية BFS للتنقل في الجراف.
- **`int visited[MAX] = {0};`**: يتم تهيئة مصفوفة لتتبع العقد التي تمت زيارتها.
- **`struct Queue q;`**: يتم إنشاء طابور لتنفيذ خوارزمية BFS.
- **`initQueue(&q);`**: يتم تهيئة الطابور.
- **`visited[startVertex] = 1;`**: يتم تحديث المصفوفة `visited` لتشير إلى أن العقدة البدئية تمت زيارتها.
- **`enqueue(&q, startVertex);`**: يتم إضافة العقدة البدئية إلى الطابور.
- **`while (!isEmpty(&q))`**: يتم التكرار حتى يصبح الطابور فارغًا.
- **`int currentVertex = dequeue(&q);`**: يتم إزالة العقدة الحالية من الطابور.
- **`printf("%d ", currentVertex);`**: يتم طباعة العقدة الحالية.
- **`for (int i = 0; i < graph->numVertices; i++)`**: يتم التكرار عبر جميع العقد في الجراف.
- **`if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i])`**: إذا كانت هناك حافة بين العقدة `currentVertex` والعقدة `i`، ولم تتم زيارة العقدة `i`، يتم تحديث المصفوفة `visited` وإضافة العقدة `i` إلى الطابور.

---

### 10. دالة `main`
```c
int main() {
    int inputVertices, numEdges, u, v;
    int maxVertex = -1;

    scanf("%d %d", &inputVertices, &numEdges);
    
    struct Graph* graph = createGraph(MAX);

    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);

        if (u > maxVertex) maxVertex = u;
        if (v > maxVertex) maxVertex = v;
    }

    graph->numVertices = maxVertex + 1;
    
    bfs(graph, 0);

    free(graph);
    return 0;
}
```
- **الهدف**: بدء تنفيذ البرنامج ومعالجة الأوامر.
- **`scanf("%d %d", &inputVertices, &numEdges);`**: يتم قراءة عدد العقد وعدد الحواف من المستخدم.
- **`struct Graph* graph = createGraph(MAX);`**: يتم إنشاء جراف جديد.
- **`for (int i = 0; i < numEdges; i++)`**: يتم قراءة الحواف من المستخدم وتحديث مصفوفة المجاورة.
- **`if (u > maxVertex) maxVertex = u;`**: يتم تحديث العقدة الأكبر في الجراف.
- **`if (v > maxVertex) maxVertex = v;`**: يتم تحديث العقدة الأكبر في الجراف.
- **`graph->numVertices = maxVertex + 1;`**: يتم تحديث عدد العقد في الجراف.
- **`bfs(graph, 0);`**: يتم بدء تنفيذ خوارزمية BFS من العقدة `0`.
- **`free(graph);`**: يتم تحرير الذاكرة التي تم تخصيصها للجراف.

---

### ملخص الكود
هذا الكود يقوم بتنفيذ خوارزمية **BFS** للتنقل في جراف ممثل كمصفوفة مجاورة. يتم استخدام الطابور لتنفيذ الخوارزمية، ويتم التنقل عرضيًا (أي تتابع الروابط على نفس المستوى قبل الانتقال إلى المستويات الأعمق).
