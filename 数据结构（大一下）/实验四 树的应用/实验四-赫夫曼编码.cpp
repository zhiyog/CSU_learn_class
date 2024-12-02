#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_size 100

typedef struct{
    float  weight;
    char ch;     
    int parent, lchild, rchild;
}HTNode, *HuffmanTree;
/*定义赫夫曼树结点的结构体变量，存放结点的权值、字符、双亲、左孩子和右孩子*/


typedef char **HuffmanCode; //指向赫夫曼编码的指针，用于存放编码

void welcome();    //操作界面
void Init(HuffmanTree &HT); //输入n个字符及其对应的权值，根据权值建立哈夫曼树
void HuffmanCreat(HuffmanTree &HT, char *character, float *w, int n);//建立赫夫曼树
void select(HuffmanTree &HT, int j, int *s1, int *s2); //选择权最小的两个结点
void EnCoding(HuffmanTree &HT); //编码
void Decoding(HuffmanTree &HT); //译码
void Print_code(); //打印代码
void Print_tree(HuffmanTree &HT); //以凹凸表形式打印哈夫曼树
int Read_tree(HuffmanTree &HT); //从文件中读入赫夫曼树
void find(HuffmanTree &HT, char *code, char *text, int i, int m);//译码时根据01字符串寻找相应叶子节点的递归算法
void Convert_tree(HuffmanTree &HT,unsigned char T[100][100], int s, int *i, int j);//将内存中的赫夫曼树转换成凹凸表形式的赫夫曼树
int n = 0; //全局变量，存放赫夫曼树叶子结点的数目

int main()
{
    char choice;
    HuffmanTree HT;
    while (1)
    {
        welcome();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:system("cls");Init(HT); break;
        case 2:system("cls");EnCoding(HT); break;
        case 3:system("cls");Decoding(HT); break;
        case 4:system("cls");Print_code(); break;
        case 5:system("cls");Print_tree(HT); break;
        case 0:exit(1);
        default:printf("Input error!\n");
        }
        getchar();
    }
    return 0;
}
//操作界面

void welcome()//打印选择界面
{
    printf("\t\t\t\t\t\t          《赫夫曼编码》        \n\n");
    printf("\t\t\t\t\t\t1.初始化哈夫曼树\n");
    printf("\t\t\t\t\t\t2.对哈夫曼树进行编码\n");
    printf("\t\t\t\t\t\t3.对编码进行译码\n");
    printf("\t\t\t\t\t\t4.打印哈夫曼编码\n");
    printf("\t\t\t\t\t\t5.打印哈夫曼树\n");
    printf("\t\t\t\t\t\t0.退出系统\n");
    printf("\t\t\t\t\t输入你的选择：");
}

/*初始化函数，输入n个字符及其对应的权值，根据权值建立哈夫曼树，并将其存于文件hfmtree.txt中*/
void Init(HuffmanTree &HT)
{
    FILE *fp;
    int i, n,num;
    float w[max_size]; //存放n个字符的权值
    char character[max_size]; //存放n个字符
    HuffmanTree HTtest;
    printf("\n输入字符个数 n:");
    scanf("%d", &n);
    HTtest=(HuffmanTree)malloc((2*n-1)*sizeof(HTNode));//内存分配
    
    printf("输入%d个字符及其对应的权值:\n", n);
    for (i = 0; i < n; i++)
    {
        getchar();
        scanf("%c %f",&character[i],&w[i]);      //输入n个字符和对应的权值
    }
    HuffmanCreat(HT, character, w, n);    //建立赫夫曼树
    if ((fp = fopen("hfmtree.txt", "w+")) == NULL)//“w+”创建新文件供读取并写入
       {
        printf("Open file hfmtree.txt error!\n");
        exit(1);
       }
    num=fwrite(HT+1,sizeof(HTNode),2*n-1,fp);//将建立的赫夫曼树存入文件，fwrite函数成功写入则返回实际写入的数据个数 
    printf("\n%d\n",num);
    rewind(fp);//重新打开文件 
    fread(HTtest+1,sizeof(HTNode),2*n-1,fp);//读取 
    for (i=1;i<=2*n-1;i++)
    {
       printf("%c %.2f %d %d %d\n",HTtest[i].ch,HTtest[i].weight,HTtest[i].lchild,HT[i].rchild,HTtest[i].parent);
    }
    printf("\n建立赫夫曼树成功，已将其存于文件hfmtree.txt中\n");
    fclose(fp);//关闭流
}


//建立赫夫曼树的算法
void HuffmanCreat(HuffmanTree &HT, char *character, float *w, int n)
{
    int m, i, s1, s2;
    HuffmanTree p;
    if (n <= 1)
        return;//结束程序块
    m = 2 * n - 1;
    HT = (HuffmanTree)malloc((m + 1)*sizeof(HTNode));//多分配一个节点空间
    for (p = HT + 1, i = 1; i <= n; ++i, ++p, ++character, ++w)
    {
        p->ch = *character;
        p->weight = *w;
        p->parent = 0;
        p->lchild = 0;
        p->rchild = 0;
    }//树的叶子 
    for (; i <= m; ++i, ++p)
    {
        p->ch = 0;
        p->weight = 0;
        p->parent = 0;
        p->lchild = 0;
        p->rchild = 0;
    }//初始化根
    for (i = n + 1; i <= m; ++i)
    {
        select(HT, i - 1, &s1, &s2);//挑出权最小的两个节点
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].ch='#';
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }//两个树组成一个新的树
}


//从HT[1]到HT[j]中选择parent为0且weight最小的两个结点，用s1和s2返回其序号
void select(HuffmanTree &HT, int j, int *s1, int *s2)
{
    int i;
    //找weight最小的结点
    for (i = 1; i <= j; i++)
    {
       if (HT[i].parent == 0)
       {
          *s1 = i;
           break;
       }
    }//挑一个作为初始值
    for (; i <= j; i++)
    {
       if ((HT[i].parent == 0) && (HT[i].weight < HT[*s1].weight))
         *s1 = i;
    }
    HT[*s1].parent = 1;
    //parent=1来筛去已使用的树
    for (i = 1; i <= j; i++)
    if (HT[i].parent == 0)
    {
        *s2 = i; break;
    }
    for (; i <= j; i++)
    {
    if ((HT[i].parent == 0) && (i != *s1) && (HT[i].weight < HT[*s2].weight))
        *s2 = i;
    }
    HT[*s2].parent = 1;
    //同理
}

/*对文件tobetrans中的正文进行编码，然后将结果存入文件codefile中*/
void EnCoding(HuffmanTree &HT)
{
	
    FILE *fp, *fw;
    int i, f, c, start;
    char *cd;
    HuffmanCode HC;
    if (n == 0)
        n = Read_tree(HT);//从文件hfmtree.txt中读入赫夫曼树,返回叶子结点数，避免出错1
        
    //以下程序段求赫夫曼树中各叶子节点的字符对应的的编码，并存于HC指向的空间中
    {
        HC = (HuffmanCode)malloc((n + 1)*sizeof(char*));
        cd = (char *)malloc(n*sizeof(char));
        cd[n - 1] = '\0';
        for (i = 1; i <= n; ++i)
        {
            start = n - 1;//从叶子到根逆向求编码 
            for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
            if (HT[f].lchild == c)
                cd[--start] = '0';
            else cd[--start] = '1';//判断左右子树
            HC[i] = (char *)malloc((n - start+1)*sizeof(char));
            strcpy(HC[i], &cd[start]);
        }
        free(cd);
    }//HC[i]储存编码

    if ((fp = fopen("tobetrans.txt", "rb")) == NULL)
        printf("Open file tobetrans.txt error!\n");
    if ((fw = fopen("codefile.txt", "wb+")) == NULL)
        printf("Open file codefile.txt error!\n");
    char temp;
    fscanf(fp, "%c", &temp); //从文件读入第一个字符
    
    while (!feof(fp))//feof()是检测流上的文件结束符的函数，如果文件结束，则返回非0值，否则返回0
    {
        for (i = 1; i <= n; i++)
           if (HT[i].ch == temp) break;    //在赫夫曼树中查找字符所在的位置
        for (int r = 0; HC[i][r] != '\0';r++) //将字符对应的编码存入文件
           fputc(HC[i][r], fw);
        fscanf(fp, "%c", &temp);        //从文件读入下一个字符
    }
    
    fclose(fw);
    fclose(fp);
    printf("\n对文件hfmtree.txt编码成功,结果已存入codefile.txt中。\n\n");
}


/*将文件codefile中的代码进行译码，结果存入文件textfile中*/
void Decoding(HuffmanTree &HT)
{
    FILE *fp, *fw;
    int m, i;
    char *code, *text, *p;
    if (n == 0)
        n = Read_tree(HT);  //从文件hfmtree.txt中读入赫夫曼树,返回叶子结点数
    if ((fp = fopen("codefile.txt", "rb+")) == NULL)
        printf("Open file codefile.txt error!\n");
    if ((fw = fopen("textfile.txt", "wb+")) == NULL)
        printf("Open file textfile.txt error!\n");
    code = (char *)malloc(sizeof(char));
    fscanf(fp, "%c", code);        //从文件读入一个字符
    for (i = 1; !feof(fp); i++)
    {
        code = (char *)realloc(code, (i + 1)*sizeof(char)); //realloc分配更大空间
        fscanf(fp, "%c", &code[i]);//从文件读入下一个字符
    }
    
    code[i - 1] = '\0';
    //到此codefile.txt文件中的字符已全部读入，存放在code数组中
    text = (char *)malloc(100 * sizeof(char));
    p = text;
    m = 2 * n - 1;
    if (*code == '0')
        find(HT, code, text, HT[m].lchild, m);   //从根节点的左子树去找
    else
        find(HT, code, text, HT[m].rchild, m);   //从根节点的右子树去找
    for (i = 0; p[i] != '\0'; i++) //把译码好的字符存入文件textfile.txt中
        fputc(p[i], fw);
    fclose(fp);
    fclose(fw);
    printf("\n对codefile.txt文件译码成功，结果已存入textfile.txt文件。\n\n");
}

/*将文件codefi1e以紧凑格式显示在终端上,每行50个代码。同时将此字符形式的编码文件写入文件codeprint中。*/
void Print_code()
{
    FILE *fp, *fw;
    char temp;
    int i;
    if ((fp = fopen("codefile.txt", "rb")) == NULL)
        printf("Open file codefile.txt error!\n");
    if ((fw = fopen("codeprint.txt", "wb+")) == NULL)
        printf("Open file codeprint.txt error!\n");
    printf("\n文件codefi1e以紧凑格式显示如下:\n");
    fscanf(fp, "%c", &temp);        //从文件读入一个字符
    for (i = 1; !feof(fp); i++)
    {
        printf("%c", temp);
        if (i % 50 == 0) printf("\n");
        fputc(temp, fw);   //将该字符存入文件codeprint.txt中
        //fputc函数向指定的文件中写入一个字符
        fscanf(fp, "%c", &temp);        //从文件读入一个字符
    }
    printf("\n\n此字符形式的编码已写入文件codeprint.txt中.\n\n");
    fclose(fp);
    fclose(fw);
}

/*将已在内存中的哈夫曼树显示在屏幕上，同时将此字符形式的哈夫曼树写入文件treeprint中。*/
void Print_tree(HuffmanTree &HT)
{
    unsigned char T[100][100];
    int i, j, m = 0;
    FILE *fp;
    if (n == 0)
        n = Read_tree(HT);//从文件hfmtree.txt中读入赫夫曼树,返回叶子结点数

    Convert_tree(HT,T, 0, &m, 2 * n - 1); //将内存中的赫夫曼树转换成树，存于数组T中
    if ((fp = fopen("treeprint.txt", "wb+")) == NULL)
        printf("Open file treeprint.txt error!\n");
    printf("\n打印赫夫曼树：\n");
    for (i = 1; i <= 2 * n - 1; i++)
    {
        for (j = 0; T[i][j] != 0; j++)
        {
            if (T[i][j] == ' ')
                {
                    printf("  ");
                    fputc(T[i][j],fp);
               }
            else
            {
                printf("%d", T[i][j]);
                fprintf(fp, "%d\n", T[i][j]);
            }
        }
        printf("\n");
    }
    fclose(fp);
    printf("\n此字符形式的哈夫曼树已写入文件treeprint.txt中.\n\n");

}

/*从文件hfmtree.txt中读入赫夫曼树，返回叶子节点数*/
int Read_tree(HuffmanTree &HT)
{
    FILE *fp;
    int i, n;
    HT = (HuffmanTree)malloc(sizeof(HTNode));
    if ((fp = fopen("hfmtree.txt", "r")) == NULL)
        printf("Open file hfmtree.txt error!\n");
    for (i = 1; !feof(fp); i++)
    {
        HT = (HuffmanTree)realloc(HT, (i + 1)*sizeof(HTNode)); //用realloc函数增加空间
        fread(&HT[i], sizeof(HTNode), 1, fp); //读入一个节点信息
    }
    fclose(fp);
    n = (i - 1) / 2;
    return n;
}


/*根据01字符串简单寻找叶子*/
void find(HuffmanTree &HT, char *code, char *text, int i, int m)
{

    if (*code != '\0') //若译码未结束
    {
        code++;
        if (HT[i].lchild == 0 && HT[i].rchild == 0)   //若找到叶子节点
        {
            *text = HT[i].ch; //将叶子节点的字符存入text中
            text++;
            if ((*code == '0'))
                find(HT, code, text, HT[m].lchild, m); //继续从根节点的左子树找
            else
                find(HT, code, text, HT[m].rchild, m); //继续从根节点的右子树找
        }
        else   //如果不是叶子节点
        if (*code == '0')
            find(HT, code, text, HT[i].lchild, m);   //从该节点的左子树去找
        else
            find(HT, code, text, HT[i].rchild, m);   //从该节点的右子树去找
}
    else
        *text = '\0'; //译码结束
}


/*将内存中的赫夫曼树转换成表形式的赫夫曼树，转换成打印二叉树那个代码的输入*/
void Convert_tree(HuffmanTree &HT,unsigned char T[100][100], int s, int *i, int j)
{
    int k, l;
    l = ++(*i);
    for (k = 0; k < s; k++)
        T[l][k] = ' ';
    T[l][k] = HT[j].weight;
    if (HT[j].lchild)
        Convert_tree(HT,T, s + 1, i, HT[j].lchild);
    if (HT[j].rchild)
        Convert_tree(HT,T, s + 1, i, HT[j].rchild);
    T[l][++k] = '\0';
}