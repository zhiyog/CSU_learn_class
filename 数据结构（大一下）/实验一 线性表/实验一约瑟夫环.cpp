#include<stdio.h>
#include<stdlib.h>
typedef struct lnode
{
    int num;//序号
    int password;//密码
    int sign;//是否已出表的标志
    struct lnode *next;
}lnode, *linklist;
 
lnode *create(int n)
{
    lnode *head,*p,*z;
    head=(lnode *)malloc(sizeof(lnode));
    z=head;
    for(int i=1;i<=n;i++)
    {
        p=(lnode *)malloc(sizeof(lnode));
        p->num=i;//赋编号
        printf("第%d个人手中的密码为：",i);
        scanf("%d",&(p->password));//赋密码
        p->sign=1;//赋标志，初始为1，可读，若为0，则跳过，表示已出表
        p->next=z->next;//添加的p结点的指针勾连到head的指针
        z->next=p;//head的指针指向p
        z=p;//尾结点变更
    }//n个人
    z->next=head;
    return head;
}
 
void run(lnode *head,int n,int m)
{
    lnode *p;
    int i;
    p=head;
    while(n>=1)
    {
        i=1;
        while(i<=m)
        {
            p=p->next;//后移一位
            if(p->sign==1)i++;//标志为1，读
        }
        printf("%d ",p->num);
        m=p->password;//获得新的m值
        p->sign=0;//出列后，赋0，不读
        n--;
    }
}
 
int main()
{
    int n,m;//n个人，数到m的人出局
    linklist head;
    printf("共有几个人：n=");
    scanf("%d",&n);
    if(n<=0)printf("n的数值存在问题！");
    printf("初始报数上限值：m=");
    scanf("%d",&m);
    if(m<=0)printf("n的数值存在问题！");
    head=NULL;
    head=create(n);
    printf("出列顺序：");
    run(head,n,m);
    printf("\n");
    return 0;
}