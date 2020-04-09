#include <iostream>
#include <cstdio>
#include <climits>
using namespace std;

typedef struct HuffmanTree *HTREE;
typedef struct HEAP *MINHEAP;
typedef HTREE ElementType;

struct HuffmanTree
{
    int Wight;
    HTREE Lift;
    HTREE Right;
};

struct HEAP
{
    ElementType *Data;
    int Size;
    int MaxSize;
};

MINHEAP CreatMinHeap(int);
MINHEAP AdjustHeap(MINHEAP);
void Insert(MINHEAP H, HTREE);
ElementType DeleteHeap(MINHEAP);
HTREE CreatHT(int);
void FreeH(MINHEAP);
MINHEAP AdjustHeap(MINHEAP H)
{
    int i, parent, child;
    ElementType TEMP;
    for (i = H->Size / 2; i >= 1; i--)
    {
        for (parent = i; 2 * parent <= H->Size; parent = child)
        {
            child = 2 * parent;
            if (child != H->Size && (H->Data[child]->Wight > H->Data[child + 1]->Wight))
            {
                child++;
            }
            if (H->Data[parent]->Wight > H->Data[child]->Wight)
            {
                TEMP = H->Data[parent];
                H->Data[parent] = H->Data[child];
                H->Data[child] = TEMP;
            }
        }
    }
    return H;
}

MINHEAP CreatMinHeap(int maxsize)
{
    MINHEAP H = (MINHEAP)malloc(sizeof(struct HEAP));
    H->Size = 0;
    H->MaxSize = maxsize;
    H->Data = (ElementType *)malloc((H->MaxSize + 1) * sizeof(ElementType));
    H->Data[0] = NULL;
    for (int i = 1; i <= H->MaxSize; i++)
    {
        H->Data[i] = (ElementType)malloc(sizeof(struct HuffmanTree));
        H->Data[i]->Lift = NULL;
        H->Data[i]->Right = NULL;
    }
    printf("Input a series of wight:\n");
    for (int i = 1; i <= H->MaxSize; i++)
    {
        scanf("%d", &H->Data[i]->Wight);
        H->Size++;
    }
    return AdjustHeap(H);
}
ElementType DeleteHeap(MINHEAP H)
{
    ElementType TEMP_Data;
    if (H->Size == 0)
        exit(-1);
    TEMP_Data = H->Data[1];
    H->Data[1] = H->Data[H->Size--];
    H = AdjustHeap(H);
    return TEMP_Data;
}
void Insert(MINHEAP H, HTREE T)
{
    if (H->Size == H->MaxSize)
        exit(-1);
    H->Size++;
    H->Data[H->Size] = T;
    H = AdjustHeap(H);
}
HTREE CreatHT(int maxsize)
{
    HTREE T;
    int i, n;
    MINHEAP H = CreatMinHeap(maxsize);
    n = H->Size;
    for (i = 1; i < n; i++)
    {
        T = (HTREE)malloc(sizeof(struct HuffmanTree));
        T->Lift = DeleteHeap(H);
        T->Right = DeleteHeap(H);
        T->Wight = T->Lift->Wight + T->Right->Wight;
        Insert(H, T);
    }
    T = DeleteHeap(H);
    FreeH(H);
    return T;
}
