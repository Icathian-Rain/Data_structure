#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void get_next(char *T, int *next)
{
    int i,j,len;
    len = strlen(T);
    i = 1;
    j = 0;
    next[0] = 0;
    while(i<len)
    {
        if(j == 0 || T[i-1] == T[j-1])
        {
            i++;
            j++;
            next[i-1] = j;
        }
        else
        {
            j = next[j-1];
        }
    }

}


void get_nextval(char *T, int *nextval)
{
    int i,j,len;
    len = strlen(T);
    i = 1;
    j = 0;
    nextval[0] = 0;
    while(i < len)
    {
        if(j == 0 || T[i-1] == T[j-1])
        {
            i ++;
            j++;
            if(T[i-1] != T[j-1])
                nextval[i-1] = j;
            else
                nextval[i-1] = nextval[j-1];
        }
        else
            j = nextval[j-1];

    }
}

int Index_KMP(char *S, char *T, int pos)
{
    int i = pos-1,len1,len2;
    int j = 0;
    int next[255];
    len1 = strlen(S), len2 = strlen(T);
    get_next(T, next);
    while(i < len1 && j <len2)
    {
        if(j == -1 || S[i] == T[j])
        {
            i ++;
            j ++;
        }
        else
        {
            j = next[j]-1;
        }
    }
    if(j >= len2)
        return i-len2+1;
    else
        return 0;



}


int main()
{
    
    char *T = "ababaaaba";
    int nextval[1000],len,i,j;
    len = strlen(T);
    get_nextval(T, nextval);
    for(i = 0; i<len; i++)
    printf("nextval[%d] = %d\n", i,nextval[i]);
    
   //test2:KMP算法
//    char *S = "googgooogleggg", *T = "google";
//    int pos = 1;
//    printf("%d",Index_KMP(S, T, pos));


    return 0;
}