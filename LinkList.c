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
    


}