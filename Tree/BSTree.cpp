#include <iostream>

using namespace std;

typedef int Elem;
typedef struct BiNode
{
    Elem data;
    struct BiNode *lchild, *rchild;
} BiNode, *BiTree;

void InitTree(BiTree B)
{
    B->lchild = NULL;
    B->rchild = NULL;
}

BiTree Find(BiTree B, Elem e)
{
    if (!B)
        return NULL;
    if (e > B->data)
        return Find(B->rchild, e);
    else if (e < B->data)
        return Find(B->lchild, e);
    return B;
}

BiTree IterFind(BiTree B, Elem e)
{
    while (B)
    {
        if (e > B->data)
            B = B->rchild;
        else if (e < B->data)
            B = B->lchild;
        else
            return B;
    }
    return NULL;
}

BiTree FindMin(BiTree B)
{
    if (!B)
        return NULL;
    else if (!B->lchild)
        return B;
    else
        return FindMin(B->lchild);
}

BiTree IterFinMax(BiTree B)
{
    if (B)
        while (B->rchild)
            B = B->rchild;
    return B;
}

BiTree Insert(BiTree B, Elem e)
{
    if (B == NULL)
    {
        B = new BiNode;
        B->data = e;
        B->lchild = B->rchild = NULL;
    }
    else
    {
        if (e > B->data)
            B->lchild = Insert(B->lchild, e);
        else if (e < B->data)
            B->rchild = Insert(B->rchild, e);
        //else e 存在不需要其他操作
    }
    return B;
}
BiTree Delete(BiTree B, Elem e)
{
    BiTree tmp;
    if (B == NULL)
        cout << "ERROR" << endl;
    else if (e < B->data)
        B->lchild = Delete(B->lchild, e);
    else if (e > B->data)
        B->rchild = Delete(B->rchild, e);
    else
    {
        if (B->lchild && B->rchild) //被删除的结点有左右两个子节点
        {
            tmp = FindMin(B->rchild); //或者找右子树最小的替换，然后删除右子树最小的
            B->data = tmp->data;
            B->rchild = Delete(B->rchild, B->data);
        }
        else //删除结点有一个或者无子节点
        {
            tmp = B;
            if (!B->lchild)
                B = B->lchild;
            else if (!B->rchild)
                B = B->rchild;
            delete tmp;
        }
    }
    return B;
}

int main()
{

    system("pause");
    return 0;
}