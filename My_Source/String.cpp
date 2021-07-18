#include<iostream>
#include<string>
using namespace std;

//朴素的模式匹配算法

//返回子串R在主串S中第pos个字符之后的位置。若不存在，则函数返回值为0

int Index(string S, string T, int pos)
{
    int i = pos;
    int j = 1;
    while(i<= S[0] && j<= T[0])
    {
        if(S[i] == T[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i-j+2;
            j = 1;
        }
    }
    if(j >T[0])
    return i-T[0];
    else
    return 0;



}