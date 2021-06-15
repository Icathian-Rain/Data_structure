//循环链表
//初始
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//定义状态Status
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;

//定义循环链表

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


//定义尾指针rear or tail
int main()
{
    //构造循环链表
    LinkList *L;
    L->tail->next = L->head;
    //合并两个链表
    LinkList *L1, *L2;
    L1 ->tail->next = L1->head;
    L2 ->tail ->next = L2 ->head;
    Node *p;
    p = L1->tail->next;
    L1->tail->next = L2->tail->next->next;
    L2->tail->next = p;
    free(p); 

}


//双向链表(double linked list)
//线性表的双向链表存储结构
typedef struct _DulNode
{
    ElemType data;
    struct _DulNode *prior;
    struct _DulNode *next;
} DulNode;

typedef struct _DuLinkList
{
    DulNode *head;
    DulNode *tail;
} DuLinkList;

//双向链表的插入
//在第i个元素和第i+1个元素间插入数据e
Status DulInsert( DuLinkList *L, int i , ElemType e)
{
    int j = 0;
    DulNode * p, *q;
    p = L->head;
    if(i <1 )
    return ERROR;
    while(p->next != L->head && j<i)
    {
        p = p->next;
        j++;
    }
    if(p ->next == L->head || j>i+!)
    return ERROR;

    q = (DulNode *)malloc(sizeof (DulNode));
    q->data = e;
    q->prior = p;
    q->next = p ->next;
    p->next->prior = q;
    p->next = q;

    return OK;
}

//双向链表的删除
Status DulDelete(DuLinkList *L, int i)
{
    int j = 0;
    DulNode *p;
    p = L->head;
    if(i <1)
    return ERROR;
    while(p ->next == L->head && j<i)
    {
        p = p->next;
        j++;
    }
    if(p ->next == L->head || j>i+!)
    return ERROR;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
}

