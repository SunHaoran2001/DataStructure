#include <iostream>
#include <cstring>
using namespace std;

typedef struct BiNode
{
    int data;
    struct BiNode *lchild = NULL, *rchild = NULL;
} BiNode, *BiTree;

char pre[30];
char in[30];
/*
BiTree Create(int i, int j, int k) //0 len-1 0
{
    BiTree root = new BiNode;
    root->data = pre[k];
    if (i == j)
        return root;
    int t = i;
    while (in[t] != pre[k])
        t++;
    if (t - 1 >= i)
        root->lchild = Create(i, t - 1, k + 1);
    if (t + 1 <= j)
        root->rchild = Create(t + 1, j, k + t - i + 1);
    return root;
}
*/
BiTree CreateTree(char pre[], char in[], int s, int e, int m, int n)
{
    int indexh = 0;
    for (int i = m; i <= n; i++)
    { //在中序遍历中找到根结点的位置
        if (in[i] == pre[s])
        {
            indexh = i;
            break;
        }
    }
    BiTree p = new BiNode;
    p->data = pre[s];
    int leftlength = indexh - m;  //确定左子树数组的长度
    int rightlength = n - indexh; //确定右子树数组的长度
    if (indexh == m)
    { //判断左子树是为空，若根结点位于中序遍历序列最前面，说明根结点前面没有数字了，自然左结点为空
        p->lchild = NULL;
    }
    else
    {
        p->lchild = CreateTree(pre, in, s + 1, s + leftlength, m, indexh - 1); //递归构建左子树
    }
    if (indexh == n)
    { //判断右子树是为空，若根结点位于中序遍历序列最后面，说明根结点后面没有数字了，自然右结点为空
        p->rchild = NULL;
    }
    else
    {
        p->rchild = CreateTree(pre, in, s + leftlength + 1, e, indexh + 1, n); //递归构建右子树
    }
    return p;
}

void PostOrderTraverse(BiTree T)
{
    if (T == NULL)
        return;
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    putchar(T->data);
}

int main()
{
    while (scanf("%s %s", pre, in) == 2)
    {
        int prelen = strlen(pre);
        int inlen = strlen(in);
        BiTree T = new BiNode;
        T = CreateTree(pre, in, 0, prelen - 1, 0, inlen - 1);
        PostOrderTraverse(T);
        putchar('\n');
    }
    return 0;
}