#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


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