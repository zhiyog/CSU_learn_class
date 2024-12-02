
typedef struct WORD{
	char letter;
	struct WORD *next;
}word;                //单词节点 

typedef struct{
	word *first;
	word *last;
}row;                  //行结构节点 

typedef struct Row{
	row r;
	struct Row *next;
}ROW;                    //行结构 

typedef struct{
	ROW *first;
	ROW *last;
}article;            //文章结构 

void create_article(article *a)      //创建文章结构 
{
	a->first = (ROW*)malloc(sizeof(ROW));
	a->last = a->first;
	a->first->next = NULL;
	a->first->r.first = (word*)malloc(sizeof(word));
	a->first->r.last = a->first->r.first;
	a->first->r.first->next = NULL;
	a->first->r.first->letter = 1; 
}

void add_row(article *a)       //添加行 
{
	ROW *p;
	p = (ROW*)malloc(sizeof(ROW));
	p->next = NULL;
	p->r.first = (word*)malloc(sizeof(word));
	p->r.last = p->r.first;
	p->r.first->letter = a->last->r.first->letter+1;
	a->last->next = p;
	a->last = p;
}

void add_word(row *r,char ch)  //添加字母 
{
	word *p;
	p = (word*)malloc(sizeof(word));
	p->letter = ch;
	p->next = NULL;
	r->last->next = p;
	r->last = p;
}
