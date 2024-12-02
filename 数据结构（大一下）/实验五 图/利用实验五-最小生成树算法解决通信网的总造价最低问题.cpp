#include<stdio.h>
#include<stdlib.h>

#define MaxVertices 100
#define INF 65535
int graph[MaxVertices][MaxVertices];
//建立边表
typedef struct node
{
	int adjvex;				//指向边表结点
	struct node *nextarc;	//指向下一条边，没有则为NULL
	int info;				//权值
}ArcNode;
//建立顶点表
typedef struct
{
	char data[MaxVertices];			//顶点数据
	ArcNode *firstarc;		//指向该顶点的第一个边表结点
}VerNode;
//建立图
typedef struct
{
	VerNode adjlist[MaxVertices];//顶点数组
	int n;						 //总顶点的个数
	int e;						 //总的边数
}ALGraph;

//建立邻接表
void CrateGraph(ALGraph *G)
{
	int i,j, k;
	int v1, v2;									//输入的两个边
	int weight;											//权值
	printf("请输入邻接表的总顶点数和边数：");
	scanf("%d %d", &G->n, &G->e);
	for (i = 1; i <= G->n; i++)				//prim最小生成树初始化
	{
		for (j = 1; j <= G->e; j++)
		{
			graph[i][j] = INF;
		}
	}
	fflush(stdin);
	printf("请输入顶点（回车结束一个输入）\n");
	for (i = 0; i < G->n; i++)
	{
		gets(G->adjlist[i].data);
		G->adjlist[i].firstarc = NULL;					//置头结点后第一条边为空 
	}
	printf("请根据顶点的位置从1开始输入两两相邻的边和权值(中间用空格隔开)\n");
	for (k = 0; k < G->e; k++)
	{
		fflush(stdin);//清空输入缓冲区 
		printf("第%d个连接点：", k + 1);
		scanf("%d %d %d", &v1, &v2, &weight);			//输入相邻的边和权值
		graph[v1][v2] = weight;
		graph[v2][v1] = weight;//类似于构造邻接矩阵 
		v1--; v2--;										//按顶点排序从1开始，减去1方便数组计算
		ArcNode *s = (ArcNode *)malloc(sizeof(ArcNode));
		s->info = weight;
		s->adjvex = v2;
		s->nextarc = G->adjlist[v1].firstarc;
		G->adjlist[v1].firstarc = s;//相当于利用邻接矩阵建立邻接表 
	}
}
//打印邻接表
void DisGraph(ALGraph *G)
{
	int i;
	printf("序号\t顶点名称\t\t边表\n");
	for (i = 0; i < G->n; i++)
	{
		printf("%d\t", i+1);						//打印序号
		printf("%s\t\t->", G->adjlist[i].data);		//打印顶点
		while (G->adjlist[i].firstarc)
		{
			printf("%d(%d)->", G->adjlist[i].firstarc->adjvex+1, G->adjlist[i].firstarc->info);
			G->adjlist[i].firstarc = G->adjlist[i].firstarc->nextarc;
		}
		printf("NULL\n");
	}
}
//prim最小生成树

int Prim(int graph[][MaxVertices], int n)
{
	int lowcost[MaxVertices], closest[MaxVertices];
	/*
	lowcost[i]记录以i为终点的边的最小权值，当lowcost[i]=0时表示终点i加入生成树
	closest[i]记录对应lowcost[i]的起点，当closest[i]=0时表示起点i加入生成树
	*/
	int i, j, min, minid, sum = 0;
	for (i = 2; i <= n; i++)				//默认选择1号节点加入生成树，从2号节点开始初始化
	{
		lowcost[i] = graph[1][i];			//最短距离初始化为其他节点到1号节点的距离
		closest[i] = 1;							//标记所有节点的起点皆为默认的1号节点
	}
	closest[1] = 0;								//标记1号节点加入生成树
	for (i = 2; i <= n; i++)				//n个节点至少需要n-1条边构成最小生成树
	{
		min = INF;
		for (j = 1; j <= n; j++)			 //找满足条件的最小权值边的节点minid
		{
			if (lowcost[j] < min && lowcost[j] != 0)  //边权值较小且不在生成树中
			{
				min = lowcost[j];
				minid = j;
			}
		}
		printf("边(%d,%d)的权为：%d\n", closest[minid], minid, min);  //输出生成树边的信息:起点，终点，权值
		sum += min;							//累加权值
		lowcost[minid] = 0;					//标记节点minid加入生成树

		for (j = 2; j <= n; j++)			//更新当前节点minid到其他节点的权值
		{
			if (graph[minid][j] < lowcost[j])  ///发现更小的权值
			{
				lowcost[j] = graph[minid][j];  //更新权值信息
				closest[j] = minid;				//更新最小权值边的起点
			}//改变U后，U到其他顶点的权值发生变化，进行更新 
		}
	}
	return sum;								//返回最小权值和
}

int main()
{
	ALGraph G;
	CrateGraph(&G);
	printf("\n");
	DisGraph(&G);
	printf("\n最小生成树的权值之和:%d\n", Prim(graph, G.n));
	return 0;
}
/*输入数据示例：
8 11
a
b
c
d
e
f
g
h
1 2 8
1 3 3
2 4 2
3 4 1
4 5 6
4 6 14
5 6 4
5 7 12
6 8 9
6 7 2
7 8 11*/
