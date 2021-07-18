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

typedef int QElemType;
#define MAXSIZE 10000;

//循环队列书序存储结构
typedef struct _SqQueue
{
    QElemType data[MAXSIZE];
    int front;              //头指针
    int rear;               //尾指针
} SqQueue;


//初始化一个空队列
Status InitQueue(SqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

//循坏队列求长度，返回Q的元素的个数，也就是队列当前的长度
int QueueLength( SqQueue *Q)
{
    return (Q->rear - Q->front +MAXSIZE) %MAXSIZE;
}

//循环队列的入队列操作
//若队列未满则插入元素e为Q新的队尾元素
Status EnQueue( SqQueue *Q, QElemType e)
{
    if((Q->rear + 1) % MAXSIZE == Q->front)
    return ERROR;
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

//循环队列的出队列操作
//若队列不空，则删除Q中队头元素，用e返回其值

Status DeQueue( SqQueue *Q, QElemType *e)
{
    if(Q->front == Q->rear) //队列空的判断
        return ERROR;
    *e = Q->data[Q->front];
    Q->front = (Q->front +1) % MAXSIZE;
    return OK;
}

//队列的链式存储结构及实现
//链队列的结构为
typedef struct _QNode       //结点结构
{
    QElemType data;
    struct _QNode *next;
} QNode;

typedef struct _LinkQueue
{
    QNode *front, *rear; //队头、队尾指针
} LinkQueue;


//入队操作
Status EnLinkQueue( LinkQueue *Q, QElemType e)
{
    QNode *s = (QNode *) malloc (sizeof (QNode));
    if(!s)
    return ERROR;
    s->data = e;
    s->next = NULL;
    Q->rear ->next = s;
    Q->rear = s;
    return OK;
}

//队列的出队操作
//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK,否则返回ERROR;

Status DeLinkQueue( LinkQueue *Q, QElemType *e)
{
    QNode *p;
    if(Q->front == Q->rear)
    return ERROR;
    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if(Q->rear == p)
    Q->rear = Q->front;
    return OK;

}













