#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*12334567890
小李
12345678@qq.com
19098079900
小王
1447689@qq.com*/
#include<iostream>
int d[50];/*再散列*/
struct list
{
    char a[12];//电话号码 
    char name[15];//名字 
    char add[20];//邮箱 
    int f=0;//标记是否存在 
};
struct sqstack
{
    struct list *base;
   int i;
};
struct sqstack S;
void store(char *a,char *name,char *add)
{
    int key;
    key=int(a[0])+int(a[3])+int(a[7]);/*以电话号码的第1,4,8位作为关键字构造哈希函数*/
    S.i=key%20;
    int j=1;
    while(true)
    {
    if((S.base+S.i)->f==0)
    {
        strcpy((S.base+S.i)->a,a);
        strcpy((S.base+S.i)->name,name);
        strcpy((S.base+S.i)->add,add);
        (S.base+S.i)->f=1;
        break;
    }
        S.i=(key%20+d[j])%20;
        j++;//解决哈希冲突 
    }
 
}
void shuru()
{
void interface();
    printf("请输入：\n例如：\n15556931615\n小王\n12345678@qq.com\n输入0结束\n\n");
    char a[12];
    char name[15];
    char add[15];
   while(true)
   {
      scanf("%s",a);
      if(a[0]=='0')
        break;
      scanf("%s",name);
      scanf("%s",add);
      printf("%s已保存\n",name);
      store(a,name,add);/*将输入保存到哈希表*/
   }
   interface();
}
void print()
{
    void interface();
    int i;
    printf("姓名   电话号码      邮箱\n");
    for(i=0;i<20;i++)
    {
        if((S.base+i)->f==1)
        {
            printf("%s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
        }
    }
    interface();
}
void search()
{
    void interface();
    int i;
    int ff=0;
    int b;
    char a[15];
    printf("输入1按电话号码查找，输入2按姓名查找，输入3按邮箱查找\n");
    scanf("%d",&b);
    switch(b)
    {
        case 1:printf("请输入电话号码\n");
               scanf("%s",a);
               for(i=0;i<20;i++)
                if(strcmp(a,(S.base+i)->a)==0)
               {
                   printf("%s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                   ff=1;
               }
               if(ff==0)
                printf("找不到该用户\n");
               break;
       case 2:printf("请输入姓名\n");
               scanf("%s",a);
               for(i=0;i<20;i++)
                if(strcmp(a,(S.base+i)->name)==0)
               {
                   printf("%s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                   ff=1;
               }
                if(ff==0)
                printf("找不到该用户\n");
               break;
        case 3:printf("请输入邮箱\n");
               scanf("%s",a);
               for(i=0;i<20;i++)
                if(strcmp(a,(S.base+i)->add)==0)
               {
                   printf("%s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                   ff=1;
               }
                if(ff==0)
                printf("找不到该用户\n");
               break;
    }
    interface();
}
void del()
{
    void interface();
    int i;
    int ff=0;
    int b;
    char a[15];
    printf("输入1按电话号码删除，输入2按姓名删除，输入3按邮箱删除\n");
    scanf("%d",&b);
    switch(b)
    {
        case 1:printf("请输入电话号码\n");
               scanf("%s",a);
               for(i=0;i<20;i++)
                if(strcmp(a,(S.base+i)->a)==0)
               {
                   (S.base+i)->f=0;
                   printf("已删除：  %s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                   ff=1;
               }
               if(ff==0)
                printf("找不到该用户\n");
               break;
       case 2:printf("请输入姓名\n");
               scanf("%s",a);
               for(i=0;i<20;i++)
                if(strcmp(a,(S.base+i)->name)==0)
               {
                   (S.base+i)->f=0;
                   printf("已删除：  %s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                   ff=1;
               }
                if(ff==0)
                printf("找不到该用户\n");
               break;
        case 3:printf("请输入邮箱\n");
               scanf("%s",a);
               for(i=0;i<20;i++)
                if(strcmp(a,(S.base+i)->add)==0)
               {
                   (S.base+i)->f=0;
                   printf("已删除：  %s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                   ff=1;
               }
                if(ff==0)
                printf("找不到该用户\n");
               break;
    }
    interface();
}
void change()
{
    void interface();
    int i;
    int ff=0;
    int b;
    char a[15];
    printf("请输入姓名\n");
    scanf("%s",a);
    for(i=0;i<20;i++)
      if(strcmp(a,(S.base+i)->name)==0)
               {
                   printf("您要修改的是：  %s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                   printf("请输入新信息\n");
                   scanf("%s",(S.base+i)->a);
                   scanf("%s",(S.base+i)->name);
                   scanf("%s",(S.base+i)->add);
                   printf("已修改成：  %s %s %s\n",(S.base+i)->name,(S.base+i)->a,(S.base+i)->add);
                         ff=1;
               }
                if(ff==0)
                printf("找不到该用户\n");
 
    interface();
}
void write()
{
    void interface();
    int i=0;
    FILE *fp;
    if((fp=fopen("通讯录.txt","wb"))==NULL)
{
printf("open file error\n");
exit(1);
}
    for(i=0;i<=20;i++)
    {
         int ch=32;
        if((S.base+i)->f==1)
        {
            fprintf(fp,"%s",(S.base+i)->name);fputc(ch,fp);
            fprintf(fp,"%s",(S.base+i)->a);fputc(ch,fp);
            ch=10;
            fprintf(fp,"%s",(S.base+i)->add);fputc(ch,fp);
        }
    }
     fclose(fp);
   interface();
}
void interface()
{
    int i;
    printf("\t\t\t\t\t╔════════════════════════════════╗\n");
    printf("\t\t\t\t\t║             菜单               ║\n");							
    printf("\t\t\t\t\t║════════════════════════════════║\n");
    printf("\t\t\t\t\t║         1--输入通讯录          ║\n");							
    printf("\t\t\t\t\t║════════════════════════════════║\n");
    printf("\t\t\t\t\t║         2--显示通讯录          ║\n");							
    printf("\t\t\t\t\t║════════════════════════════════║\n");
    printf("\t\t\t\t\t║         3--查找联系人          ║\n");
    printf("\t\t\t\t\t║════════════════════════════════║\n");
    printf("\t\t\t\t\t║         4--删除联系人          ║\n");
    printf("\t\t\t\t\t║════════════════════════════════║\n");
    printf("\t\t\t\t\t║         5--修改联系人信息      ║\n");
    printf("\t\t\t\t\t║════════════════════════════════║\n");
    printf("\t\t\t\t\t║         6--保存到文件          ║\n");
    printf("\t\t\t\t\t║════════════════════════════════║\n");
    printf("\t\t\t\t\t║         0--退出系统            ║\n");
    printf("\t\t\t\t\t╚════════════════════════════════╝\n");
    printf("请输入你的选择:\n");
    scanf("%d",&i);
    switch(i)
    {
        case 0:return ;break;
        case 1:shuru();break;
        case 2:print();break;
        case 3:search();break;
        case 4:del();break;
        case 5:change();break;
        case 6:write();break;
    };
}
int main()
{
    system("color F0"); //可以写成 red 调出颜色组
    S.base=(struct list *)malloc(20*sizeof(struct list));
    printf("      				****************欢迎使用通讯录查询系统*********************\n\n");
    system("date /T");
     system("TIME /T");
        int i;
        for(i=1;i<25;i++)
            d[2*i]=-1*i*i;
        for(i=1;i<25;i++)/*构造二次再散列*/
            d[i+i-1]=i*i;
    interface();
}