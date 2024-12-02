#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//二叉树结构体 
typedef struct BiTreeNode
{
    char data;
    int deep; 
    struct BiTreeNode *lchild;
    struct BiTreeNode *rchild;
}BiTreeNode,*BiTree;
//先序方式建立二叉树,深度来控制横向为位置

void CreateBiTree(BiTree *T,int d) 
{
    char ch;
    scanf("%c",&ch);
    
    if(ch == ' ')
        (*T)= NULL;  //此节点为空 
 
    else
    {
        (*T) = (BiTree)malloc(sizeof(BiTreeNode));
        (*T)->data = ch;
        (*T)->deep = d;
        CreateBiTree(&((*T)->lchild),d+1);//遍历到孩子节点，深度加一 
        CreateBiTree(&((*T)->rchild),d+1);
    }
}

void InOrderOpposite(BiTree T,void (*print)(BiTree T))
{
    if(T==NULL)
        return;
    InOrderOpposite(T->rchild,print);
    print(T);
    InOrderOpposite(T->lchild,print);
}

//使用中序遍历来打印树，采用“右根左”的遍历顺序输出

void print(BiTree t)        
{
	int i;
	for(i = 0;i <= t->deep;i++)
	{
		printf("   ");//叶子在最右侧
	}

	printf("%c",t->data);
	printf("\n");
}


int main()
{
	BiTree T;	
	T = (BiTree)malloc(sizeof(BiTree));
	
	printf("输入需要打印的二叉树：\n");
	CreateBiTree(&T,0);
	if(!T)
	  printf("树空\n");
	else
	   InOrderOpposite(T,print);
	   
	return 0;
}