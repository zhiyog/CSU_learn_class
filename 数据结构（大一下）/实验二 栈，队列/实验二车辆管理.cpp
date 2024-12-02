#define _CRT_SECURE_NO_WARNINGS 1
#define  Maxpart 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//定义车辆信息
typedef struct _carinfo
{
    char id[10]; //车牌号
    int hourCome; //到达时间，单位时，为了简便，这里只处理同一天内的时间
    int hourLeave; //离开时间，单位时
}Carinfo;
/*****************************************************定义顺序栈，栈，先进后出xqls*********************************/
typedef struct _Stack
{
    Carinfo* pcar;
    int maxlen;
    int front;
}Stack;
//初始化栈
void Stackinit(Stack* s,int size)
{
    s->maxlen = size;
    s->pcar = (Carinfo*)malloc(size * sizeof(Carinfo));
    s->front = 0;
}
//入栈
int Stackpush(Stack* s, Carinfo c)
{
    if (s->front >= s->maxlen)
        return 0;
    else
    {
        s->pcar[s->front] = c;
        s->front++;
        return s->front;
    }
}
//出栈
int Stackpop(Stack* s, Carinfo* e)
{
    if (s->front <= 0)
        return 0;
    else
    {
        s->front--;
        *e = s->pcar[s->front];
        return 1;
    }
}
//判断是否为空
int Stackempty(Stack s)
{
    if (s.front <= 0)
        return 1;
    else
        return 0;
}
//判断栈是否满
int StackFull(Stack s)
{
    if (s.front == s.maxlen)
        return 1;
    else
        return 0;
}
/*****************************************************定义链式队列，先进先出xqls*********************************/
typedef struct _node
{
    Carinfo car;
    struct _node* next;
}QueueNode,*Queue;
//初始化队列
Queue Queueinit()
{
    Queue head = (Queue)malloc(sizeof(QueueNode));
    head->next = 0;
    return head;
}
//入队
int Queuepush(Queue q, Carinfo c)
{
    Queue p = q;
    QueueNode* t = (QueueNode*)malloc(sizeof(QueueNode));
    int pos = 1;
    t->car = c;
    t->next = 0;
    while (p->next)
    {
        p = p->next;
        pos++;
    }
    p->next = t;
    return pos;
}
//出队
int Queuepop(Queue q, Carinfo* e)
{
    Queue p = q->next;
    if (q->next == 0)
        return 0;
    else
    {
        *e = p->car;
        q->next = p->next;
        free(p);
        p = 0;
        return 1;
    }
}
//判断是否为空
int Queueempty(Queue q)
{
    if (q->next == 0)
        return 1;
    else
        return 0;
}
//计算停车费xqls
double pay(int h1, int h2, double p)
{
    double out = (h2 - h1)  * p;
    return out;
}
 
int main()
{
    Stack parking; //停车场栈 xqls
    Stack tmp;   //临时栈 xqls
    Queue waiting; //等候队列 xqls
    //int n; //停车场最多停放的车辆数目
    char op; //操作
    int h,h1;
    int pos = 0;
    char id[10] = { 0 };
    double pay_perhour = 2; //每小时的停车费
    /*printf("请输入停车场最大的停车数量n：");
    scanf("%d", &n);*/
    //初始化
    Stackinit(&parking,Maxpart);
    Stackinit(&tmp,Maxpart);
    waiting = Queueinit();
    
    while (1)
    {
        printf("请输入操作：A.到达；D.离开；E.退出程序 : ");
        scanf(" %c", &op);
        if (op == 'D'&& Stackempty(parking))
        {
            printf("停车场目前暂无车辆\n");
            continue;
        }
        printf("请输入车牌号：");
        scanf("%s", id);
        //到达
        if (op == 'A')
        {
            printf("请输入到达时间：");
            scanf("%d", &h);
            Carinfo cc;
            strcpy(cc.id, id);
            cc.hourCome = h;
            if (StackFull(parking))
            {
                pos = Queuepush(waiting, cc);
                printf("便道位置：%d\n", pos);
            }
            else
            {
                pos = Stackpush(&parking, cc);
                printf("停车场位置：%d\n", pos);
            }
        }
        else if (op == 'D')
        {
            while (1)
            {
                //该车之后的先出栈，入临时栈
                Carinfo cc;
                Stackpop(&parking, &cc);
                if (strcmp(cc.id, id) == 0)
                {
                    printf("请输入离开时间：");
                    scanf("%d", &cc.hourLeave);
                    h1=cc.hourLeave;
                    printf("缴费：%.1f\n 停留时间：%d\n",pay(cc.hourCome, cc.hourLeave,  pay_perhour),cc.hourLeave-cc.hourCome);
                    break;
                }
                else
                {
                    Stackpush(&tmp, cc);
                    printf("    %s入临时栈\n", cc.id);
                }
            }
            //临时栈车辆返回
            while (!Stackempty(tmp))
            {
                Carinfo cc;
                Stackpop(&tmp, &cc);
                Stackpush(&parking, cc);
                printf("    %s返回停车场\n", cc.id);
            }
            //等待队列入栈
            if (!Queueempty(waiting))
            {
                Carinfo cc;
                Queuepop(waiting, &cc);
                    cc.hourCome=h1;
                pos = Stackpush(&parking, cc);
                printf("%s驶入停车场，位置：%d\n", cc.id,pos);
            }
 
        }
        else if (op == 'E'){
        scanf("%d");
         break;
		}
    }
    return 0;
}




