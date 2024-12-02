//图的建立和遍历
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*顶点数，边数：5 8
  行数：5 
测试矩阵：0 1 0 1 1
			1 0 1 1 0
			0 1 0 1 1
			1 1 1 0 1
			1 0 1 1 0*/ 
#define MAXV 100 
#define INF 9999
#define MaxSize 100
typedef struct ANode{
	int adjvex;//邻接点
	struct ANode *nextarc;//指向下一个的指针 
	int weight; //权值 
}ArcNode;//边结点 
typedef struct VNode{
	int data;//顶点值 
	ArcNode *firstarc;//指向第一个边结点 
}VNode;//头结点 
typedef struct{
	VNode adjlist[MAXV];//邻接表的头结点数组
	int n,e;//顶点数n和边数e 
}AdjGraph;//完整的图邻接表类型  
typedef struct {
	int data[MaxSize];
	int front, rear;
} SqQueue;

void InitQueue(SqQueue *&q) {
	q = (SqQueue *)malloc(sizeof(SqQueue));
	q->front = q->rear = 0;
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

void CreatAdj(AdjGraph*& G,int A[MAXV][MAXV],int n,int e){
	int i,j;ArcNode *p;
	G = (AdjGraph*)malloc(sizeof(AdjGraph));
	for(i=0;i<n;i++)
		G->adjlist[i].firstarc = NULL;
	for(i=0;i<n;i++)
		for(j=n-1;j>=0;j--)//遍历邻接矩阵
			if(A[i][j]!=0&&A[i][j]!=INF){
				p = (ArcNode*)malloc(sizeof(ArcNode));//创立边结点 
				p->adjvex = j;
				p->weight = A[i][j];
				p->nextarc = G->adjlist[i].firstarc;//头插法
				G->adjlist[i].firstarc = p; 
			}
	G->n = n;
	G->e = e; 
}
int visited1[MAXV]={0};
void DFS(AdjGraph* G,int v){//深度优先遍历 
	ArcNode *p;
	visited1[v] = 1;//标记已被访问的顶点 
	printf("%d ",v);//输出已被访问顶点的编号 
	p = G->adjlist[v].firstarc;
	while(p!=NULL){
		if(visited1[p->adjvex]==0){
			DFS(G,p->adjvex);
		}
		p = p->nextarc; 
	}
}
int visited[MAXV] = {0};
void BFS(AdjGraph *G,int v){//广度优先 遍历 
	int w,i;
	ArcNode *p;
	SqQueue *qu;
	InitQueue(qu);
	int visted[MAXV];
	for(i=0;i<G->n;i++)
		visited[i] = 0;//访问标记数组初始化 
	printf("%d ",v);//输出被访问顶点的编号 
	visited[v] = 1;//标记已被访问的顶点 
	enQueue(qu,v);
	while(!QueueEmpty(qu)){
		deQueue(qu,w);//出队一个顶点
		p = G->adjlist[w].firstarc;//指向第一个边结点
		while(p!=NULL){
			if(visited[p->adjvex]==0){
				printf("%d ",p->adjvex);
				visited[p->adjvex] = 1;
				enQueue(qu,p->adjvex);//访问后该顶点进队 
			}
			p = p->nextarc;
		} 
	}
	printf("\n");
}

void printDgraph(AdjGraph *G)
{
    int i;ArcNode *p;
    for(i=0;i<G->n;i++){
    	p = G->adjlist[i].firstarc;
    	printf("%3d: ",i);
    	while(p!=NULL){
    		printf("%3d[%d]->",p->adjvex,p->weight);
    		p = p->nextarc;
		}
		printf("Λ\n");
	}
}

void welcome()//打印选择界面
{
    printf("\t\t\t\t\t╔════════════════════════════════╗\n");
    printf("\t\t\t\t\t║             MENU               ║\n");
    printf("\t\t\t\t\t║════════════════════════════════║\n");
    printf("\t\t\t\t\t║         1--Create Graph        ║\n");
    printf("\t\t\t\t\t║════════════════════════════════║\n");
    printf("\t\t\t\t\t║         2--DFS    Graph        ║\n");
    printf("\t\t\t\t\t║════════════════════════════════║\n");
    printf("\t\t\t\t\t║         3--BFS    Graph        ║\n");
    printf("\t\t\t\t\t║════════════════════════════════║\n");
    printf("\t\t\t\t\t║         0--Exit                ║\n");
    printf("\t\t\t\t\t╚════════════════════════════════╝\n");
    printf("请输入你的选择:\n");
}
int main(){
	AdjGraph *g;
	int A[MAXV][MAXV];
	int n,e,choice,row;
	int a,b;
	while(1){
		welcome();
		scanf("%d",&choice);
		switch(choice){
		case 1:
			system("cls");
			printf("请输入图的顶点数和边数：");
			scanf("%d%d",&n,&e);
			printf("请输入邻接矩阵的行数：");
			scanf("%d",&row);
			printf("输入矩阵的元素值：(9999视为无穷大)\n");
			for(int i=0;i<row;i++)
				for(int j=0;j<row;j++)
					scanf("%d",&A[i][j]);
			CreatAdj(g,A,n,e);
			printf("建立成功！图如下：\n");
			printDgraph(g);
			break;
		case 2:
			system("cls");
			printf("请输入指定的搜索点：");
			scanf("%d",&a);
			printf("深搜结果如下：\n");
			DFS(g,a);
			for(int i=0;i<MAXV;i++) visited1[i] = 0;
			break;
		case 3:
			system("cls");
			printf("请输入指定的搜索点：");
			scanf("%d",&b);
			printf("广搜结果如下：\n");
			BFS(g,b);
			for(int i=0;i<MAXV;i++) visited[i] = 0;
			break;
		case 0:exit(1);
		default:printf("输入有误！");break;
		}
	}	
	return 0;
}
