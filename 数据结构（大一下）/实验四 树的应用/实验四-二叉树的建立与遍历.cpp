#include <stdio.h>
#include <stdlib.h>

//输入示例（ABC  DE G  F   ）


typedef struct BiTreeNode
{
    char data;
    struct BiTreeNode *lchild;
    struct BiTreeNode *rchild;
}BiTreeNode,*BiTree;//
void CreateBiTree(BiTree *T) 
{
    char ch;
    scanf("%c",&ch);//数据
 
    if(ch == ' ')
        (*T)= NULL;  //此节点为空 
 
    else
    {
        (*T) = (BiTree)malloc(sizeof(BiTreeNode));
        (*T)->data = ch;
        CreateBiTree(&((*T)->lchild));
        CreateBiTree(&((*T)->rchild));
    }
}
//先序方式递归建立二叉树 
 

void PreOrder(BiTree T)
{
    if(T==NULL)
        return;
    printf("%c ",T->data);
    PreOrder(T->lchild);
    PreOrder(T->rchild);
}
//先序遍历并打印 

void InOrder(BiTree T)
{
    if(T==NULL)
        return;
    InOrder(T->lchild);
    printf("%c ",T->data);
    InOrder(T->rchild);
} 
//中序遍历并打印 

void PostOrder(BiTree T)
{
    if(T==NULL)
        return;
    PostOrder(T->lchild);
    PostOrder(T->rchild);
    printf("%c ",T->data);
}
//后序遍历并打印 


int main()
{
    BiTree T;
    T = (BiTree)malloc(sizeof(BiTreeNode));//分配空间
 
    printf("请给二叉树按照先序方式依次输入结点的值(空结点为' '):\n");
    CreateBiTree(&T); 
 
    printf("先序方式遍历结果：\n");
    PreOrder(T);
    printf("\n");
 
    printf("中序方式遍历结果：\n");
    InOrder(T);
    printf("\n");
 
    printf("后序方式遍历结果：\n");
    PostOrder(T);
    printf("\n");
    
    return 0;
}