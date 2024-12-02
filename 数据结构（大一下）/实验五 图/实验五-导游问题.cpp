#include<stdio.h>
#include<stdlib.h>
#define UNVISITED 0
#define VISITED 1
#define INFINITY INT_MAX
#define UNSELECTED 0
#define SELECTED 1

typedef struct
{
    int symbol;//景点代号
    const char *name;//景点名字
    const char *introduction;//景点简介
}spot;          //景点类型

typedef struct
{
    spot v,w;   //边的端点
    int info;   //对带权图，为权值，此处为距离
}ArcInfo;   //存储边信息

typedef struct
{
    spot *vexs;  //顶点数组，spot是景点类型
    int **arcs;  //关系数组，此图为带权图，则为权值或INFINITY
    int n,e;     //顶点数和边数
    int *tags;   //标志数组，可用于在图的遍历中标记顶点访问与否
}MGraph;

typedef struct
{
    int prev;   //当前最短路径上该顶点的前驱顶点的位序
    int lowcost;//当前最短路径的长度
}DistInfo;//V-U中定点的当前最短路径信息


int LocateVex(MGraph G,spot v)//找顶点位置 
{
    int i;
    for(i=0;i<G.n;i++)
        if(v.symbol==G.vexs[i].symbol) return i;
    return -1;
}

int  InitGraph(MGraph &G,spot *vexs,int n)
{
    //初始化含n个顶点且无边的图G
    int i,j,info;
    if(n<0||(n>0&&vexs==NULL)) return 0;
    info=INFINITY;  //带权图
    G.n = n;
    G.e = 0;  //顶点数和边数
    if(G.n==0) return 1;   //空图
    if((G.vexs=(spot*)malloc(n*sizeof(spot)))==NULL) return 0;
    for(i=0;i<G.n;i++) G.vexs[i]=vexs[i];
    if((G.arcs=(int **)malloc(n*sizeof(int*)))==NULL) //分配指针数组
        return 0;
    for(i=0;i<n;i++) //分配每个指针所指向的数组
        if((G.arcs[i]=(int*)malloc(n*sizeof(int)))==NULL)
            return 0;
    if((G.tags=(int*)malloc(n*sizeof(int)))==NULL) return 0;
    for(i=0;i<n;i++){   //初始化标志数组和关系数组
        G.tags[i]=UNVISITED;
        for(j=0;j<n;j++) G.arcs[i][j]=info;
    }
    return 1;
}

int  CreateGraph(MGraph &G,spot *vexs,int n,ArcInfo *arcs,int e)
{
    //创建含n个顶点和e条边的无向带权图图G，vexs为顶点信息，arcs为边信息
    if(n<0||e<0||(n>0&&vexs==NULL)||(e>0&&arcs==NULL)) return 0;
    int i,j,k;
    spot v,w;
    if(InitGraph(G,vexs,n)!=1) return 0;    //初始化
    G.e = e;//边数
    for(k=0;k<G.e;k++){//建立关系数组
        v=arcs[k].v; w=arcs[k].w;   //读入边(v,w)
        i=LocateVex(G,v);j=LocateVex(G,w);//确定v和w在顶点数组中的位序i和j
        if(i<0||j<0) return 0;
        G.arcs[i][j]=G.arcs[j][i]=arcs[k].info;
    }
    return 1;
}

int FirstAdjVex(MGraph G,int k)
{//求图G中k顶点的第一个邻接顶点的位序
    int i;
    if(k<0||k>=G.n) return -1;
    for(i=0;i<G.n;i++){//查找第一个值非零且非INFINITY的元素
        if(G.arcs[k][i]!=0&&G.arcs[k][i]!=INFINITY) return i;
    }
    return -1;//k顶点无邻接顶点
}

int NextAdjVex(MGraph G,int k,int m)
{
    //m顶点为k顶点的邻接顶点，求图中k顶点相对于m顶点的下一个邻接顶点的位序
    int i;
    if(k<0||k>=G.n||m<0||m>=G.n) return 0;
    for(i=m+1;i<G.n;i++)
        if(G.arcs[k][i]!=0&&G.arcs[k][i]!=INFINITY)
            return i;
    return -1;
}

int  visit(int k,MGraph G)
{
    //访问结点信息（读取景点信息）
    if(k<0||k>=G.n) return 0;
    printf("景点序号：%d\n",G.vexs[k].symbol);
    printf("景点名字：%s\n",G.vexs[k].name);
    printf("景点简介：%s\n",G.vexs[k].introduction);
    return 1;
}


int Dijkstra(MGraph G,int i,DistInfo* &Dist)
{
    //求图G中从i顶点到其他所有顶点的最短路径，并由Dist返回
    //迪杰斯特拉算法
    int j,m,k,min,p;
    Dist = (DistInfo*)malloc(G.n*sizeof(DistInfo));
    for(j=0;j<G.n;j++){
        //初始化
        Dist[j].lowcost = INFINITY;
        G.tags[j] = UNSELECTED;
    }
    for(j=0;j<G.n;j++){
        //源点i引出的所有弧的信息存入Dist
        if(G.arcs[i][j]!=INFINITY){
            Dist[j].prev=i;
            Dist[j].lowcost=G.arcs[i][j];
        }
    }
    Dist[i].prev=-1;Dist[i].lowcost=0;//源点i信息存入Dist
    G.tags[i]=SELECTED;//初始集合U仅含源点i

    for(m=1;m<G.n;m++){ //按路径长度升序，依次求源点到其他定点的最短路径
        min=INFINITY;k=0;
        for(j=0;j<G.n;j++)
            {
            if(UNSELECTED==G.tags[j]&&Dist[j].lowcost<min)
            {
                k=j;
                min=Dist[k].lowcost;        //此处求得在V-U集合中的最短路径
            }
        }
        G.tags[k]=SELECTED; //将k顶点加入集合U
        for(p=FirstAdjVex(G,k);p>=0;p=NextAdjVex(G,k,p)){    //更新Dist数组，这里做了一个简单优化，不用从0开始循环 
            if(UNSELECTED==G.tags[p]&&Dist[k].lowcost+G.arcs[k][p]<Dist[p].lowcost){
                Dist[p].lowcost = Dist[k].lowcost+G.arcs[k][p];     //k点的邻接点中距离最小的点p
                Dist[p].prev=k;
            }
        }
    }
    return 1;
}

void Dispath(MGraph G,DistInfo *Dist,int k)
{
    //沿Dist数组的prev域，可递归获得源点到k定点的最短路径
    if(k==-1) return ;
    Dispath(G,Dist,Dist[k].prev);//逆向递归获得路径上的顶点
    printf("%d.%s  ",G.vexs[k].symbol,G.vexs[k].name);    //正向输出当前路径上的顶点
}



void initdata(spot *vexs,ArcInfo *arcs)
{

    vexs[0].symbol=1;
    vexs[0].name="大门";
    vexs[0].introduction="公园的正门，雄伟壮观的大理石做的门，体现了公园的宏伟壮观";

    vexs[1].symbol=2;
    vexs[1].name="荷花池";
    vexs[1].introduction="一到夏日，满池的荷花鲜艳绽放";

    vexs[2].symbol=3;
    vexs[2].name="九曲桥";
    vexs[2].introduction="九曲桥蜿蜒在荷花池中央，游客可在桥上近距离赏花";

    vexs[3].symbol=4;
    vexs[3].name="湖中亭";
    vexs[3].introduction="建在荷花池中央，便于游客停下休息";

    vexs[4].symbol=5;
    vexs[4].name="游乐场";
    vexs[4].introduction="各种游乐设施齐全，可供游客尽情玩耍，释放自我";

    vexs[5].symbol=6;
    vexs[5].name="纪念塔";
    vexs[5].introduction="这是纪念红军的纪念塔，满含红色革命精神";

    vexs[6].symbol=7;
    vexs[6].name="观景台";
    vexs[6].introduction="观景台是地势公园最高的地方，在此，可以鸟瞰到整个公园的风景";

    vexs[7].symbol=8;
    vexs[7].name="餐厅";
    vexs[7].introduction="餐厅内有各种食物，可为游客解渴充饥";

    vexs[8].symbol=9;
    vexs[8].name="休息区";
    vexs[8].introduction="配备房间，游客累了能在此休息";

    vexs[9].symbol=10;
    vexs[9].name="自行车道";
    vexs[9].introduction="有各种款式的自行车，也有专门的自行车道，方便1骑行";

    vexs[10].symbol=11;
    vexs[10].name="游船港";
    vexs[10].introduction="有双人、多人复古风游船，能让游客尽情地享受水上的快乐时光";

    //边信息
    arcs[0].v=vexs[0];
    arcs[0].w=vexs[1];
    arcs[0].info=1;

    arcs[1].v=vexs[1];
    arcs[1].w=vexs[2];
    arcs[1].info=3;

    arcs[2].v=vexs[1];
    arcs[2].w=vexs[3];
    arcs[2].info=4;

    arcs[3].v=vexs[2];
    arcs[3].w=vexs[3];
    arcs[3].info=6;

    arcs[4].v=vexs[3];
    arcs[4].w=vexs[4];
    arcs[4].info=1;

    arcs[5].v=vexs[1];
    arcs[5].w=vexs[5];
    arcs[5].info=4;

    arcs[6].v=vexs[2];
    arcs[6].w=vexs[5];
    arcs[6].info=4;

    arcs[7].v=vexs[3];
    arcs[7].w=vexs[5];
    arcs[7].info=5;

    arcs[8].v=vexs[3];
    arcs[8].w=vexs[6];
    arcs[8].info=6;

    arcs[9].v=vexs[2];
    arcs[9].w=vexs[7];
    arcs[9].info=7;

    arcs[10].v=vexs[5];
    arcs[10].w=vexs[6];
    arcs[10].info=9;

    arcs[11].v=vexs[5];
    arcs[11].w=vexs[7];
    arcs[11].info=6;

    arcs[12].v=vexs[5];
    arcs[12].w=vexs[8];
    arcs[12].info=4;

    arcs[13].v=vexs[5];
    arcs[13].w=vexs[9];
    arcs[13].info=6;

    arcs[14].v=vexs[3];
    arcs[14].w=vexs[9];
    arcs[14].info=7;

    arcs[15].v=vexs[6];
    arcs[15].w=vexs[10];
    arcs[15].info=3;

    arcs[16].v=vexs[7];
    arcs[16].w=vexs[8];
    arcs[16].info=4;

    arcs[17].v=vexs[8];
    arcs[17].w=vexs[9];
    arcs[17].info=5;

    arcs[18].v=vexs[9];
    arcs[18].w=vexs[10];
    arcs[18].info=5;

}

void welcom()
{
    printf("\t\t\t\t\t\t╔════════════════════════════════╗\n");
    printf("\t\t\t\t\t\t║         公园导游系统           ║\n");
    printf("\t\t\t\t\t\t║════════════════════════════════║\n");
    printf("\t\t\t\t\t\t║         1-查看景点信息         ║\n");
    printf("\t\t\t\t\t\t║════════════════════════════════║\n");
    printf("\t\t\t\t\t\t║         2-查看两景点间最短路径 ║\n");
    printf("\t\t\t\t\t\t║════════════════════════════════║\n");
    printf("\t\t\t\t\t\t║         3-退出系统             ║\n");
    printf("\t\t\t\t\t\t╚════════════════════════════════╝\n");

}

void spotList()
{
    printf("\t\t\t\t\t\t***********景点列表************     \n");
    printf("\t\t\t\t\t   ------------------------------------------\n");
    printf("\t\t\t\t\t   1.大门     2.荷花池    3.九曲桥   4.湖中亭\n");
    printf("\t\t\t\t\t   5.游乐场   6.纪念塔    7.观景台   8.餐厅 \n");
    printf("\t\t\t\t\t   9.休息区   10.自行车道 11.游船港        \n");
    printf("\t\t\t\t\t   ------------------------------------------\n");

}


int main()
{
    int n=11,e=19,sum=0,flag=0;
    spot *vexs;
    ArcInfo *arcs;
    int *path;      //用于存储路径
    int length;     //当前路径长度
    int choice=INFINITY,i,j;
    vexs=(spot*)malloc(n*sizeof(spot));         //分配空间
    arcs=(ArcInfo*)malloc(e*sizeof(ArcInfo));
    path=(int*)malloc(e*sizeof(int));
    length=0;
    MGraph G;
    DistInfo *Dist; //定义数组
    initdata(vexs,arcs);
    CreateGraph(G,vexs,n,arcs,e);
    while(1)
    {
        welcom();
        spotList();
        printf(" \n| 请选择功能  |\n");
        scanf("%d",&choice);
        switch(choice)
        {
          case 1:
          	system("cls");
          	spotList();
            printf("你想查看哪个景点的信息（1-%d）？\n",G.n);
            scanf("%d",&i);
            while(i<=0||i>G.n)
            {
             printf("你输入的数据不合法，请重新输入\n");
             scanf("%d",&i);
            }
             visit(i-1,G);
             break;
         case 2:
            system("cls");
            spotList();
            for(i=0;i<n;i++)
            {   //初始化标志数组
             G.tags[i]=UNVISITED;
            }
             printf("输入第一个点的序号（1-%d）\n",G.n);      //算最短路径
             scanf("%d",&i);
            while(i<=0||i>G.n)
            {
             printf("你输入的数据不合法，请重新输入\n");
             scanf("%d",&i);
            }
             printf("输入第二个点的序号（1-%d）\n",G.n);
             scanf("%d",&j);
            while(j<=0||j>G.n)
            {
             printf("你输入的数据不合法，请重新输入\n");
             scanf("%d",&j);
            }
             Dijkstra(G,i-1,Dist);   //迪杰斯特拉算法求出Dist数组
            if(Dist[j-1].lowcost==INFINITY)
            {
             printf("没有连通\n");
             break;
            }
            else
            {
                printf("路线：");
                Dispath(G,Dist,j-1); //递归输出
                printf("\n");
                printf("路径长度为:%d米\n",Dist[j-1].lowcost*100);
                break;
            }
        case 3:exit(1);
        default:system("cls");printf("输入数据不合法，请重新选择\n");
      }
    }
    return 0;
}