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

//栈的结构定义
#define MAXSIZE 10000 
typedef int SElemType;
typedef struct _SqStack
{
    SElemType data[MAXSIZE];
    int top;
} SqStack;

//进栈操作
//插入元素e为新的栈顶元素
Status Push(SqStack *S, SElemType e)
{
    if(S->top == MAXSIZE -1)        //栈满
        return ERROR;
    S->top ++;                      //栈顶加1
    S->data[S->top] = e;         //将新插入元素赋值给栈顶空间
    return OK;
}

//出栈操作
//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
Status Pop( SqStack *S, SElemType *e)
{
    if(S->top == -1)
    return ERROR;
    *e = S->data[S->top];
    S->top--;
    return OK;

}


//两栈共享空间结构

typedef struct _SqDoubleStack
{
    SElemType data[MAXSIZE];
    int top1;
    int top2;
} SqDoubleStack;


//两栈共享空间的Push方法
//插入元素e为新的栈顶元素
Status DoublePush(SqDoubleStack *S, SElemType e, int stackNumber)
{
    if(S->top1 +1 == S->top2)
    return ERROR;
    if(stackNumber == 1)
    {
        S->top1 ++;
        S->data[S->top1] = e;
    }
    else if (stackNumber == 2)
    {
        S->top2 --;                 //若栈2则先top2-1后给数组元素赋值
        S->data[S->top2] = e;
    }
    return OK;
}


//两栈共享空间的Pop方法，参数只是判断栈1和栈2的参数stackNumber;
//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR;

Status DoublePop(SqDoubleStack *S, SElemType *e, int stackNumber)
{
    if(stackNumber == 1)
    {
        if(S->top1 == -1)
            return ERROR;
        *e = S->data[S->top1--];
    }
    else if (stackNumber == 2)
    {
        if(S->top2 == MAXSIZE)
            return ERROR;
        *e = S->data[S->top2 ++];
    }
    return OK;

}

//栈的链式存储结构

//链栈的结构代码：
typedef struct _StackNode
{
    SElemType data;
    struct _StackNode *next;
} StackNode, *LinkStackPtr;
typedef struct _LinkStack
{
    StackNode *top;
    int count;
} LinkStack;

//进栈操作
//插入元素e为新的栈顶元素

Status LinkStackPush (LinkStack *S, SElemType e)
{
    StackNode *s;
    s = (StackNode *)malloc(sizeof(StackNode));
    s->data = e;
    s->next = S->top;
    S->top = s;
    S->count++;    
    return OK;
}

//出栈操作
//若栈不空则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR；
Status LinkStackPop(LinkStack *S, SElemType *e)
{
    StackNode *p;
    if(!S->top)
    return ERROR;
    *e = S->top->data;
    p = S->top;             //将栈顶结点赋值给p
    S->top = S->top->next;  //将栈顶结点往后移一位
    free(p);
    S->count--;
    return OK;   

}

//栈的作用：递归
//斐波那契的递归函数

int Fbi(int i)
{
    if(i < 2)
    return i == 0 ? 0 : 1;      //如果i=1 则返回1，如果i= 0 则返回0
    return Fbi(i-1) + Fbi(i-2)  //Fbi函数就是函数自己，它在调用自己

}
int main()
{
    int i;
    for(i = 0; i<40 ; i++)
    printf("%d", Fbi(i));
    return 0;
}



