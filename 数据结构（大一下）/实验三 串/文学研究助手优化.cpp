#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int  keynum;//关键词数量
char *readbuf;//读入缓冲区（用来读写所存的文件） 
int  hang,lie;//确定行和列 

int length(char *p){   //求字符串长度 
	int i=1;
	while(p[i]){
		i++;
	}
	return i-1;
}

int* get_next(char *p,int *next){ //求next数组 
	int i,k;
    i=1,k=0;
    next[1]=0; 
    while(i<length(p)){ 
    	if(k==0||p[i]==p[k]){
    		++i;
    		++k;
    		if(p[i]!=p[k]){
    		next[i]=k;}
    		else{
    		  next[i] = next[k];
			}
		}
		else{
			k=next[k];
		}
	}
	return next;
}

int Index(char *S,char *P,int pos,int *next) //KMP算法
{
	int i=pos,j=1;
   	while(i<=length(S)&&j<=length(P))
   	{
    	if(j==0||S[i]==P[j])
		{
			++i;
			++j;
		} 
    	else
    	{
    		j=next[j];
		}
   	}
   if(j>length(P))
    {
   		return (i-length(P));
	} 
    else
    {
    	return 0;
	}
}


int main()
{
  int i,j;
  char **p;
  int  **next;
  int  **pnext;
  printf("*******************欢迎使用文学助手系统**************************\n");
  while(1){
  printf("请输入你需要查询的关键词数量\n");
  scanf("%d",&keynum);
  p    =    (char**)malloc(sizeof(char*)*keynum);//动态开辟二维数组 用来保存字符串 
  next =    (int**) malloc(sizeof(int*)*keynum);//动态开辟二维数组  用来保存每个字符串的next数组 
  pnext =   (int**) malloc(sizeof(int*)*keynum);//用来承接函数返回值 
  for(i=0;i<keynum;i++){
  	next[i] = (int*)malloc(sizeof(int)*20);
  }
  for(i=0;i<keynum;i++){
  	pnext[i] = (int*)malloc(sizeof(int)*20);
  }
  for(i=0;i<keynum;i++){
  	p[i] = (char *)malloc(sizeof(char)*20);
  }
  printf("请输入你需要查询的关键词\n");
  for(i=0;i<keynum;i++){
  	scanf("%s",&p[i][1]);                //输入字符串 
  }
  printf("你所查询的关键词如下:\n");
  for(i=0;i<keynum;i++){
  	printf("%s",&p[i][1]);               //查询字符串 
  	printf("\n");
  }
  for(i=0;i<keynum;i++){
     pnext[i] = get_next(p[i],next[i]);
     printf("%s的next数组为：",&p[i][1]);
     for(j=1;j<strlen(p[i]);j++){
     	 printf("%d ",pnext[i][j]);
	 }
	 printf("\n");
  }
  readbuf = (char*)malloc(sizeof(char)*1024);
  for(i=0;i<keynum;i++){
  	    int row=0,col =0;
  	    int k=0;
  	    int count = 0;
  	  	FILE *fp;                           //创建一个文件 
	  	fp=fopen("1.txt","r");
	  	if(fp==NULL){
			printf("open file\n");
		}
	  while(!feof(fp)){
	  	fgets(readbuf,1024,fp);
	  	row++;
  	 	col = Index(readbuf,p[i],0,next[i]);   //返回文件的列 
  	 	if(col!=0){
  	 	  printf("%s的行为%d,列为%d",&p[i][1],row,col+1);
  	 	  k++;
		}
		while(col!=0){
			col = Index(readbuf,p[i],col+1,next[i]);
			if (col!=0)         
	    	{
				k++;
				printf(",%d",col+1);//若匹配成功，则打印列号
		    }else{
		    	printf("\n");
			}
		 }
  	}
	   	count=count+k;
//	   	if (k) 
//	   	{
//		   	printf("\n"); //输出格式控制	
//		}
		fclose(fp);	
	    if(count){
		 printf("%s共出现%d次\n",&p[i][1],count);
		 printf("\n");
	  } 
	 else{
		 printf("No Found\n");
		 printf("\n"); 
	 }
	}
  }
  
}
 
