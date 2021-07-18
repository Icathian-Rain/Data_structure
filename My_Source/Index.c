#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int Index(char *s, char *t, int pos)
{
    int len_s, len_t;
    len_s = strlen(s), len_t = strlen(t);
    int i = pos-1;
    int j = 0;
    while( i <= len_s-1 && j<=len_t-1)
    {
        if(s[i] == t[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i-j+1;
            j = 0;
        }
    }
    if(j >= len_t)
        return i-len_t+1;
    else
        return 0;
}



int main()
{
    char *s = "gggoggggg";
    char *t = "ggog";
    int pos = 1;
    printf("%d\n", Index(s,t, pos));
    return 0;

}