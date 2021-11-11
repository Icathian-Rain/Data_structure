// 1.c
//头文件
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

#define MAXSIZE 100

//定义线性表
typedef int ElemType;
typedef struct _Node
{
    int Co; //系数
    int Ep; //指数
    struct _Node *next;
}Node;

typedef struct _SqList
{
    Node *head;
    Node *tail;
} SqList;

//栈
typedef struct _Stack
{
    int data[MAXSIZE];
    int top;
} Stack;

//栈操作
Status InitStack(Stack *S)
{
    S->top = 0;
    return OK;
}

Status Push(Stack *S, int e)
{
    if(S->top == MAXSIZE -1)
    {
        printf("Overflow\n");
        return ERROR;
    }
    S->data[S->top] = e;
    S->top ++;
    return OK;
}

Status Pop(Stack *S, int *e)
{
    if(S->top == 0)
    {
        printf("NULL\n");
        return ERROR;
    }
    S->top --;
    *e = S->data[S->top];
    return OK;
}

int IsSEmpty(Stack *S)
{
    if(!S->top)
        return 1;
    else
        return 0;
}


//循环队列定义
typedef struct _Queue
{
    int data[MAXSIZE];
    int front;
    int rear;
} Queue;


//队列操作
Status InitQueue(Queue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

Status EnQueue(Queue *Q, int e)
{
    if((Q->rear+1) % MAXSIZE == Q->front )
    return ERROR;
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1)%MAXSIZE;
    return OK;
}

Status DeQueue(Queue *Q, int *e)
{
    if(Q->front == Q->rear)
    return ERROR;
    *e = Q->data[Q->front];
    Q->front = (Q->front+1) % MAXSIZE;
    return OK;
}

int IsQEmpty(Queue *Q)
{
    if(Q->front == Q->rear)
    return 1;
    else
    return 0;
}

//初始化顺序表
Status _InitSqlist(SqList *S)
{
    S->head = (Node *)malloc(sizeof(Node));
    S->head = NULL;
    S->tail = S->head;
    return OK;
}

Status 










int main()
{
    char s[200];
    scanf("%s", s);

}