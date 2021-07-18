
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//?二叉树结点
//二叉树结构

#define MAX_TREE_SIZE 100
typedef char TElemType;

//二叉链表

typedef struct _BiTNode //结点结构
{
    TElemType data;
    struct _BiTNode *lchild, *rchild;
} BiTNode, *BiTree;


//二叉树的二叉线索存储结构定义
typedef enum {Link, Thread} PointerTag ;   //Link ==0表示左右孩子指针
                                            //Thread == 1表示指向前驱或后驱的线索
typedef struct _BiThrNode       //二叉线索存储结点结构
{
    TElemType data;
    struct _BiThrNode *lchild, *rchild;
    PointerTag LTag;
    PointerTag RTag;
} BiThrNode, *BiThrTree;


//?二叉树的遍历
//二叉树的遍历原理
//二叉树的遍历(traversing binary tree)是指从根结点出发，按照某种次序一次访问二叉树中所有结点，使得每个结点被访问一次且仅被访问一次

/*1.前序遍历
    规则是若二叉树为空，则空操作返回，否则先访问根结点，
    然后前序遍历左子树，再前序遍历右子树
*/
void PreOrderTraverse(BiTree T)
{
    if(T == NULL)
        return;
    printf("%c", T->data);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

/*2.中序遍历
    规则是若树为空，则空操作返回，否则从根结点开始（注意并不是
    先访问根结点），中序遍历根结点的左子树，然后是访问根结点，
    左后中序遍历右子树
*/

void InOrderTraverse(BiTree T)
{
    if(T == NULL)
        return;
    InOrderTraverse(T->lchild);
    printf("%c", T->data);
    InOrderTraverse(T->rchild);
}

/*3.后序遍历
    规则是若树为空，则空操作返回，否则从左到右先叶子后结点的方式
    遍历访问左右子树，最后是访问根结点。
*/

void PostOrderTraverse(BiTree T)
{
    if(T ==NULL)
        return;
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    printf("%c", T->data);
    
}

/*4.层序遍历
    规则是若树为空，则空操作返回，否则从树的第一层，也就是根结点
    开始访问，从上而下逐层遍历，在同一层中，按从左到右的顺序对结
    点逐个访问。
*/

//?二叉树的建立
//将原二叉树变为扩展二叉树

//按前序输入二叉树的中结点的值（一个字符）
//#表示空树，构造二叉树表示二叉树T0

void CreatBiTree(BiTree *T)
{
    TElemType ch;
    scanf("%c", &ch);
    if(ch == '#')
        *T = NULL;
    else
    {
        *T = (BiTree) malloc (sizeof(BiTNode));
        if(! *T)
            exit(OVERFLOW);
        (*T)->data = ch;
        CreatBiTree(&(*T)->lchild);
        CreatBiTree(&(*T)->rchild);
    }
}

//线索二叉树的构造（初步）
void CreatBiThrTree(BiThrTree *T)
{
    TElemType ch;
    scanf("%c", &ch);
    if(ch == '#')
        *T = NULL;
    else
    {
        *T = (BiThrTree) malloc (sizeof(BiThrNode));
        if(! *T)
            exit(OVERFLOW);
        (*T)->data = ch;
        (*T)->LTag = (*T)->RTag = Link;
        CreatBiThrTree(&(*T)->lchild);
        CreatBiThrTree(&(*T)->rchild);
    }    
}



//?中序遍历线索化的递归函数
BiThrTree pre;          //全局变量，始终指向刚刚访问过的结点
//中序遍历进行中序线索化
void InThreading (BiThrTree p)
{
    if(p)
    {
        InThreading(p->lchild);
        if(!p->lchild)
        {
            p->LTag = Thread;
            p->lchild = pre;
        }
        if(pre != NULL && !pre->rchild)
        {
            pre->RTag = Thread;
            pre->rchild = p;
        }
        pre = p;
        InThreading(p->rchild);
    }
}

//遍历添加头指针
void InOrder_addhead(BiThrTree T, BiThrTree *T_head)
{
    *T_head = (BiThrTree) malloc (sizeof(BiThrNode));
    (*T_head) ->lchild = T;
    (*T_head) ->LTag = Link;
    (*T_head) ->rchild = NULL;
    (*T_head) ->RTag = Thread;
    BiThrTree p;
    p = T;
    while(p->lchild)
    p = p->lchild;
    p ->lchild = *T_head;
    p ->LTag  = Thread;
    p = T;
    while(p->rchild)
    p = p->rchild;
    p ->rchild = *T_head;
    p ->RTag = Thread;
    (*T_head) ->rchild = p;
}

//中序遍历
void InOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p;
    p = T->lchild;
    while(p != T)
    {
        while(p->LTag == Link)
        p = p->lchild;
        printf("%c",p->data);
        while(p->RTag == Thread&& p->rchild != T)
        {
            p = p->rchild;
            printf("%c", p->data);
        }
        p = p->rchild;
    }
}

int main()
{
    /*
    BiTree T;
    CreatBiTree(&T);
    printf("\n前序遍历为:");
    PreOrderTraverse(T);
    printf("\n中序遍历为:");
    InOrderTraverse(T);
    printf("\n后序遍历为:");
    PostOrderTraverse(T);
    */

    BiThrTree T,T_head;
    CreatBiThrTree(&T);
    InThreading(T);
    InOrder_addhead(T, &T_head);
    InOrderTraverse_Thr(T_head);
    return 0;

 
}
