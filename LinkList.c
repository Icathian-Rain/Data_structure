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

typedef struct _List
{
    Node *head;
    Node *tail;
} List;