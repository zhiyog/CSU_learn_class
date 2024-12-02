//队列
# include <stdio.h>
# include <stdlib.h>
# define MaxSize 1000

typedef struct {
	int data[MaxSize];
	int front, rear;
} SqQueue;

void InitQueue(SqQueue *&q) {
	q = (SqQueue *)malloc(sizeof(SqQueue));
	q->front = q->rear = 0;
}

void DestroyQueue(SqQueue *&q) {
	free(q);
}

bool QueueEmpty(SqQueue *q) {
	return (q->front == q->rear);
}

bool enQueue(SqQueue *&q, int e) {
	if ((q->rear + 1) % MaxSize == q->front)
		return false;
	q->rear++;
	q->data[q->rear] = e;
	return true;
}

bool deQueue(SqQueue *&q, int &e) {
	if (q->front == q->rear)
		return false;
	q->front++;
	e = q->data[q->front];
	return true;
}

int QueueLength(SqQueue *q) {
	int len = 0, *p;
	for (int p = q->front; p != q->rear; p++) {
		len++;
	}
	return len;
}

/*1 2 3 4 5 6 7 8 9 10*/
int main() {
	SqQueue *s;
	InitQueue(s);
	int i, k;
	if (QueueEmpty(s))
		printf("队空\n");
	else
		printf("队不空\n");

	printf("请输入十个数用于测试：\n");
	for (int j = 0; j < 10; j++) {
		scanf("%d", &i);
		enQueue(s, i);
	}
	i = 0;
	if (QueueEmpty(s))
		printf("此时队空\n");
	else
		printf("此时队不空\n");
	int n;
	int len = QueueLength(s);
	printf("队长：%d", len);
	printf("\n需要出队元素个数（小于10）：");
	scanf("%d", &n);
	int g;
	for (int j = 1; j <= n; j++) {
		deQueue(s, g);
	}
	printf("此时队为：");
	for (int u = s->front + 1; u <= s->rear; u++) {
		printf("%d ", s->data[u]);
	}
	DestroyQueue(s);
	return 0;
}