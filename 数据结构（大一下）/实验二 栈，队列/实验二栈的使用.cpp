//栈的各种操作实现
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define MaxSize 100

typedef struct {
	int data[MaxSize];
	int top;
} SqStack;

void InitStack(SqStack *&s) {
	s = (SqStack *)malloc(sizeof(SqStack));
	s->top = -1;
}

void DestroyStack(SqStack *&s) {
	free(s);
}

bool StackEmpty(SqStack *&s) {
	return (s->top == -1);
}

bool Push(SqStack *&s, int &e) {
	if (s->top == MaxSize - 1)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

bool Pop(SqStack *&s, int &e) {
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	s->top--;
	return true;
}

bool GetTop(SqStack *s, int &e) {
	if (s->top == -1)
		return false;
	e = s->data[s->top];
	return true;
}

int StackLength(SqStack *s) {
	return s->top + 1;
}

int main() {
	SqStack *s;
	InitStack(s);
	int i, k;
	if (StackEmpty(s))
		printf("栈空\n");
	else
		printf("栈不空\n");

	printf("请输入十个数用于测试：\n");
	for (int j = 0; j < 10; j++) {
		scanf("%d", &i);
		Push(s, i);
	}
	i = 0;
	if (StackEmpty(s))
		printf("此时栈空\n");
	else
		printf("此时栈不空\n");

	if (GetTop(s, k))
		printf("栈顶元素：%d\n", k);
	else
		printf("出现错误\n");

	int n;
	int len = StackLength(s);
	printf("栈长：%d", len);
	printf("\n需要出栈元素个数（小于10）：");
	scanf("%d", &n);
	int g;
	for (int j = 1; j <= n; j++) {
		Pop(s, g);
	}
	printf("此时栈为：");
	for (int i = s->top ; i >= 0; i--) {
		printf("%d ", s->data[i]);
	}
	DestroyStack(s);
	return 0;
} 1