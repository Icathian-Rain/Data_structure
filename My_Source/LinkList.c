#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//线性表的单链表存储结构
typedef int ElemType;

typedef struct _Node
{
    ElemType data;
    struct _Node *next;
} Node;

typedef struct _LinkList
{
    Node *head;
    Node *tail;
} LinkList;

//定义状态Status
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;

//单链表的读取
//用e返回L中第i个数据元素的值
Status GetElem(LinkList *L, int i, ElemType *e)
{
    int j;
    Node *p;
    p = L->head->next;
    j = 1;
    while( p && j<i)
    {
        p = p->next;
        j++;
    }
    if( !p || j > i+1)
    return ERROR;
    *e = p->data;
    return OK;
}

//单链表的插入
//在L中第i个位置之前插入新的数据元素e，L的长度加1
Status ListInsert( LinkList *L, int i, ElemType e)
{
    int j;
    Node *p,*s;
    p = L->head;
    j = 1;
    while(p && j<i)
    {
        p = p->next;
        j++;
    }
    if(!p || j>i)
        return ERROR;
    s = (Node*)malloc(sizeof(Node));
    s ->data = e;
    s ->next = p->next;
    p->next = s;
    return OK;
}

//单链表的删除
//删除L的第i个数据元素，并用e返回其值，L的长度减1
Status ListDelete(LinkList *L,int i,ElemType *e)
{
    int j;
    Node *p, *q;
    p = L->head;
    while(p->next && j<i)
    {
        p=p->next;
        j++;
    }
    if(!(p->next) || j>i)
        return ERROR;
    q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return OK;
}


//单链表的整表创建
//头插法
/*循环：
    生成一新结点赋值给p;
    随机生成一数字赋值给p的数据域p->data;
    将p插入到头结点与前一新结点之间
*/
//随机产生n个元素的值，建立带表头结点的单链线性表L（头插法）
void CreateListHead(LinkList *L, int n)
{
    Node *p;
    int i;
    srand(time(0));
    L->head = (Node *)malloc (sizeof(Node));
    L->head->next = NULL;
    for(i = 0; i<n; i++)
    {
        p = (Node *)malloc(sizeof(Node));
        p->data = rand() %100 +1;
        p->next = L->head->next;    
        L->head->next = p;          //插入到表头
    }
}

//尾插法
//随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法）

void CreatListTail(LinkList *L, int n)
{
    Node *p, *r;
    int i;
    srand(time(0));
    L->head = (Node *)malloc(sizeof (Node));
    L->tail = L->head;
    for(i = 0 ;i<n; i++)
    {
        p = (Node *)malloc(sizeof(Node));
        p->data = rand() %100 +1;
        L->tail->next = p;
        L->tail = p;
    }
    L->tail = NULL;
}

//单链表的删除
/*思路：
将下一结点赋值给q;
释放p；
将q赋值给p;*/
//初始条件：顺序线性表L已存在，操作结果：将L重置为空表
Status ClearList(LinkList *L)
{
    Node *p, *q;
    p = L->head;
    while(p)
    {
        q= p->next;
        free(p);
        p = q;
    }
    L->head = NULL;
    return OK;
}






