//树的存储结构


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <math.h>
//双亲表示法
#define MAX_TREE_SIZE 100
typedef int TElemType;
typedef struct _PTNode //树结点结构
{
    TElemType data;
    int parent;        //双亲域
    int firstchild;    //长子域
    int rightsib       //右兄弟域
} PTNode;

typedef struct _Tree //树结构
{
    PTNode nodes[MAX_TREE_SIZE];
    int r,n;
} PTree;


//孩子表示法
//树的孩子表示法结构定义

typedef struct _CTNode  //孩子结点
{
    int child;
    struct _CTNode *next;
} CTNode;

typedef struct _CTBox    //表头结构
{
    TElemType data;
    CTNode * firstchild;
} CTBox;

typedef struct _CTree            //树结构
{
    CTBox nodes{MAX_TREE_SIZE};
    int r.n;
} CTree;

//树的孩子兄弟表示法结构定义

typedef struct _CSNode
{
    TElemType data;
    struct _CSNode *firstchild, *rightsib;
} CSNode;


//二叉链表
typedef struct _BiTNode //结点结构
{
    TElemType data;
    struct _BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
