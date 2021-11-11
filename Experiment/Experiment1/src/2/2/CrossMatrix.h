#ifndef CROSSMATRIX_H_
#define CROSSMATRIX_H_

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100

typedef int Status;
typedef int ElemType;

typedef struct _OLNode      //十字链表结点结构
{
    /* data */
    int i,j;        //存储行号
    ElemType e;     //存放数据  
    struct _OLNode *down, *right;       //右指针和下指针
} OLNode;


typedef struct _CrossM
{
    OLNode **rhead, **chead;        //行列头指针数组，动态分配
    int mu, nu, tu;                 //行列数和非零元的个数
} CrossM;


#endif // CROSSMATRIX_H_