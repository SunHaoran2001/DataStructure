#include <iostream>
#include "MinHeapOfInt.h"
using namespace std;

typedef struct
{
    int weight;
    HuffmanTree lchild, rchild;
} HTNode, *HuffmanTree;

MinHeap BuildMinHeap(MinHeap H)
{
    int size = H->Size;
    for (int i = 1; i <= size; i++)
    {
        Insert(H, H->Elem[i]);
    }
    return H;
}

HuffmanTree Huffman(MinHeap H)
{
    int i;
    HuffmanTree T;
    BuildMinHeap(H);
    for (i = 1; i < H->Size; i++)
    {
        T = new HTNode;
        T->lchild = DeleteMin(H);
        T->rchild = DeleteMin(H);
        T->weight = T->lchild->weight + T->rchild->weight;
        Insert(H, T);
    }
    T = DeleteMin(H);
    return T;
}
int main()
{

    system("pause");
    return 0;
}