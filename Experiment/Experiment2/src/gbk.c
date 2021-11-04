#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef char ElemType;

typedef struct _CodeNode
{
    ElemType data[3];
    int weight;
    char *code;
    struct _CodeNode *next;
} CodeNode;

typedef struct _CodeTable
{
    CodeNode *head;
    CodeNode *tail;
    int num;
} CodeTable;

void InitCodeTable(CodeTable *CT)
{
    CT->head = (CodeNode *)malloc(sizeof(CodeNode));
    CT->head->next = NULL;
    CT->tail = CT->head;
    CT->num = 0;
}


int GetNum(unsigned char p)
{
    return ((p>>7) & 1);
}



int GetWeight(char *s, CodeTable *CT)
{
    //ÊäÈë×Ö·û´®s,±àÂë±íCode_Table;
    int num;
    ElemType data[2];
    char *p = s;
    CodeNode *pc = NULL;
    while (*p)
    {
        int num = GetNum(*p) + 1;
        int i;
        for(i = 0; i<num; i++)
        {
            data[i] = *p++;
        }
        data[i] = '\0';
        pc = CT->head->next;
        while (pc)
        {
            if(!strcmp(pc->data, data))
                break;
            pc = pc->next;
        }
        if(pc)
            pc->weight ++;
        else
        {
            pc = (CodeNode *)malloc(sizeof(CodeNode));
            strcpy(pc->data, data);
            pc->weight = 1;
            pc->next = NULL;
            CT->tail->next = pc;
            CT->tail = pc;
            CT->num ++;
        }
    }
}


void ShowTable(CodeTable *CT)
{
    CodeNode *p;
    p = CT->head->next;
    while(p)
    {
        printf(" '%s': weight:%d \n", p->data, p->weight);
        p = p->next;
    }
    return ;
}

int main()
{
    system("chcp 936");
    char s[100] = "yyds,¾ø¾ø×Ó£¬ÇÌjiojio\n";
    CodeTable CT;
    InitCodeTable(&CT);
    GetWeight(s, &CT);
    ShowTable(&CT);
    printf("%s", s);
    return 0;
}
