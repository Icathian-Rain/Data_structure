#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//数据类型为char *
typedef char ElemType;
//哈夫曼树的结点
//第一个空间不用于存储
typedef struct _HTNode
{
    int weight;                     //储存当前的权值
    int parent, lchild, rchild;     //储存双亲结点，左孩子，右孩子的位置
} HTNode, *HTree;
typedef struct _CodeNode
{
    ElemType data[5];
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
    //初始化CodeTable，CT = 待初始化的CodeTable的地址
    CT->head = (CodeNode *)malloc(sizeof(CodeNode));
    CT->head->next = NULL;
    CT->tail = CT->head;
    CT->num = 0;
}


int GetNum(unsigned char p)
{
    int i;
    for(i = 0; ;i++)
    if( ((p << i) >> 7 & 1) == 0)
    {
        if(i == 0)
        return 1;
        return i;
    }
}



int GetWeight(char *s, CodeTable *CT)
{
    //输入字符串s,编码表Code_Table;
    int num;
    ElemType data[5];
    char *p = s;
    CodeNode *pc = NULL;
    while (*p)
    {
        num = GetNum(*p);
        int i;
        for(i = 0; i<num; i++)
        {
            data[i] = *p;
            p++;
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
void SortByWeight(CodeTable *CT)        
{
    //对传入的编码表依据权重排序
    //CT = 传入的编码表
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

void Select(HTree HT, int n, int *n1, int *n2)
{
    //从哈夫曼树未接入的结点中选取权重最小的两个结点
    //HT = 哈夫曼树数组，n = 范围， n1传回最小的两个结点中的一个，n2传回最小的两个结点中的另一个
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
    //对字符表进行哈夫曼编码，构建哈夫曼树
    //HT = 构建的哈夫曼树的首地址, CT为字符表
    if(CT->num <= 1)    //若总字符数小于1则返回
    return ;
    int m, i, c, f;     
    int s1, s2;
    CodeNode *pc;
    m = 2* CT->num -1;  
    *HT = (HTree)malloc((m+1) * sizeof(HTNode));                //初始化哈夫曼树，结点数为叶子结点的2倍-1，首结点不存储
    for(i = 1, pc = CT->head->next; i<=CT->num; i++, pc = pc->next)     //初始化叶子结点及，字符结点
    {
        (*HT)[i].weight = pc->weight;
        (*HT)[i].lchild = 0;
        (*HT)[i].rchild = 0;
        (*HT)[i].parent = 0;
    }
    for( ; i<=m; i++)                                                   //初始化非叶子结点
    {
        (*HT)[i].weight = 0;
        (*HT)[i].lchild = 0;
        (*HT)[i].rchild = 0;
        (*HT)[i].parent = 0;
    }
    for(i = CT->num+1; i<=m; i++)                   //构建哈夫曼树
    {
        Select(*HT, i-1, &s1, &s2);                 //选取权重最小的两个结点
        (*HT)[s1].parent = i, (*HT)[s2].parent = i; //双亲为最新的结点
        (*HT)[i].lchild = s1; (*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
    char *cd;        //存储编码串
    int n = CT->num;
    cd = (char *)malloc(sizeof(char) * n);
    for(i = 1, pc = CT->head->next; i<= CT->num; i++, pc = pc->next)        //得到编码串
    {
        int start;
        cd[n] = '\0';
        start = n;
        for(c = i, f = (*HT)[i].parent; f!= 0; c = f, f = (*HT)[f].parent)  //从结点向根倒序编码
        {
            if((*HT)[f].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
            pc->code = (char *)malloc(sizeof(char) * (n-start));
            strcpy(pc->code, &cd[start]);           //将编码值赋给字符表中的code
        }
    }
}

void EnCodeByCT(char *s, char *cd, CodeTable *CT)
{
    //通过字符表解码
    //s = 目的字符串的地址, cd = 存储密文串的地址, CT = 字符表
    CodeNode *pc;
    int num, i;
    char data[5];
    char *p;
    p = s;
    while(*p)
    {
        num = GetNum(*p);
        for(i = 0; i<num; i++)
        {
            data[i] = *p;
            p++;
        }
        data[num] = '\0';
        pc = CT->head->next;
        while(pc)
        {
            if(!strcmp(data, pc->data))
            break;
            pc = pc->next;
        }
        if(pc)
            strcat(cd, pc->code);
        else
            printf("ERROR\n");
    }
}
void DeCodeByCT(char *s, char *cd, CodeTable *CT)
{
    //通过字符表CT进行解码
    //s = 目的串地址，cd = 密文串地址， CT = 字符表
    int i = 0;
    char code[10000];
    char *p2;
    CodeNode *pc;
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
                if(!strcmp(code, pc->code)) //匹配串与CT中的代码表
                break;
                pc = pc->next;
            }
            if(pc)
            {
                strcat(s, pc->data);
                break;
            }
        }
    }
}

void DeCodebyTree(char *s, char *cd, HTree *HT, CodeTable *CT)
{
    //通过哈夫曼树解码
    //s = 目的串地址， cd = 密文串地址, HT = 哈夫曼树地址, CT = 字符表的地址
    int root,i, j;
    char *p2;
    CodeNode *pc;
    p2 = cd;
    root = 2 * CT->num - 1;
    while(*p2)
    {
        i = root;
        while((*HT)[i].lchild != 0 || (*HT)[i].rchild != 0)     //判断是否为叶子结点
        {
            if(*p2 == '0')
            i = (*HT)[i].lchild;
            else
            i = (*HT)[i].rchild;
            p2++;
        }
        for(j = 1, pc=CT->head->next; j<i; j++, pc = pc->next);
        strcat(s, pc->data);
    }
    return ;
}


void ShowTable(CodeTable *CT)
{
    //输出CodeTable
    //CT = 
    CodeNode *p;
    p = CT->head->next;
    while(p)
    {
        printf(" '%s': weight:%d \n", p->data, p->weight);
        p = p->next;
    }
    return ;
}

void ShowTree(CodeTable *CT, HTree *HT)
{
    //输出哈夫曼树
    //CT = 字符表， HT = 哈夫曼树
    CodeNode *p;
    int i;
    for(i = 1, p = CT->head->next; i<= CT->num; i++, p = p->next)
    {
        printf("序号:%d--W%d--//P%d//L%d//R%d//%s==>%s\n", i-1, (*HT)[i].weight,(*HT)[i].parent, (*HT)[i].lchild, (*HT)[i].rchild, p->data, p->code );
    }
    for(; i<=CT->num * 2-1; i++)
    {
        printf("序号:%d--W%d--//P%d//L%d//R%d//\n", i-1, (*HT)[i].weight,(*HT)[i].parent, (*HT)[i].lchild, (*HT)[i].rchild);
    }
}

int main()
{
    // system("chcp 65001");
    //定义变量
    CodeTable CT;
    HTree HT;
    FILE *fp;
    char *p, ch;
    char Plaintext[10000],Ciphertext[20001] = "",Translatedtext[10000];
    char filename[200] = "C:\\Users\\Shooting stars\\Desktop\\Study\\C\\code\\Data_structure\\Experiment\\Experiment2\\src\\sampleCUTF8.txt";
    //从文件内读入字符串，保存在Plaintext里
    fp = fopen(filename, "r");
    if(!fp)
        printf("Error!\n");
    p = Plaintext;
    while((ch = fgetc(fp)) != -1)
    {
        *p++ = ch;
    }
    *p = '\0';
    //编码
    //初始化编码表
    InitCodeTable(&CT);
    //得到权重
    GetWeight(Plaintext, &CT);
    //排序
    SortByWeight(&CT);
    //哈夫曼编码
    HuffmanCoding(&HT, &CT);
    //编码明文
    EnCodeByCT(Plaintext, Ciphertext, &CT);
    printf("%s", Ciphertext);
    printf("\n");
    //输出字符表与哈夫曼树
    // ShowTable(&CT);
    ShowTree(&CT, &HT);
    //解码
    // DeCodeByCT(Translatedtext, Ciphertext, &CT);
    DeCodebyTree(Translatedtext, Ciphertext, &HT, &CT);
    //输出解码后的密文
    printf("%s", Translatedtext);
    return 0;
}
