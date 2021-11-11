#ifndef _MATRIX_H_
#define _MATRIX_H_

//定义状态Status
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100

typedef int Status;
typedef int ElemType;


typedef struct _Triple
{
    int i;      //行号
    int j;      //列号
    ElemType e;     //数据
} Triple;

typedef struct _TSMatrix
{
    int mu;         //行数
    int nu;         //列数
    int tu;         //非零元个数    
    Triple data[MAXSIZE];       //三元组数组
    int SqPos[MAXSIZE];         //每行的第一个元素的位置
}  TSMatrix;



#endif      //_MATRIX_H_