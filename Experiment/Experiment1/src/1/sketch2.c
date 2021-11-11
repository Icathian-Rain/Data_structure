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
    double Coef; //系数
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

//符号栈
typedef struct _FlagStack
{
    char data[MAXSIZE];
    int top;
    int num;
} FlagStack;

void InitFlagStack(FlagStack *FS)
{
    FS->top = 0;
    FS->num = 0;
}

Status FSPush(FlagStack *FS, char e)
{
    if(FS->top == MAXSIZE - 1)
    {
        printf("Overflow\n");
        return OVERFLOW;
    }
    if(e == '-')
    FS->num ++;
    FS->data[FS->top] = e;
    FS->top ++;
}

Status FSPop(FlagStack *FS)
{
    if(FS->top == 0)
    {
        printf("Empty\n");
        return ERROR;
    }
    FS->top --;
    if(FS->data[FS->top-1] == '-')
    {
        FS->top --;
        FS->num --;
    }
}





void Mk_Point(SqList *S, double Coef, int Expn)
{
    Node *p, *q;
    if(!S->head->next)
    {
        p = (Node *)malloc(sizeof(Node));
        p->Coef = Coef;
        p->Expn = Expn;
        p->prior = S->head;
        p->next = NULL;
        S->head->next = p;
        S->tail = p;
    }
    else
    {
        q = S->head->next;
        while(q && q->Expn > Expn)
        {
            q = q->next;
        }
        if(q && q->Expn == Expn)
        {
            q->Coef += Coef;
        }
        else
        {
            p = (Node *)malloc(sizeof(Node));
            p->Coef = Coef;
            p->Expn = Expn;
            if(q)
            {
                p->next = q;
                p->prior = q->prior;
                q->prior->next = p;
                q->prior = p;
            }
            else
            {
                p->next = NULL;
                p->prior = S->tail;
                S->tail->next = p;
                S->tail = p;
            }
        }
    }
}


void func(char *s, SqList *S)
{
    double Coef,x;
    int flag1, flag2,point;
    int Expn;
    char *p;
    FlagStack FS;
    InitFlagStack(&FS);
    p = s;
    while(*p)
    {
        flag1 = 0;
        flag2 = 0;
        point = 0;
        Coef = 0.0;
        x = 1.0;
        Expn = 0;
        //读取某一项前的(), +, -
        while(*p == '(' || *p == ')' || *p == '-' || *p == '+')
        {
            if(*p == '-')
            {
                if(*(p+1) == '(')
                    FSPush(&FS, *p);
                else
                    flag1++;
            }
            if(*p == '(')
            FSPush(&FS, *p);
            if(*p == ')')
            FSPop(&FS);
            p++;
        }
        if(*p == '\0')
        break;
        while(*p>='0' && *p<='9' || *p == '.')
        {
            if(*p == '.')
            {
                point = 1;
                p++;
            }
            if(point)
            {
                x *= 0.1;
                Coef += (*p-'0') * x;
            }
            else
            {
                Coef *= 10;
                Coef += *p-'0'; 
            }
            p++;
        }
        if(*p == 'x')
        {
            if(abs(Coef) < 10e-6)
            Coef = 1.0;
            p++;
            if(*p == '^')
            {
                p++;
                while(*p == '(' || *p == ')' || *p == '+' || *p =='-')
                {
                    if(*p == '-')
                    flag2 = 1;
                    p++;
                }
                while(*p >= '0' && *p <= '9')
                {
                    Expn *= 10;
                    Expn += *p - '0';
                    p++;
                }
                if(flag2)
                    Expn = -Expn;
            }
            else
            {
                Expn = 1;
            }
        }
        else
        Expn = 0;
        if((FS.num+flag1) % 2)
            Coef = -Coef;
        Mk_Point(S, Coef, Expn);    
    }
}

void OutPut(SqList *S)
{
    Node *p;
    int flag = 0;
    int sum = 0;
    printf(" = ");
    p = S->head->next;
    while(p)
    {
        if(!abs(p->Coef) < 10e-6)           //如果系数不为0
        {
            if(p->Expn)                 //如果指数不为0
            {
                if(abs(p->Coef + 1)<10e-6)      //如果系数为-1
                {
                    printf("-");
                    flag = 1;
                }
                else if(abs(p->Coef - 1) < 10e-6)       //如果系数为+1
                {
                    if(flag)
                    printf("+");
                    else
                    flag = 1;
                }
                else
                {
                    if(flag)                //如果是第一个出现的
                    {
                        printf("%+lf", p->Coef);
                    }
                    else
                    {
                        if(p->Coef <0)
                        printf("-");
                        printf("%lf", p->Coef);
                        flag = 1;
                    }
                }
                printf("x");
                if(!abs(p->Expn-1) <10e-6)
                {
                    printf("^%d", p->Expn);
                }
            }
            else
            {
                if(abs(p->Coef - 1) < 10e-6)
                {
                    if(flag)
                        printf("+1");
                    else
                    {
                        printf("1");
                        flag = 1;
                    }
                }
                else if(abs(p->Coef + 1) < 10e-6)
                {
                    printf("-1");
                    flag = 1;
                }
                else
                {
                    if(flag)                //如果是第一个出现的
                    {
                        printf("%+lf", p->Coef);
                    }
                    else
                    {
                        if(p->Coef <0)
                        printf("-");
                        printf("%lf", p->Coef);
                        flag = 1;
                    }
                }
            }
            sum++;
        }
        p = p->next;
    }
    if(!sum)
    printf("0");
    printf("\n");
    printf("%d ", sum);
    p = S->tail;
    while(p != S->head)
    {
        if(!abs(p->Coef) < 10e-6)
            printf("%lf %d ", p->Coef, p->Expn);
        p = p->prior;
    }
}


int main()
{
    char s[120];
    scanf("%s", s);
    SqList S;
    InitSqlist(&S);
    func(s, &S);
    OutPut(&S);
    return 0;
}
