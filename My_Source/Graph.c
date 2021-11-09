#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

//定义状态Status
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;

//邻接矩阵

typedef char VertexType;        //顶点类型
typedef int EdgeType;           //边上的权值类型
#define MAXVEX 100              //最大顶点数
#define INFINITY 65535          //用65535代替∞
typedef struct _MGraph
{
    VertexType vexs[MAXVEX];
    EdgeType arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
} MGraph;

void CreateMGraph(MGraph *G)
{
    int i,j,k,w;
    printf("输入顶点数和边数\n");
    scanf("%d%d", &G->numVertexes, &G->numEdges);
    for(i = 0; i<G->numVertexes; i++)
    scanf(&G->vexs[i]);
    for(i = 0; i<G->numVertexes; i++)
        for(j = 0; j<G->numVertexes; j++)
        G->arc[i][j] = INFINITY;
    for(k = 0; k < G->numEdges; k++)
    {
        printf("输入边(vi,vj)的上标i，下标j和权w:\n");
        scanf("%d%d%d", &i, &j, &w);
        G->arc[i][j] = w;
        G->arc[j][i] = G[i][j];
    }
}

// 邻接表
typedef struct _EdgeNode         //边表结点
{
    int adjvex;
    EdgeType weight;
    struct _EdgeNode *next;
} EdgeNode;

typedef struct _VertexNode
{
    VertexType data;
    EdgeNode *firstedge;
} VertexNode, AdjList[MAXVEX];

typedef struct _GraphAdjList
{
    AdjList adjList;
    int numVertexes, numEdges;         //图中当前顶点数和边数
} GraphAdjList;

//建立图的邻接表结构
void CreatedALGraph(GraphAdjList *G)
{
    int i,j,k;
    EdgeNode *e;
    printf("输入顶点数和边数:\n");
    scanf("%d%d", &G->numVertexes, &G->numEdges);       //输入顶点数和边数
    for(i = 0; i < G->numVertexes; i++)
    {
        scanf(&G->adjList[i].data);         //输入顶点信息
        G->adjList[i].firstedge = NULL;
    }
    for(k = 0; k < G->numVertexes; k++)
    {
        printf("输入边(vi,vj)上的顶点序号:\n");
        scanf("%d%d", &i, &j);
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = j;
        e->next = G->adjList[i].firstedge;
        G->adjList[i].firstedge = e;

        e = (EdgeNode *)malloc(sizeof{EdgeNode});
        e->adjvex = i;
        e->next = G->adjList[j].firstedge;
        G->adjList[i].firstedge = e;
    }
}


typedef int boolean;        //boolean是布尔类型，其值是TRUE或FALSE
boolean visited[MAXVEX];    //访问标志的数组

//? 深度优先遍历递归算法
// 邻接矩阵类型
void DFS(MGraph G, int i)
{
    int j;
    visited[i] = TRUE;
    printf("%c ", G.vexs[i]);
    for(j = 0; j < G.numVertexes; j++)
        if(G.arc[i][j] == 1 && !visited[j])
            DFS(G,j);
}

void DFSTraverse(MGraph G)
{
    int i;
    for(i = 0; i < G.numVertexes; i++)
        visited[i] = FALSE;
    for(i = 0; i < G.numVertexes; i++)
        if(!visited[i])
            DFS(G, i);
}

//? 广度遍历算法
// 邻接矩阵结构

//队列结构
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

void BFSTraverse(MGraph G)
{
    int i,j;
    EnQueue Q;
    for(i = 0; i<G.numVertexes; i++)
        visited[i] = FALSE;
    InitQueue(&Q);
    for( i = 0; i< G.numVertexes; i++)
    if(!visited[i])
    {
        visited[i] = TRUE;
        printf("%c", G.vexs[i]);
        EnQueue(&Q, i);
        while(!Que)

    }





}
