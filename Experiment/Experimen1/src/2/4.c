
//?头文件区
//标准头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


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


void InputCrossM(CrossM *M);
Status transpose(CrossM *M);
Status Display(CrossM *M);


void InputCrossM(CrossM *M)
{
    //将输入的一般矩阵以十字矩阵链表的稀疏矩阵存储
    static int num = 1;
    //num统计输入矩阵的个数
    int mu, nu, i, j;
    int *N;
    //N 存储一般矩阵
    printf("Please Input the %d's mu and nu:\n", num);
    //读入行列
    scanf("%d %d", &mu, &nu);
    //构建一般矩阵，并统计非0项的个数
    N = (int *)malloc(sizeof(int)*((mu*nu)+1));
    printf("Please Input the %d's Matrix:\n", num);
    M->tu = 0;
    for(i = 1; i<=mu; i++)
    for(j = 1; j<=nu; j++)
    {
        int x = (i-1)*nu + j;
        scanf("%d", &N[x]);
        if(N[x] != 0)
        M->tu++;
    }
    getchar();
    //构建十字矩阵链表的稀疏矩阵
    M->mu = mu;
    M->nu = nu;
    //构建行头指针数组
    M->rhead = (OLNode **)malloc(sizeof(OLNode *) * (M->mu + 1));
    //构建列头指针数组
    M->chead = (OLNode **)malloc(sizeof(OLNode *) * (M->nu +1 ));
    //初始化行列头指针数组
    for(i = 1; i<=mu; i++)
    {
        M->rhead[i] = NULL;
    }
    for(i = 1; i<=nu; i++)
    {
        M->chead[i] = NULL;
    }
    OLNode *p = NULL;
    OLNode *q = NULL;
    for(i = 1; i<= M->mu; i++)
    {
        for(j = 1; j <= M->nu; j++)
        {
            int x = (i-1)*nu + j;
            if(N[x] != 0)   //将一般矩阵中的非0项存入十字链表
            {
                p = (OLNode *)malloc(sizeof(OLNode));   //动态内存分配一块内存
                p->i = i;
                p->j = j;
                p->e = N[x];
                if(!M->rhead[i])    //判断是否是第一个
                {
                    p->right = M->rhead[i];
                    M->rhead[i] = p;
                }
                else
                {
                    for(q = M->rhead[i]; q->right && q->right->j < j; q = q->right);    //将q移至p的前一个位置
                    p->right = q->right;
                    q->right = p;
                }
                //同行操作类似
                if(!M->chead[j] || M->chead[j]->i > i)
                {
                    p->down = M->chead[j];
                    M->chead[j] = p;
                }
                else
                {
                    for(q = M->chead[j]; (q->down) && q->down->i < i; q = q->down);    
                    p->down = q->down;
                    q->down = p;
                }
                
            }
        }
    }
    free(N);
}


Status transpose(CrossM *M)
{
    //通过十字链表实现转置
    OLNode *p, *ptemp, *save;   //p用于遍历，ptemp和save用于交换down 和right
    OLNode **p1;                //用于free原来的行列头指针数组
    int i,j,temp;               //temp用于交换行,列
    //将每一个结点的行列值互换，down和right互换
    for(i = 1; i<=M->mu; i++)
    {
        p = M->rhead[i];
        while(p)
        {
            temp = p->i;
            p->i = p->j;
            p->j = temp;
            save = p;
            p = p->right;
            ptemp = save->right;
            save->right = save->down;
            save->down = ptemp;
        }
    }
    //将稀疏矩阵的行列数互换
    temp = M->mu;
    M->mu = M->nu;
    M->nu = M->mu;
    //构建新的行列头指针数组
    OLNode** newrhead = (OLNode**)malloc(sizeof(OLNode *) * (M->mu + 1));
    OLNode** newchead = (OLNode**)malloc(sizeof(OLNode *) * (M->nu + 1));
    //将原行头指针赋给新列头指针
    //将原列头指针赋给新行头指针
    for(i = 1; i<= M->mu; i++)
    {
        newrhead[i] = M->chead[i];
    }
    for(i = 1; i<= M->nu; i++)
    {
        newchead[i] = M->rhead[i];
    }
    //将原行列头指针数组释放
    p1 = M->rhead;
    free(p1);
    p1 = M->chead;
    free(p1);
    //赋值
    M->rhead = newrhead;
    M->chead = newchead;
    return OK;

}

Status Display(CrossM *M)
{
    //将以十字链表存储的稀疏矩阵以一般矩阵的形式输出
    int i, j, t;
    t = 1;
    printf("The result is :\n");
    for(i = 1; i<=M->mu; i++)
    {
        //从每一行头指针开始遍历
        OLNode *p = M->rhead[i];
        for(j = 1; j<=M->nu; j++)
        {
            if(p && p->j == j)//若未到结尾且列数相同则输出非0 元
            {
                printf("%4d", p->e);
                p = p->right;
            }
            else        //否则输出0元
            {
              printf("   0");  
            }
            if(j < M->nu)
                printf(" ");
            else
                printf("\n");
        }
    }
    return OK;
}


int main()
{
    CrossM M;
    InputCrossM(&M);
    transpose(&M);
    Display(&M);
    system("pause");
    return 0;
}