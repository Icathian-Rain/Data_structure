#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef int ElemType;


//定义状态Status
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;



//线性表的静态链表存储结构
#define MAXSIZE 1000
typedef struct _Component
{
    ElemType data;
    int cur;
} Component, StaticLinkList[MAXSIZE];

//将一维数组space中个分量链成以备用链表
//space[0].cur为头指针，0表示空指针

Status InitList(StaticLinkList space)
{
    int i;
    for(i = 0; i<MAXSIZE-1; i++)
        space[i].cur = i+1;
    space[MAXSIZE - 1].cur = 0;// 静态链表为空，最后一个元素为0;
    return OK;
}

/*为了辨明数组中哪些分量未被使用，解决的办法是将所有未被使用过的及
已被删除的分量用游标链成一个备用的链表，每当进行插入时，便可以从备
用链表上取得第一个结点作为待插入的新结点。*/
int Malloc_SLL(StaticLinkList space)
{
    int i=space[0].cur;         //当前数组第一个元素的cur存的值
    if(space[0].cur)            //就是要返回的第一个备用空闲的下表
    space[0].cur = space[i].cur
    return i;
}

//在L中第i个元素之前插入新的元素e
Status ListInsert( StaticLinkList L, int i, ElemType e)
{
    int j,k,l;
    k = MAXSIZE-1;
    if(i <1 || i>MAXSIZE )
    return ERROR;
    j = Malloc_SLL(L);
    if(j)
    {
        L[j].data = e;
        for(l = 1; l<i; l++)
        k = L[k].cur;
        L[j].cur = L[k].cur;
        L[k].cur = j;
        return OK;
    }
    return ERROR;
}

//将下标为k的空闲结点回收到备用链表
void Free_SSL(StaticLinkList space, int k)
{
    space[k].cur = space[0].cur;
    space[0].cur = k;
}


//静态链表的删除操作
//删除在L中第i个元素e
Status ListDelete( StaticLinkList L, int i)
{
    int j,k;
    if( i<1 || i>MAXSIZE-1)
    return ERROR;
    k = MAXSIZE - 1;
    for(j = 1; j<i; j++)
    k = L[k].cur;
    j = L[k].cur;
    L[k].cur = L[j].cur;
    Free_SSL(L,j);
    return OK;
}

//静态链表的长度计算
//静态链表L已存在。操作结果：返回L中数据元素个数
int Listlength(StaticLinkList L)
{
    int j = 0;
    int i = L[MAXSIZE].cur;
    while(i)
    {
        i=L[i].cur;
        j++;
    }
    return j;
}








