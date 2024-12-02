#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>     //conio是Console Input/Output(控制台输入输出)的简写，其中定义了通过控制台进行数据输入和数据输出的函数，
//主要是一些用户通过按键盘产生的对应操作，比如getch()函数等等。
/*
5
12345 小李 91 92 93
12346 小王 98 80 98
12348 小张 97 99 100
12349 小明 95 94 93
12290 小林 89 97 96 
*/ 
//成绩结构体
struct score
{
	char snum[9];
	char sname[11];
	int chinese;
	int math;
	int english;
	int sumcj;//成绩总数 
	int rank;//排名 
};

//函数声明 
void showmenu(void);//菜单 
int xg(int);//修改成绩   
void lr(int);//录入成绩 
void cx(int);//查询成绩 
void xhcx(int);//学号查询 
void xmcx(int n);//姓名查询
void allrankcx(int);//排名查询 
void showcxmenu(void);//二级菜单，查询菜单 
void xs(int);//成绩显示 
void jspm(int);//计算排名 
int sc(int);//删除成绩 
void bccj(void);//保存成绩并退出 

//main函数 
int main()
{
	int flag,n=0,count=0;//flag标志位,count计数,当前总人数
	//-------------判断文件里面有多少条记录--------------------//
	FILE *fp;//文件指针 
	//表示fp是指向FILE结构的指针变量，通过fp即可找存放某个文件信息的结构变量，
	//然后按结构变量提供的信息找到该文件，实施对文件的操作。习惯上也笼统地把fp称为指向一个文件的指针。
	fp=fopen("cj.txt","a+");//打开这个文件，并将文件放入缓冲区 
	//"a+"：可读/写数据，原来的文件不被删去，位置指针移到文件末尾 
	if(fp==NULL)      //文件指针指向空 
	{
		printf("打开文件失败,请重试！\n");
		getch(); 
		fclose(fp);  //fclose是一个函数名，功能是关闭一个流。
		exit(0);
	} 
	int c = 0;
//	feof()是检测流上的文件结束符的函数，如果文件结束，则返回非0值，否则返回0
//
//一般在文件操作，中经常使用feof()判断文件是否结束。
	while(!feof(fp))//当条件为不是文件尾时均执行后续代码
	{
		char cc = fgetc(fp);//读取下一个字符 
		if(cc==EOF)
        {
        	break;
        }
        //输出字符
//        putchar(cc);
		c++;
	}
	count = c/14;//IO流的读取是按字符读的，有意义文字7+空格6+换行符1=14 
//	printf("%d", count); 
//	getch();
//fclose是一个函数名，功能是关闭一个流。
//注意:使用fclose()函数就可以把缓冲区内最后剩余的数据输出到内核缓冲区，
//并释放文件指针和有关的缓冲区。
	fclose(fp);//返回一个流，并将文件储存进入磁盘 
	//---------------------------------//
	do
	{
		showmenu();
		scanf("%d",&flag);//选择操作 
		switch(flag)
		{
			case 1: printf("请输入您要录入的人数：");
					scanf("%d",&n);
				    lr(n);
					count += n;break;
			case 2: count=sc(count);break;
			case 3: xg(count);break;
			case 4: cx(count);break;
			case 5: jspm(count);break;
		    case 6: xs(count);break;
		    case 0: bccj();break; 
		    default:printf("输入错误，请重试！\n");getch();//getch()用户输入一个字符函数便自动读取，不需要回车 
		} 
	}while(flag!=0);
	getch();
	return 0;
}

//0显示菜单
void showmenu()
{
	system("cls"); 
	printf("*----------------------------------------------------*\n");
	printf("*               欢迎使用**成绩管理系统               *\n");
	printf("*----------------------------------------------------*\n"); 
	printf("*               1： 录入成绩                         *\n");
	printf("*               2： 删除成绩                         *\n");
	printf("*               3： 修改成绩                         *\n");
	printf("*               4： 成绩查询                         *\n");
	printf("*               5： 成绩计算并排名                   *\n");
	printf("*               6： 显示成绩信息                     *\n");
	printf("*               0： 保存信息并退出系统               *\n");
	printf("*----------------------------------------------------*\n");
	printf("选择操作<0-6>                                         \n");
	return;
}//展示界面 
 
//1录入成绩 
void lr(int n)
 {
 	struct score stu[100];
 	FILE *fp;
 	fp=fopen("cj.txt","a+");
 	if(fp==NULL)
 	{
		printf("打开文件失败,请重试！\n");
		getch(); 
		fclose(fp);
		exit(0);
	}
 	printf("请输入全部学生的学号，姓名，语文成绩，数学成绩，英语成绩；\n"); 
 	int i;
 	for(i=0;i<n;i++)
 	{	
 		printf("----第%d个学生----\n", i+1);
		printf("学号:");
		scanf("%s",&stu[i].snum);
		for(int k=0;k<i;k++)
		{
			if(strcmp(stu[i].snum,stu[k].snum)==0)
			{
			printf("学号重复，请重新输入！");
		    scanf("%s",&stu[i].snum);
		}
		 } 
	
		printf("姓名：");
		scanf("%s,",&stu[i].sname);
		
		printf("语文成绩：");
		scanf("%d",&stu[i].chinese);
		
		printf("数学成绩：");
		scanf("%d",&stu[i].math);
		
		printf("英语成绩：");
		scanf("%d",&stu[i].english);
		
		stu[i].sumcj=0;
		stu[i].rank=0;	//暂时先让排行和总成绩为零 
		//写入数据 
		fprintf(fp,"%s %s %d %d %d %d %d\n",stu[i].snum,stu[i].sname,stu[i].chinese,stu[i].math,stu[i].english,stu[i].sumcj,stu[i].rank);}
		//写入文件 
	 	fclose(fp);
	 	printf("添加学生成功,请按任意键返回\n");
	 	getch();
 }
	
//2删除成绩                                    
int sc(int n)
{
	struct score stu[100];
	struct score sub[99];//删除后的结构体数组 
	char stnum[9];//学号
	int find=0;
	printf("请输入你要删除的学生学号:"); 
	scanf("%s", &stnum);
	FILE *fp;
	fp=fopen("cj.txt","r");//"r"：只能从文件中读数据，该文件必须先存在，否则打开失败 
	if(fp==NULL)
	{
		printf("打开文件失败,请联系管理员\n");
		getch(); 
		return -1;   
	}
	int c=0;
	int index=0;//用于记录目标序号 
	while(!feof(fp))//不为空   当条件为不是文件尾时均执行后续代码
	{ 
		fscanf(fp,"%s %s %d %d %d %d %d\n", &stu[c].snum,&stu[c].sname,&stu[c].chinese,&stu[c].math,&stu[c].english,&stu[c].sumcj,&stu[c].rank);
		if(strcmp(stnum,stu[c].snum)==0)//字符串比较（查找学号一样的） 
		{
			find = 1;//根据学号查找，找到赋值为1 
			index = c;//记录编号
		} 
		c++;//运用一个简单的循环，依次向下找 
	}
	fclose(fp);
	if(n==0)
	{
		printf("已经没有学生成绩信息了,请按任意键返回\n");
		getch();  
		showmenu();
		return n;
	}
	if(find==0)
	{
		printf("没有该学生成绩信息,请按任意键返回\n");
		getch();  
		showmenu();
		return n;
	}
	else 
	{
		int i;
		//删除 
		for(i=0;i<c;i++) // 
		{
			if(i < index)
			{
				sub[i] = stu[i];//在需删除的学号前，一一对应
			}
			else
			{
				sub[i] = stu[i+1];//sub是删除后的 
			}//需删除的学号之后，移一个位置 
		}
		
		fp=fopen("cj.txt","w");//"w"：只能向文件写数据，若指定的文件不存在则创建它，如果存在则先删除它再重建一个新文件
		//写入数据 
		for(i=0;i<c-1;i++)
		{
			fprintf(fp,"%s %s %d %d %d %d %d\n",sub[i].snum,sub[i].sname,sub[i].chinese,sub[i].math,sub[i].english,sub[i].sumcj,sub[i].rank); 	
		} 
		fclose(fp);//写入删除后的成绩，并储存进入磁盘 
		printf("学号为%s的学生成绩删除成功,请按任意键返回\n",stnum);
		getch();
		showmenu();
		return n-1;//学生人数-1 
	}     
}
 
///3修改成绩
int xg(int n) 
{	
	struct score stu[100];
 	FILE *fp;
 	char stnum[9];
 	int find=0;  
 	printf("请输入要修改的学生学号:");
 	scanf("%s",stnum);
 	fp=fopen("cj.txt","r");
 	if(fp==NULL)
 	{
	  	printf("文件打开失败,请联系管理员\n");
	  	getch();
	  	return -1;	
 	}
 	int c=0;
 	while(!feof(fp))
	{
//		fscanf 位于头文件<stdio.h>中，函数原型为 int fscanf(FILE * stream, const char * format, [argument...]); 
//其功能为根据数据格式(format)从输入流(stream)中读入数据(存储到argument);与fgets的差别在于:fscanf遇到空格和换行时结束，注意空格时也结束，fgets遇到空格不结束。
//

	 	fscanf(fp,"%s %s %d %d %d %d %d\n",&stu[c].snum,&stu[c].sname,&stu[c].chinese,&stu[c].math,&stu[c].english,&stu[c].sumcj,&stu[c].rank);
	 	if(strcmp(stnum,stu[c].snum)==0)	
		{
		 	find=1;
		 	//修改操作 
		 	printf("找到你要修改成绩的同学,请输入他的成绩:\n");
		 	printf("语文成绩: %d,新成绩为:",stu[c].chinese);
		 	scanf("%d",&stu[c].chinese);
		 	printf("数学成绩: %d,新成绩为:",stu[c].math); 
		 	scanf("%d",&stu[c].math);
		 	printf("英语成绩: %d,新成绩为:",stu[c].english);
		 	scanf("%d",&stu[c].english);
 		}
  		c++;	
 	}
	fclose(fp);
	if(find==0)
	{
		printf("没有找到要修改的学生记录,请按任意键退出\n");
		getch(); 
	} 
	else
 	{
	  	fp=fopen("cj.txt","w");
	  	int i; 
	   	for(i=0;i<n;i++)
	   	{
	   		//更新数据 
		    fprintf(fp,"%s %s %d %d %d %d %d\n",stu[i].snum,stu[i].sname,stu[i].chinese,stu[i].math,stu[i].english,stu[i].sumcj,stu[i].rank);	
	   	}
		fclose(fp);	 
		printf("学号为%s同学的成绩已经修改成功,请按任意键返回",stnum);
 		getch(); 
 	}
  	showmenu();
  	return 1; 
}
   
//4成绩查询
void cx(int n) //n全班人数 
{
	int k;
	do
	{
		showcxmenu();
		scanf("%d",&k); 
		switch(k)
		{ 
			case 1:xhcx(n);break;//学号查询 
			case 2:xmcx(n);break;//姓名查询 
			case 3:allrankcx(n);break;//全班排名查询
			case 0:break;
			default:printf("输入错误，请重新选择\n");getch();
		} 
	}while(k!=0);
	return;		
}

//4.0查询菜单
void showcxmenu() 
{
	system("cls");
	printf("*----------------------------------------------------*\n");
	printf("*                    成绩查询菜单                    *\n");
	printf("*----------------------------------------------------*\n"); 
	printf("*               1： 按学号查询                       *\n");
	printf("*               2： 按姓名查询                       *\n");
	printf("*               3： 全班排名查询                     *\n");
	printf("*               0： 退出查询系统，返回主系统         *\n");
	printf("*----------------------------------------------------*\n");
	printf("选择操作<0-3>                                         \n");
}

//4.1学号查询
void xhcx(int n)
{   
	struct score stu[100];
	char snum[9];
	printf("请输入你要查询学生的学号：");
	scanf("%s",&snum);
	FILE *fp; 
	fp=fopen("cj.txt ","r");//"r"：只能从文件中读数据，该文件必须先存在，否则打开失败 
	if(fp==NULL)
	{
		printf("打开文件失败！\n");
		getch();
		exit(0); 
	}
	int c = 0;
	while(!feof(fp)){
		fscanf(fp,"%s %s %d %d %d %d %d\n",&stu[c].snum,&stu[c].sname,&stu[c].chinese,&stu[c].math,&stu[c].english,&stu[c].sumcj,&stu[c].rank);
		c++;
	}
	int i;
	for(i=0;i<n;i++)
	{
		if(strcmp(snum,stu[i].snum)==0)//二者相等返回0 
		{
			printf("学号\t姓名\t语文\t数学\t英语\t总分\t名次\n");
			printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n",stu[i].snum,stu[i].sname,stu[i].chinese,stu[i].math,stu[i].english,stu[i].sumcj,stu[i].rank);
			printf("按任意键返回\n");
			getch();
			fclose(fp);
			return;			
		}
	}
	printf("未找到要查询学生的成绩，请重试！\n");
	getch();
	fclose(fp);
	return;
}  

//4.2姓名查询
void xmcx(int n)
{
  	struct score stu[100];	
	char sname[11];
	printf("请输入你要查询学生的姓名：");
	scanf("%s",&sname);
	FILE *fp; 
	fp=fopen("cj.txt ","r");
	if(fp==NULL)
	{
		printf("打开文件失败！\n");
		getch();
		exit(0); 
	}
	int c = 0;
	while(!feof(fp)){
		fscanf(fp,"%s %s %d %d %d %d %d\n\n",&stu[c].snum,&stu[c].sname,&stu[c].chinese,&stu[c].math,&stu[c].english,&stu[c].sumcj,&stu[c].rank);
		c++;
	}
	int i,p=0;
	for(i=0;i<n;i++)
	{
		if(strcmp(sname,stu[i].sname)==0)
		{
			p++;
			printf("学号\t姓名\t语文\t数学\t英语\t总分\t名次\n");
			printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n",stu[i].snum,stu[i].sname,stu[i].chinese,stu[i].math,stu[i].english,stu[i].sumcj,stu[i].rank);
			printf("按任意键返回\n");
			getch();
			fclose(fp);
		}
	}
	if(p!=0) return;
	printf("未找到要查询学生的成绩，请重试！\n");
	getch();
	fclose(fp);
	return;     
}

//4.3全班排名查询
void allrankcx(int n)
{
  	struct score stu[100];	
  	struct score temp;	
	FILE *fp; 
	fp=fopen("cj.txt ","r");
	if(fp==NULL)
	{
		printf("打开文件失败！\n");
		getch();
		exit(0); 
	}
	int c = 0;
	while(!feof(fp)){
		fscanf(fp,"%s %s %d %d %d %d %d\n",&stu[c].snum,&stu[c].sname,&stu[c].chinese,&stu[c].math,&stu[c].english,&stu[c].sumcj,&stu[c].rank);
		c++;
	}
	int i,j;
	for(i=0;i<n;i++)
	{
		if(stu[i].rank == 0){
			printf("请先进行成绩计算进行排名！！\n");
			getch();
			fclose(fp);
			return;	
		}
		stu[i].sumcj = stu[i].chinese + stu[i].math + stu[i].english;
		//冒泡排序算法：进行 n-1 轮比较
	    for(i=0; i<n-1; i++){
	        //每一轮比较前 n-1-i 个，也就是说，已经排序好的最后 i 个不用比较
	        for(j=0; j<n-1-i; j++){
	            if(stu[j].sumcj > stu[j+1].sumcj){
	                temp = stu[j];
	                stu[j] = stu[j+1];
	                stu[j+1] = temp;
	            }
	        }
	    }
	    printf("学号\t姓名\t语文\t数学\t英语\t总分\t名次\n");
	    for(i=0;i<n;i++)
	    {
			printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n",stu[i].snum,stu[i].sname,stu[i].chinese,stu[i].math,stu[i].english,stu[i].sumcj,stu[i].rank);
		}
		printf("按任意键返回\n");
		getch();
		fclose(fp);
		return;
	}
	printf("查询失败，请重试！\n");
	getch();
	fclose(fp);
	return;     
}

//5计算排名函数 
void jspm(int n)
{
	struct score stu[100];
	int i,j,temp;
	int count;
	FILE *fp;
	fp=fopen("cj.txt","r");
	if(fp==NULL)
	{
		printf("打开文件失败！\n");
		getch();
		exit(0);
	}
    int c = 0;
	while(!feof(fp)){
		fscanf(fp,"%s %s %d %d %d %d %d\n",&stu[c].snum,&stu[c].sname,&stu[c].chinese,&stu[c].math,&stu[c].english,&stu[c].sumcj,&stu[c].rank);
		stu[c].sumcj = stu[c].chinese + stu[c].math + stu[c].english;
		c++;
	}
	fclose(fp);
	//计算排名并存储 
    for(i=0;i<n;i++)
    {
	    temp=1;//第1名 
	    for(j=0;j<n;j++){
	    	if(stu[i].sumcj<stu[j].sumcj) temp++;//如果较小，排名下降1名
		} 
		stu[i].rank=temp;
    }
    //更新记录 
    fp=fopen("cj.txt","w");
   	for(i=0;i<n;i++)
   	{
	    fprintf(fp,"%s %s %d %d %d %d %d\n",stu[i].snum,stu[i].sname,stu[i].chinese,stu[i].math,stu[i].english,stu[i].sumcj,stu[i].rank);	
   	}
	fclose(fp);
    printf("数据重新计算和排名成功,请按任意键返回主菜单。\n");
	getch();
    return;       
}

//6显示成绩信息
void xs(int n) 
{
	struct score stu[100];
	int i;	
	printf("成绩信息如下：\n");
	FILE *fp;
	fp=fopen("cj.txt","r");
	if(fp==NULL)
	{
		printf("打开文件失败,请重试！\n");
		getch(); 
		fclose(fp);  
		exit(0);
	} 
	printf("学号\t姓名\t语文\t数学\t英语\t总分\t名次\n"); 
	int c = 0;
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %d %d %d %d %d\n",&stu[c].snum,&stu[c].sname,&stu[c].chinese,&stu[c].math,&stu[c].english,&stu[c].sumcj,&stu[c].rank);
		c++;
	}
	if(n!=0){//人数不为0 
		for(i=0;i<c;i++)
		{
			printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\n",stu[i].snum,stu[i].sname,stu[i].chinese,stu[i].math,stu[i].english,stu[i].sumcj,stu[i].rank);
		}	
	}
	fclose(fp); 
	printf("显示完毕 ,请按任意键返回\n");
	getch();
	return;
}

//0保存信息并退出系统
void bccj()
{
	printf("感谢您的使用，欢迎下次使用!\n");
	getch();	 
	return;
}