//?头文件区
//标准头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
//自编头文件
#include "Matrix.h"         //存放三元组，稀疏矩阵的定义
#include "Functionh.h"      //存放函数声明
         
//?函数区

int ShowTable()
{
    //print table界面
    //将得到的输入以flag返回，flag == 1为加法, flag == 0为减法, flag == 2为乘法, flag == 3为退出
    char c;
    int flag;
    printf("Welcome to use Matrix Caulator!\n");            //打印开始菜单
    printf("please input the function number:\n \
            1:add two Matrixs\n \
            2:sub two Matrixs\n  \
           3:plus two Matrixs\n \
            4:clear the screen\n \
            input others to exit the application\n");     //输入1加法，2为减法，3为乘法，4为清屏
    c = getchar();
    switch(c)
    {
        case '1':   flag = 1;
                    break;
        case '2':   flag = 0;
                    break;
        case '3':
                    flag = 2;
                    break;
        case '4':
                    flag = 4;
                    break;
        default:
                    flag = 3;
                    break;
    }
    return flag;
}


int Cmp(Triple p1, Triple p2)     
{
    //比较两个三元组的前后顺序
    int flag = 1;
    if(p1.i > p2.i)
    {
        flag = 2;
    }
    else if(p1.i == p2.i)
    {
        if(p1.j == p2.j)
        flag = 0;
        else if(p1.j > p2.j)
        flag = 2;
    }
    return flag;
}


Status inputMatrix(TSMatrix *M)
{
    //将输入的一般矩阵以三元组的稀疏矩阵存储
    static int num = 1;     //num统计输入矩阵的个数
    int mu, nu, i, j, t, M_row;
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
    //构建三元组的稀疏矩阵
    // 初始化
    M->mu = mu;
    M->nu = nu;
    M_row = 0;
    t = 0;
    //初始化，令每行第一个元素均为非零元个数+1
    for(i = 0; i<=mu; i++)
    {
        M->SqPos[i] = M->tu+1;
    }
    for(i = 1; i<=mu; i++)
    {    
        for(j = 1; j<=nu; j++)
        {
            int x = (i-1)*nu + j;
            if(N[x] != 0)       //若N[i][j]为非零元，则存入M->data中
            {
                t++;
                M->data[t].i = i;
                M->data[t].j = j;
                M->data[t].e = N[x];
                while(M_row < i)        //构建M->Sqpos
                {                       //若某一行无元素，则其为下一行开始元素的位置
                    M_row ++;   
                    M->SqPos[M_row] = t;
                }
            }
        }
    }
    num ++;
    return 1;
}

Status ADDANDSUB_TSM(TSMatrix *M, TSMatrix *N, TSMatrix *Q, int f)
{
    if(M->mu != N->mu || M->nu != N->nu)
    {
        return ERROR;
    }
    Q->mu = M->mu, Q->nu= M->nu;        //初始化
    Triple *p;                          //用于赋值
    int t1 = 1, t2 = 1, end, i;         //记录遍历个数
    int Q_row = 0;
    Q->tu = 0;
    //初始化Q->SqPos
    for(i = 0; i<=Q->mu; i++)
    {
        Q->SqPos[i] = M->tu+1;
    }
    while(t1 <= M->tu && t2 <= N->tu)
    {
        int flag = Cmp(M->data[t1], N->data[t2]) ;
        //判断M->data[t1]和M->data[t2]的前后关系
        if(flag == 0)
        {
            //若在同一个位置，则相加减
            int x;
            if(f)
            {
                x = M->data[t1].e + N->data[t2].e;
            }
            else
            {
                x = M->data[t1].e - N->data[t2].e;
            }
            //计算结果不为0则存入
            if(x)
            {
                Q->tu ++;
                Q->data[Q->tu].e = x;
                Q->data[Q->tu].i = M->data[t1].i;
                Q->data[Q->tu].j = M->data[t1].j;
                while (Q_row < Q->data[Q->tu].i)
                {
                    Q_row ++;
                    Q->SqPos[Q_row] = Q->tu;
                }
            }
            t1++, t2++;
        }
        else 
        {
            if(flag == 1)           //M->data[t1]在前则将其直接存入
            {
                p = &M->data[t1];
                t1++;            
            }
            else                    //反之则将N->data[t2]存入
            {
                p = &N->data[t2];
                t2++;        
            }
            Q->tu ++;
            Q->data[Q->tu].e = p->e;
            Q->data[Q->tu].i = p->i;
            Q->data[Q->tu].j = p->j;
            while (Q_row < Q->data[Q->tu].i)
            {
                Q_row ++;
                Q->SqPos[Q_row] = Q->tu;
            }
        }
    }
    while(t1 <= M->tu)          //将多出的直接存入
    {
        Q->tu ++;
        Q->data[Q->tu].e = M->data[t1].e;
        Q->data[Q->tu].i = M->data[t1].i;
        Q->data[Q->tu].j = M->data[t1].j;
        t1 ++;
        while (Q_row < Q->data[Q->tu].i)
        {
            Q_row ++;
            Q->SqPos[Q_row] = Q->tu;
        }        
    }
    while(t2 <= N->tu)      //同上
    {
        Q->tu ++;
        Q->data[Q->tu].e = N->data[t2].e;
        Q->data[Q->tu].i = N->data[t2].i;
        Q->data[Q->tu].j = N->data[t2].j;        
        t2++;
        while (Q_row < Q->data[Q->tu].i)
        {
            Q_row ++;
            Q->SqPos[Q_row] = Q->tu;
        }
    }
    return OK;
}



Status Mul_TSM(TSMatrix *M, TSMatrix *N, TSMatrix *Q)
{
    if(M->nu != N->mu)
    {
        return ERROR;
    }
    //初始化
    Q->mu = M->mu;  
    Q->nu = N->nu;
    Q->tu = 0;
    int i;
    int M_row, N_row;           //M的行与N的行
    int SqPos2_M, SqPos_M;      //限定M某一行内的
    int SqPos2_N, Sqpos_N;      //限定N某一行
    for(M_row = 1; M_row <= M->mu; M_row++)
    {
        int *QElem = (int *)malloc(sizeof(int) * (Q->nu+1));    //初始化QElem数组
        for(i = 1; i<=Q->nu; i++)
        {
            QElem[i] = 0;
        }
        Q->SqPos[M_row] = Q->tu+1;  //记录其Q->SqPos
        //求M_row行最后一个元素
        if(M_row < M->mu)           
            SqPos2_M = M->SqPos[M_row + 1];
        else
            SqPos2_M = M->tu + 1;
        //遍历每一个元素
        for(SqPos_M = M->SqPos[M_row]; SqPos_M < SqPos2_M; SqPos_M++)
        {
            N_row = M->data[SqPos_M].j;
            //求N的N_row行最后一个元素
            if(N_row < N->mu)
                SqPos2_N = N->SqPos[N_row+1];
            else
                SqPos2_N = N->tu+1;
            int SqPos_N;
            //遍历相乘，存入QElem数组中
            for(SqPos_N = N->SqPos[N_row]; SqPos_N < SqPos2_N; SqPos_N++)
            {
                int col = N->data[SqPos_N].j;
                QElem[col] += M->data[SqPos_M].e * N->data[SqPos_N].e;
            }
        }
        //将数组中的数据存入Q->data中
        int col;
        for(col = 1; col<=Q->nu;col++)
        {
            if(QElem[col] != 0)
            {
                Q->tu++;
                Q->data[Q->tu].i = M_row;
                Q->data[Q->tu].j = col;
                Q->data[Q->tu].e = QElem[col]; 
            }
        }
    }
    return OK;

}



void Display(TSMatrix *M)
{
    //将以三元组存储的稀疏矩阵以一般矩阵的形式输出
    int i, j, t;
    t = 1;
    printf("The result is :\n");
    for(i = 1; i<=M->mu; i++)
    {
        //从每一行头指针开始遍历
        for( j = 1; j<=M->nu; j++)
        {
            if(t <= M->tu && i == M->data[t].i && j == M->data[t].j)//若未到结尾且列数相同则输出非0 元
            {
                printf("%4d", M->data[t].e);
                t++;
            }
            else printf("   0");    //否则输出0元
            if(j<M->nu) 
                printf(" ");
            else
                printf("\n");
        }
    }
}



int main()
{
    int flag;
    int SFlag;
    while(1)
    {
        flag = ShowTable();
        if(flag == 3)
            break;
        else if(flag == 4)
        {
            getchar();
            system("cls");
        }
        else
        {
            TSMatrix M, N, Q;
            inputMatrix(&M);
            inputMatrix(&N);
            if(flag == 2)
            {
                SFlag = Mul_TSM(&M, &N, &Q);
                if(!SFlag)
                {
                    printf("The Two Matrix is not match\n");
                }
            }
            else
            {
                SFlag = ADDANDSUB_TSM(&M, &N, &Q, flag);
                if(!SFlag)
                {
                    printf("The Two Matrix is not match\n");
                }
            }
            Display(&Q);
        }
    }
    printf("Thanks!\n");
    system("pause");
    return 0;
}