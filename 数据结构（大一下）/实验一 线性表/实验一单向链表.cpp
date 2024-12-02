# include <stdio.h>
# include <stdlib.h>
# define MaxSize 50
//链表

typedef struct LNode {
	int data;
	struct LNode *next;
} LinkNode;

void InitList(LinkNode *L) {
	L = (LinkNode *)malloc(sizeof(LinkNode));
	L->next = NULL;
} //初始化

void CreateListR(LinkNode *&L, int a[], int n) {
	LinkNode *s, *r;
	L = (LinkNode *)malloc(sizeof(LinkNode));
	r = L;
	for (int i = 0; i < n; i++) //插入数目
	{
		s = (LinkNode *)malloc(sizeof(LinkNode));//新结点
		s->data = a[i];//数据域
		r->next = s;
		r = s;
	}
	r->next = NULL;
}//使用头结点的尾插法


void DestroyList(LinkNode *L) {
	LinkNode *pre = NULL, *p = L->next;
	while (p != NULL) {
		free(pre);
		pre = p;
		p=p->next;
	}
	free(pre);
}//销毁线性表

void DispList(LinkNode *L) {
	LinkNode *p = L->next;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
} //输出

int GetElem(LinkNode *L, int i) {
	int e;
	int j;
	LinkNode *p = L;
	if (i <= 0)
		return 0;
	while (j < i && p != NULL) {
		j++;
		p = p->next;
	}
	if (p == NULL) {
		return 0;
	} else {
		e = p->data;
	}
	return e;
} //求某个元素值

int LocateElem(LinkNode *L, int e) {
	int i = 1;
	LinkNode *p = L->next;
	while (p != NULL && p->data != e) {
		p = p->next;
		i++;
	}
	if (p == NULL) {
		return 0;
	} else
		return i;
}//按元素值查找

bool ListInsert(LinkNode *L, int e, int i) {
	int j = 0;
	LinkNode *p = L, *s;
	if (i <= 0)
		return false;
	while (j < i - 1 && p != NULL) {
		j++;
		p = p->next;
	}
	if (p == NULL)
		return false;
	else {
		s = (LinkNode *)malloc(sizeof(LinkNode));
		s->data = e;
		s->next = p->next;
		p->next = s;
		return true;
	}
}//插入数据元素

bool ListDelete(LinkNode *L, int &e, int i) {
	int j = 0;
	LinkNode *p = L, *q;
	if (i <= 0)
		return false;
	while (j < i - 1 && p != NULL) {
		j++;
		p = p->next;
	}
	if (p == NULL)
		return false;
	else {
		q = p->next;
		if (q == NULL)
			return false;
		e = q->data;
		p->next = q->next;
		free(q);
		return true;
	}
}//删除数据元素

int main() {
	LinkNode *test;
	InitList(test);
	printf("索引菜单：\n");
	printf("            		1.尾插建立单链表\n");
	printf("			2.插入结点\n");
	printf("			3.删除结点\n");
	printf("			4.按元素值查找\n");
	printf("			5.求指定位置元素值\n");
	printf("			6.打印链表\n");
	printf("			7.销毁链表并退出\n");
	do {
		printf("请选择功能：\n");
		int i, j, k, s[MaxSize], t, a, b, c, d, e, f;
		scanf("%d", &i);
		switch (i) {
			case 1:
				printf("请输入单链表所需要的元素个数：\n");
				scanf("%d", &t);
				printf("请输入所有元素：\n");
				for (int u = 0; u < t; u++) {
					scanf("%d", &s[u]);
				}
				CreateListR(test, s, t);
				break;
			case 2:
				printf("请输入要插入的结点值以及位置：\n");
				scanf("%d%d", &j, &k);
				if (ListInsert(test, j, k))
					printf("完成\n");
				else
					printf("输入数据不符合要求\n");
				break;
			case 3:
				printf("请输入要删除的结点值以及位置：\n");
				scanf("%d%d", &a, &b);
				if (ListDelete(test, a, b))
					printf("完成\n");
				else
					printf("输入数据不符合要求\n");
				break;
			case 4:
				printf("请输入要查找的元素值:\n");
				scanf("%d", &c);
				d = LocateElem(test, c);
				printf("位置为：%d\n", d);
				break;
			case 5:
				printf("请输入元素所在位置：\n");
				scanf("%d", &f);
				e = GetElem(test, f);
				printf("元素值：%d\n", e);
				break;
			case 6:
				printf("线性表如下：\n");
				DispList(test);
				break;
			case 7:
				DestroyList(test);
				printf("销毁成功！");
				break;
		}
	} while (1);
	return 0;
}