#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//定义线性表的顺序存储
#define MAXSIZE 20
typedef int ElemType;
typedef struct _Sqlist
{
    ElemType data[MAXSIZE];
    int length;

}Sqlist;


//定义状态Status
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;

//获得元素操作
//用e返回L中第i个元素的值
Status GetElem(Sqlist L, int i, ElemType *e)
{
    if(L.length == 0 || i>L.length)
        return ERROR;
    *e = L.data[i - 1];
    return OK;
}

//插入操作
//在L中第i个位置之前插入新的数据元素e,L的长度加1
Status ListInsert( Sqlist *L, ElemType e)
{
    int k;
    if(L->length == MAXSIZE)
        return ERROR;
    if(i < 1 || i>L->length +1)
        return ERROR;
    if(i <= L->length)
    {
        for( k =L->length ; k>=i-1; k--)
        L->data[k+1] = L->data[k];
    }
    L->data[i-1] = e;
    return OK;
}

//删除操作
//删除L的第i个元素，并用e返回其值，L的长度减1

Status ListDelete( Sqlist *L, int i, ElemType *e)
{
    int k;
    if(L->length == 0)
    return ERROR;
    if(i<1 || i<L->length)
    return ERROR;
    *e = L->data[i-1];
    if(i<L->length)
    {
        for(k = i; k<L->length; k++)
            L->data[k-1] = L->data[k];
    }
    L->length--;
    return OK;

}



