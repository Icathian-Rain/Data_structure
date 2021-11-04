#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Matrix.h"
#include "Functionh.h"

int ShowTable()
{
    char c;
    int flag;
    printf("Welcome to use Matrix Caulator!\n");
    printf("please input the function number:\n \
            1:add two Matrixs\n \
            2:sub two Matrixs\n  \
           3:plus two Matrixs\n \
            4:exit this system\n");
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
        default:
                    flag = 3;
                    break;
    }
    return flag;
}

int main()
{
    ShowTable();
    return 0;
}