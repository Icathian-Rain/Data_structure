#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef union
{
    char En;
    char Cn[4];
} ElemType;
//哈夫曼树的结点
typedef struct _HTNode
{
    int weight;                     //储存当前的权值
    int parent, lchild, rchild;     //储存双亲结点，左孩子，右孩子的位置
} HTNode, *HTree;

typedef struct _CodeNode
{
    ElemType data;
    int language;       //1为英文，0为英文
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

int IsEn()










int GetWeight(char *s, CodeTable *CT)
{
    //输入字符串s,编码表Code_Table;
    char *p = s;
    CodeNode *pc = NULL;;
    while (*p)
    {
        if(*p < 32 && *p > 126)
        {
            printf("Invald Code\n");
            p++;
            continue;
        }
        pc = CT->head->next;
        while (pc)
        {
            if(pc->data == *p)
                break;
            pc = pc->next;
        }
        if(pc)
            pc->weight ++;
        else
        {
            pc = (CodeNode *)malloc(sizeof(CodeNode));
            pc->data = *p;
            pc->weight = 1;
            pc->next = NULL;
            CT->tail->next = pc;
            CT->tail = pc;
            CT->num ++;
        }
        p++;
    }
}

void SortByWeight(CodeTable *CT)
{
    CodeNode *p, *q;
    int i, j;
    for(i = 0; i<CT->num - 1; i++)
    {
        p = CT->head;
        for(j = i; j<CT->num - 1; j++)
        {
            q = p->next;
            if(q->weight > q->next->weight)
            {
                p->next = q->next;
                q->next = q->next->next;
                p->next->next = q;
            }
            p = p->next;
        }
    } 
}


void SortByASCII(CodeTable *CT)
{
    CodeNode *p, *q;
    int i, j;
    for(i = 0; i<CT->num - 1; i++)
    {
        p = CT->head;
        for(j = i; j<CT->num - 1; j++)
        {
            q = p->next;
            if(q->data > q->next->data)
            {
                p->next = q->next;
                q->next = q->next->next;
                p->next->next = q;
            }
            p = p->next;
        }
    } 
}


void Select(HTree HT, int n, int *n1, int *n2)
{
    int i, *maxer;
    int flag1 = 1, flag2 = 1;
    for(i = 1; i<=n; i++)
    {
        if(!HT[i].parent)
        {
            if(flag1)
            {
                *n1 = i;
                flag1 = 0;
                continue;
            }
            else if(flag2)
            {
                *n2 = i;
                flag2 = 0;
                continue;
            }
            maxer = HT[*n1].weight > HT[*n2].weight ? n1 : n2;
            if(HT[i].weight <  HT[*maxer].weight)
            *maxer = i;
        }
    }
}

void HuffmanCoding(HTree *HT, CodeTable *CT)
{
    if(CT->num <= 1)
    return ;
    char cd[41];
    int m, i, c, f;
    int s1, s2;
    CodeNode *pc;
    m = 2* CT->num -1;
    *HT = (HTree)malloc((m+1) * sizeof(HTNode));
    for(i = 1, pc = CT->head->next; i<=CT->num; i++, pc = pc->next)
    {
        (*HT)[i].weight = pc->weight;
        (*HT)[i].lchild = 0;
        (*HT)[i].rchild = 0;
        (*HT)[i].parent = 0;
    }
    for( ; i<=m; i++)
    {
        (*HT)[i].weight = 0;
        (*HT)[i].lchild = 0;
        (*HT)[i].rchild = 0;
        (*HT)[i].parent = 0;
    }
    for(i = CT->num+1; i<=m; i++)
    {
        Select(*HT, i-1, &s1, &s2);
        (*HT)[s1].parent = i, (*HT)[s2].parent = i;
        (*HT)[i].lchild = s1; (*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
    for(i = 1, pc = CT->head->next; i<= CT->num; i++, pc = pc->next)
    {
        int n, start;
        n = 40;
        cd[n] = '\0';
        start = n;
        for(c = i, f = (*HT)[i].parent; f!= 0; c = f, f = (*HT)[f].parent)
        {
            if((*HT)[f].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
            pc->code = (char *)malloc(sizeof(char) * (n-start));
            strcpy(pc->code, &cd[start]);
        }
    }
}


void ShowTable(CodeTable *CT)
{
    CodeNode *p;
    p = CT->head->next;
    while(p)
    {
        printf(" '%c': weight:%d   code:%s\n", p->data, p->weight, p->code);
        p = p->next;
    }
    return ;
}

void ShowTree(CodeTable *CT, HTree *HT)
{
    CodeNode *p;
    int i;
    for(i = 1, p = CT->head->next; i<= CT->num; i++, p = p->next)
    {
        printf("序号:%d--W%d--//P%d//L%d//R%d//%c==>%s\n", i-1, (*HT)[i].weight,(*HT)[i].parent, (*HT)[i].lchild, (*HT)[i].rchild, p->data, p->code );
    }
    for(; i<=CT->num * 2-1; i++)
    {
        printf("序号:%d--W%d--//P%d//L%d//R%d//\n", i-1, (*HT)[i].weight,(*HT)[i].parent, (*HT)[i].lchild, (*HT)[i].rchild);
    }
}



void EnCode(char *s, char *cd, CodeTable *CT)
{
    CodeNode *pc;
    char *p;
    p = s;
    while(*p)
    {
        pc = CT->head->next;
        while(pc)
        {
            if(pc->data == *p)
            break;
            pc = pc->next;
        }
        if(pc)
            strcat(cd, pc->code);
        else
            printf("ERROR\n");
        p++;
    }
}


void DeCode(char *s, char *cd, CodeTable *CT)
{
    int i = 0;
    char code[10000];
    char *p1, *p2;
    CodeNode *pc;
    p1 = s;
    p2 = cd;
    while(*p2)
    {
        for(i = 0; ;i++)
        {
            code[i] = *p2;
            code[i+1] = '\0';
            p2++;
            pc = CT->head->next;
            while(pc)
            {
                if(!strcmp(code, pc->code))
                break;
                pc = pc->next;
            }
            if(pc)
            {
                *p1 = pc->data;
                printf("%c", *p1);
                p1++;
                break;
            }
        }
    }
    *p1 = '\0';
}





void DeCodebyTree(char *s, char *cd, HTree *HT, CodeTable *CT)
{
    int root,i, j;
    char *p1, *p2;
    CodeNode *pc;
    p1 = s, p2 = cd;
    root = 1;
    while(1)
    {
        if((*HT)[root].parent == 0)
        break;
        root++;
    }
    while(*p2)
    {
        i = root;
        while((*HT)[i].lchild != 0 || (*HT)[i].rchild != 0)
        {
            if(*p2 == '0')
            i = (*HT)[i].lchild;
            else
            i = (*HT)[i].rchild;
            p2++;
        }
        for(j = 1, pc=CT->head->next; j<i; j++, pc = pc->next);
        *p1 = pc->data;
        p1 ++;
    }
    *p1 = '\0';
    return ;
}



int main()
{
    CodeTable CT;
    HTree HT;
    FILE *fp;
    char *p, ch;
    char Plaintext[2001],Ciphertext[10001] = "",Translatetext[2001];
    char filename[100] = "C:\\Users\\Shooting stars\\Desktop\\Study\\C\\code\\Data_structure\\Experiment\\Experiment2\\src\\sampleE.txt";
    fp = fopen(filename, "r");
    if(!fp)
        printf("Error!\n");
    p = Plaintext;
    while((ch = fgetc(fp)) != -1)
    {
        *p++ = ch;
    }
    *p = '\0';
    InitCodeTable(&CT);
    GetWeight(Plaintext, &CT);
    // SortByWeight(&CT);
    SortByASCII(&CT);
    HuffmanCoding(&HT, &CT);
    // ShowTable(&CT);
    ShowTree(&CT, &HT);
    EnCode(Plaintext, Ciphertext, &CT);
    // DeCode(t, cd, &CT);
    DeCodebyTree(Translatetext, Ciphertext, &HT, &CT);
    printf("%s", Translatetext);
    return 0;
}