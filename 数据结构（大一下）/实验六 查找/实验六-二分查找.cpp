#include<stdio.h>
#include<stdlib.h>
//二分查找非递归方式
int HalfSearch(int a[],int low,int high,int key)
{
	int mid;
 while(low<=high)
 {
 mid=(low+high)/2;//二分点
 if(a[mid]==key) return mid;
 else if(a[mid]<key) low=mid+1;
 else high=mid-1;
 }
 return -1;
}
//二分查找递归方式
int HalfSearch1(int a[],int low,int high,int key)
{
 int mid;
 if(low>high) return -1;//没找到，递归结束
 else{
 mid=(low+high)/2;
 if(a[mid]==key) return mid;//找到了，递归结束
 else if(a[mid]<key) return HalfSearch(a,mid+1,high,key);//右递归
 else return HalfSearch(a,low,mid-1,key);//左递归
 }
}
int main(void)
{
 int a[10]={12,22,34,65,76,78,89,90,121,145};
 int n;
 int key;
 printf("enter data to key:\n");
 scanf("%5d",&key);
 n=HalfSearch1(a,0,9,key);//也可以使用上一个函数 
 if(n==-1) printf("not found!\n");//没找到
 else printf("位置在：a[%d]",n);
 return 0;
}