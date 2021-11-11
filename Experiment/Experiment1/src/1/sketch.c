//todo :int -> double , danxiang -> shuangxiang
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
    int Coef; //系数
    int Expn; //指数
    struct _Node *next;
    struct _Node *prior;
}Node;

typedef struct _SqList
{
    Node *head;
    Node *tail;
} SqList;

void InitSqlist(SqList *S)
{
    S->head = (Node *)malloc(sizeof(Node));
    S->head->next = NULL;
    S->head->prior = NULL;
    S->tail = S->head;
}


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

int issym(char c)
{
    int flag = 0;
    if(c == '+' || c== '-' || c=='(' || c==')' || c == '\0')
    flag = 1;
    return flag;
}

void Insert(SqList *S, int coef, int expn)
{
    Node *p, *q, *r;
    if(!S->head->next)
    {
        p = (Node *)malloc(sizeof(Node));
        p->Coef = coef;
        p->Expn = expn;
        p->next = NULL;
        p->prior = S->head;
        S->head->next = p;
        S->tail = p;
    }
    else
    {
        q = S->head->next;
        while( !q && q->Expn > expn)
        {
            q = q->next;
        }
        if(q && q->Expn == expn)
            q->Coef+= coef;
        else
        {
            p = (Node *)malloc(sizeof(Node));
            p->Coef = coef;
            p->Expn = expn;
            if(q)
            {
                p->next = q->next;
                p->prior = q;
                q->next->prior = p;
                q->next = p;
            }
            else
            {
                p->prior = S->tail;
                p->next = NULL;
                S->tail = p;
            }
        }
    }
}

void mknode(char *begin, char *end, SqList *S, int flag)
{
    char *p = begin;
    int Coef = 0, Expn = 0;
    int x,e;
    Coef = Expn = 0;
    Stack St;
    InitStack(&St);
    while(*p >= '0' && *p <= '0')
    {
        Push(&St, *p);
        p++;
    }
    x = 1;
    while(!IsSEmpty(&St))
    {
        Pop(&St, &e);
        Coef += e*x;
        x *= 10;
    }
    if(p == 'x')
    {
        p++;
        if(p == '^')
        p++;
    }
    while(p<=end)
    {
        push(&St, *p);
        p++;
    }
    x = 1;
    while(!IsSEmpty(&St))
    {
        Pop(&St, &e);
        Expn += e*x;
        x *= 10;
    }
    if(flag)
    Insert(SqList &S, Coef, Expn);
}



void plus(char *s, SqList *S)
{
    char *p1, *p2;
    int flag = 0;
    p1 = s;
    if(*p1 == '-')
    {
        flag = 1;
        p1++;
    }
    p2 = p1;
    while(*p1)
    {
        while(!issym(*p2))
        p2++;
        mknode(p1, p2-1, &S, flag);
        while(*p2 && issym(*p2))
            p2++;
        p1 = p2;
    }
}

void output(SqList *S)
{
    Node *p;
    int flag = 0;
    int num;
    printf(" = ");
    p = S->head->next;
    num = 0;
    while(p && p->Coef)
    {
        if(flag)
        {
            printf("%+d", p->Coef);
        }
        else
            printf("%d", p->Coef);
        if(p->Expn == 1)
        printf("x");
        else if(p->Expn >1)
        printf("x^%d", p->Expn);
        num++;
    }
    printf(";\n");
    printf("%d", num);
    p = S->tail;
    while(p->prior)
    {
        printf("%d %d ", p->Coef, p->Expn);
        p = p->prior;
    }
}

int main()
{
    char s[120];
    SqList S;
    InitSqlist(&S);
    scanf("%s", s);
    plus(s, &S);
    output(&S);
    return 0;
}



/*test 
1:
    input :(1+x)-(x)
    output:(1+x)-(x) = 1；
    1,1,0
2:
    (x+x^3)+(-x-x^3) = 0；  
    0
3:
    (x+x^1000)+(x^1000+x^2000) = x^2000+x+2x^1000；
    2,2,1000,1,2000
4:
    0+(x^-1+x^3) = x^3+x^-1；
    2,1,-1,1,3
5：
    (6x^-3-x+4.4x^2-1.2x^9)-(-6x^-3+5.4x^2+7.8x^15) = -7.8x^15-1.2x^9-x^2-x；
    4,-1,1,-1,2,-1.2,9,-7.8,15


*/


