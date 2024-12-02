#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100

typedef struct {
	char data[MaxSize];
	int top;
} SqStack;

void InitStack(SqStack *s) {
	s->top = -1;
}

bool StackEmpty(SqStack *s) {
	return (s->top == -1);
}

bool Push(SqStack *s, char e) {
	if (s->top == MaxSize - 1)
		return false;
	s->top++;
	s->data[s->top] = e;
	return true;
}

bool Pop(SqStack *s, char *e) {
	if (s->top == -1)
		return false;
	*e = s->data[s->top];
	s->top--;
	return true;
}

bool March(SqStack *s, char *str) {
	InitStack(s);
	char e;
	int i = 0;
	while (str[i] != '\0') {
		switch (str[i]) {
			case '(':
				Push(s, '(');
				break;
			case '{':
				Push(s, '{');
				break;
			case '[':
				Push(s, '[');
				break;
			case ')':
				Pop(s, &e);
				if (e != '(')
					return 0;
				break;
			case '}':
				Pop(s, &e);
				if (e != '{')
					return 0;
				break;
			case ']':
				Pop(s, &e);
				if (e != '[')
					return 0;
				break;
			default:
				break;

		}
		i++;
	}
	int h = StackEmpty(s);
	if (h == 0)
		return 0;
	else
		return 1;
}
int main() {
	SqStack s;
	char str[MaxSize];
	printf("请输入你要收入的字符串：");
	scanf("%s", str);
	bool h = March(&s, str);
	if (h == 0)
		printf("括号不匹配");
	else
		printf("括号匹配");
	return 0;
}