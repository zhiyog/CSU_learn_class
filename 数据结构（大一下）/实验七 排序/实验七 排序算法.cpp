#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<sys/timeb.h>

//#define MAX 25000  
#define MAX 25000

/*
n种排序方法，都是从大到小排列
没有太参考别人的程序，大部分是根据定义琢磨的
如有疏漏，恳请批评指教
*/

//辅助函数：交换两个变量
void swap(int*a,int*p)
{
    int temp = *a;
    *a = *p;
    *p = temp;
}

//冒泡排序
void bubbleSort(int* arr,int len)
{
    int i,j;
    //这个是上界
    for(i=0;i<len;i++)
    {
        //一般导数第i+1个以后都已经排好了
        for(j=1;j<len-i;j++)
        {
            //大的一直冒泡到最后面去
            if(arr[j-1]>arr[j])
            {
                swap(&arr[j-1],&arr[j]);
            }
        }
    }
}

//插入排序
//从第1个数开始，往后开始遍历，第i个数一定要放到使得前i个数都变成有序的。
void insertSort(int* arr,int len)
{
    int i,j;
    for(i=0;i<len;i++)
    {
        for(j=i;j>0;j--)
        {
            if(arr[j]<arr[j-1])
            {
                swap(&arr[j],&arr[j-1]);
            }else
            {
                //已经不比那个元素小了就提前退出
                break;
            }
        }
    }
}

//快速排序
void quickSort(int* arr,int start,int end)
{
    //递归最重要的就是设置退出条件，如下
    if(start>=end)
    {
        return;
    }
    int i = start;
    int j = end;
    int temp = arr[i];
    //如果右指针j一直没小于左指针i，一直跑
    while(i<j)
    {
        //先从右边找比基准小的，找到和基准交换，但要保留j值
        while(i<j)
        {
            if(arr[j]<temp)
            {
                swap(&arr[j],&arr[i]);
                break;
            }
            j--;
        }

        //右边找到一个比基准小的之后，轮到左边找比基准大的，然后和上面空出的j位置交换
        while(i<j)
        {
            if(arr[i]>temp)
            {
                swap(&arr[j],&arr[i]);
                break;
            }
            i++;
        }

    }
    //排左半区
    quickSort(arr,start,i-1);
    //排右半区
    quickSort(arr,i+1,end);
}

void mergeSort(int* arr,int start,int end)
{
    if(start>=end)
    {
        return;
    }
    int i = start;
    int mid = (start+end)/2;
    int j = mid + 1;
    mergeSort(arr,i,mid);
    mergeSort(arr,j,end);

    //合并
    //其实我觉得不用这个额外的空间也行，两个子序列再排一次能减少空间，不过速度肯定会有影响
    int* temp = (int*)malloc((end-start+1)*sizeof(int));
    int index = 0;
    //开始对比两个子序列，头部最小的那个数放到新空间
    while(i<=mid&&j<=end)
    {
        if(arr[i]<=arr[j])
        {
            temp[index++] = arr[i++];
        }else
        {
            temp[index++] = arr[j++];
        }
    }
    //总有一个序列是还没有放完的，这里再遍历一下没放完的
    while(i<=mid)
    {
        temp[index++] = arr[i++];
    }
    while(j<=end)
    {
        temp[index++] = arr[j++];
    }
    //排完再把新空间的元素放回旧空间
    int k = start;
    for(k;k<=end;k++)
    {
        arr[k] = temp[k-start];
    }
    free(temp);
}
//堆排序 
void adjust(int* arr,int len,int index)
{
    //调整函数，把孩子、父亲中的最大值放到父亲节点
    //index为待调整节点下标,一开始设它最大
    int max = index;
    int left = 2*index+1;//左孩子
    int right = 2*index+2;//右孩子
    if(left<len && arr[left] > arr[max])
    {
        max = left;
    }
    if(right<len && arr[right] > arr[max])
    {
        max = right;
    }
    //如果父亲节点不是最大
    if(max!=index)
    {
        //一旦上层节点影响了某个孩子节点，还要观察以这个孩子节点为父节点的子树是不是也不是大顶堆了
        swap(&arr[index],&arr[max]);
        //因为发生了交换，还要继续调整受到影响的孩子节点
        //***************************************
        adjust(arr,len,max);//这句话非常非常关键
        //***************************************
        /*
            只有父亲和孩子节点发生了交换，才有继续调整孩子的必要，如果无脑在不是这里面递归，堆排序的效果不会比冒泡好到哪去
            而如果写在了这里面，虽然还是pk不过快排，但好歹和快排的差距只缩小到个位数倍数的量级（小数据量的时候）
            堆排序一个优点是空间复杂度也不高
        */
    }
}
//主要排序部分
void heapSort(int* arr,int len)
{
    
    int i = len/2-1;
    for(i;i>=0;i--)
    {
        adjust(arr,len,i);
    }
    swap(&arr[0],&arr[len-1]);
    //第二次之后，只需要从根节点从上到下调整，遇到没发生交换的直接可以退出循环了
    //微调得到大顶堆（因为只有堆顶不满足而已）
    int j = len -1; //去掉尾节点后的数组长度
    //把最大值交换到最后
    for(j;j>0;j--)
    {
        adjust(arr,j,0);
        swap(&arr[0],&arr[j-1]);
    }
}

//计算时间，精确到毫秒
long getTime()
{
    struct timeb tb;
    ftime(&tb);//取得当前的时间 
    //前面是毫秒，后面是微秒
    return tb.time*1000+tb.millitm;
}

//小型主函数
void test()
{
    int* a1 = (int*)malloc(MAX*sizeof(int));
    int* a2 = (int*)malloc(MAX*sizeof(int));
    int* a3 = (int*)malloc(MAX*sizeof(int));
    int* a4 = (int*)malloc(MAX*sizeof(int));
    int* a5 = (int*)malloc(MAX*sizeof(int));
    int i = 0;
    srand(time(NULL));
    for(i;i<MAX;i++)
    {
        int temp = rand()%(MAX+1);
//        int temp = i;//升序测试
//        int temp = MAX-i-1;//降序测试

        a1[i] = temp;
        a2[i] = temp; 
        a3[i] = temp; 
        a4[i] = temp; 
        a5[i] = temp; 
    }


    long t1 = getTime();


    //冒泡排序
    bubbleSort(a1,MAX);
    long t2 = getTime();
    printf("冒泡排序排%d个随机数据耗时%ld毫秒\n",MAX,t2-t1);

    //插入排序
    insertSort(a2,MAX);
    long t3 = getTime();
    printf("插入排序排%d个随机数据耗时%ld毫秒\n",MAX,t3-t2);

    //快速排序
    quickSort(a3,0,MAX-1);
    long t4 = getTime();
    printf("快速排序排%d个随机数据耗时%ld毫秒\n",MAX,t4-t3);

    //归并排序
    mergeSort(a4,0,MAX-1);
    long t5 = getTime();
    printf("归并排序排%d个随机数据耗时%ld毫秒\n",MAX,t5-t4);

    //堆排序
    heapSort(a5,MAX);
    long t6 = getTime();
    printf("堆排序排%d个随机数据耗时%ld毫秒\n",MAX,t6-t5);
}

int main()
{
    test();
    return 0;
}