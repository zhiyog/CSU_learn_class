#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

#define MAXINT 10000
#define OK 1
#define ERROR 0 

typedef int Status ; 
typedef struct Node{
	
	char name[MAXINT] ;      //存储城市名； 
	float x_index, y_index ; //存储城市坐标； 
	struct Node *next ;
	
}Node, *LinkList;


//创建一个链表 
LinkList CreatList (int e) {
	
	LinkList l, tempt, p ;
	l = (LinkList)malloc(sizeof(Node)) ;
	l->next = NULL ;
	
	tempt = l ;
	
	int i = 0;
	for(i = 0 ; i < e ; i ++) {	 //向链表中存储数据 
		p = (LinkList)malloc(sizeof(Node)) ;
		scanf("%s %f %f", &p->name, &p->x_index, &p->y_index) ;
		p->next = tempt->next ;
		tempt->next = p ;
		tempt = p ;
	}
	return l ;
}

//打印出链表的信息
Status ShowList(LinkList l) {
	LinkList p ;
	p = l ;
	p = p->next ;
		printf("\t\t\t\t\t城市信息为：") ; 
		printf("\n") ;
		printf("\t\t\t\t\t-----------------------------------------------\n") ;
		printf("\t\t\t\t\t序\t城市名称\t城市坐标\n", p->name, p->x_index, p->y_index) ;		
	int order = 1 ;  
	while(p) {
		printf("\t\t\t\t\t%02d\t %-8s\t( %.2f°N, %.2f°E )\n",order, p->name, p->x_index, p->y_index) ;
		p = p->next ;
		order++ ;
	}
		printf("\t\t\t\t\t-----------------------------------------------\n" ) ; 
		return OK ;
} 

//查找一个链表元素
LinkList SearchList(LinkList l){	
	LinkList q ;
	q = (LinkList)malloc(sizeof(Node)) ;
	q->next = NULL ;
	scanf("%s", &q->name) ;
	LinkList p ;
	p = l ;
	while(p) {
		p = p->next ;
		if(!strcmp(p->name, q->name)){
			return p ; 
		}
		if(p->next == NULL){
		printf("没有查找到该城市信息") ;
	    return NULL ;
	    break ;
		}
	} 
	return 0;	
}

//将城市插入链表头部 
LinkList InsertList_head (LinkList l, LinkList temp) {
	Node *p, *q;
	p = l ;
	q = temp;
	q = q->next ;
	q->next = p->next ;
	p->next = q ;
	return l ;
}

//将城市插入任一城市之后 
LinkList InsertList_city (LinkList l, LinkList temp) {
	printf("请输入希望插入其后的城市：") ;
	Node *index, *q ;
	index = SearchList(l) ;
	q = temp ;
	q = q->next ;
	q->next = index->next ;
	index->next = q;
	return l ;
}

//插入一个链表元素 
LinkList InsertList (LinkList l) {
	// 插入城市信息
	printf("\n") ; 
	printf("请选择您希望将该城市插入的位置：\n");
	printf("A.将该城市插入至城市链表的头部\n") ;
	printf("B.将该城市插入任一城市之后\n") ;
	char c ;
	scanf("%s", &c) ;
	
	LinkList tempt ;
	printf("请输入新插入的城市名：\n") ;
	tempt = CreatList(1) ;
	
	switch(c) {
		case 'A':case 'a': l = InsertList_head (l, tempt) ; break ;
		case 'B':case 'b': l = InsertList_city (l, tempt) ; break ;
	} 
	return l ;
}

//删除一个链表元素
LinkList DeleteList(LinkList l){
	printf("请输入你想要删除的城市名称：\n") ;
	
	//已找到指向想要删除的城市的指针 
	Node *index , *p;
	index = SearchList(l) ; 
	//进行删除操作 
	p = l ;
	while(p->next != index) {
		p = p->next ;
	}
	p->next = p->next->next ;
	return l ;
}  

//更新链表中的一个元素
LinkList RenewList(LinkList l) {
	printf("请输入你想要更新的城市名称：\n") ;
	
	//已找到指向想要更新的城市的指针 
	Node *index , *p;
	index = SearchList(l) ; 
	//进行更新操作 
	printf("请输入新的城市名称及地理位置:\n") ;
	scanf("%s %f %f",&index->name, &index->x_index, &index->y_index) ;
	return l ;
}  

	//进入城市距离计算比较功能
LinkList DistanceCity(LinkList l, float e){
	printf("请输入一个城市的名称作为定位标志:\n") ;
	Node *index , *p, *q;
	index = SearchList(l) ;
	
	//从列表中删除被选中的定位城市的信息
	p = l ;
	while(p->next != index) {
		p = p->next ;
	}
	p->next = p->next->next ;
	ShowList(l) ; 
	
	//计算列表中其他城市与定位城市的距离
	int i = 0 ; 
	float dx = 0 , dy = 0 ;
	float distance = 0 ;
	LinkList dis ; //制作一个链表存储距离小于给定值的城市的所有信息 ;
	Node *d ; //一直指向dis链表末尾的指针; 
	dis = (LinkList)malloc(sizeof(Node)) ;
	dis->next = NULL ;
	d = dis ; 
	 
	q = l ; //利用两个坐标点间的距离公式，开始计算 
	while(q){
		q = q->next ;
		dx = q->x_index - index->x_index ;
		dy = q->y_index - index->y_index ;
		distance = sqrt(dx * dx + dy * dy) ;
		printf("%-8s距%-8s的距离为%.2f\n",q->name, index->name, distance) ;
		if(distance <= e) {
			LinkList temp ;
			temp = (LinkList)malloc(sizeof(Node)) ;
			strcpy(temp->name , q->name) ;
			temp->x_index = q->x_index ;
			temp->y_index = q->y_index ;
			temp->next = d->next ;
			d->next = temp ;
			d = temp ;
		}
		if(q->next == NULL)
		ShowList(dis) ;
	} 
   	return dis ;	
} 

Status Entrance(char c, LinkList l ){
	
	//查找城市信息 	
	 if(c == 'A' || c == 'a') {
	Node *index ;
	printf("请输入希望查询的城市：") ;
	index = SearchList(l) ;
    printf(" ( %.2f°N, %.2f°E )",  index->x_index, index->y_index) ;
}
    //插入城市信息 
    if(c == 'B' || c =='b') {
	l = InsertList(l) ; 
	ShowList(l) ;
}
	//删除城市信息
	if(c == 'C' || c =='c') {
	l = DeleteList(l) ; 
	ShowList(l) ;
}	
	//更新城市信息
	if(c == 'D' || c =='d') {
	l = RenewList(l) ;
	ShowList(l) ; 
	}
	
	//进入城市距离计算比较功能
	if(c == 'E' || c =='e') {
	float n ;
	printf("请输入您想查询的距离范围的数值：\n") ;
	scanf("%f", &n) ; 
	LinkList l_ ;	
	l_ = DistanceCity(l,n);
	ShowList(l_) ;
	}
	
	return OK ;
}


int main() {
	
		
	printf("建立城市链表：") ;
	int e = 0 ;
	printf("请输入您想输入的城市数目:") ;
	scanf("%d", &e) ;
	
	//创建一个城市链表 
	LinkList l ;
	printf("请输入城市名及其坐标：\n") ;
	l = CreatList(e) ;
	ShowList(l) ;
	
	//入口 
	printf("进入城市链表操作\n") ;
	printf("在创建城市链表后，可以进行如下操作\n") ;
	printf("A.查找城市信息\n") ;
	printf("B.插入城市信息\n") ;
	printf("C.删除城市信息\n") ;
	printf("D.更新城市信息\n") ;
	printf("E.进入城市距离计算比较功能\n") ;
	printf("F.退出操作\n") ;
	while(1){
	char c ; 
	printf("\n请输入操作数:\n") ;
    scanf("%s", &c) ;
    if(c == 'F' || c == 'f'){
    printf("退出程序。\n") ; 
	break ; // 退出程序 
}
    Entrance(c, l) ;
    }

	 
	return 0 ;
}
