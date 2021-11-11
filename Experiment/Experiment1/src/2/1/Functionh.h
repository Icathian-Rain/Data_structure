#ifndef FUNCTIONH_H_
#define FUNCTIONH_H_

int ShowTable();
int Cmp(Triple p1, Triple p2);
Status inputMatrix(TSMatrix *M);
Status ADDANDSUB_TSM(TSMatrix *M, TSMatrix *N, TSMatrix *Q, int f);
Status Mul_TSM(TSMatrix *M, TSMatrix *N, TSMatrix *Q);
void Display(TSMatrix *TSM);





#endif