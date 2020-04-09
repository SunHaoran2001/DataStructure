#include <iostream>
#include <cstdio>
#include <climits>
using namespace std;

typedef int Elemtype;
typedef struct Heap
{
    Elemtype *Elem;
    int Size;
    int Capacity;
} * MinHeap;

constexpr int MinData = INT_MIN;

MinHeap Create(int MaxSize)
{
    MinHeap H = new Heap;
    H->Elem = new Elemtype[MaxSize + 1];
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Elem[0] = MinData;
    return H;
}

int isFull(MinHeap H)
{
    if (H->Size == H->Capacity)
        return 1;
    return 0;
}

int isEmpty(MinHeap H)
{
    return !(H->Size);
}

void Insert(MinHeap H, Elemtype item)
{
    int i;
    if (isFull(H))
    {
        cout << "Heap is full!" << endl;
        return;
    }
    i = ++H->Size;
    for (; H->Elem[i / 2] > item; i /= 2)
    {
        H->Elem[i] = H->Elem[i / 2];
    }
    H->Elem[i] = item;
}

Elemtype DeleteMin(MinHeap H)
{
    int Parent, Child;
    Elemtype MinItem, temp;
    if (isEmpty(H))
    {
        cout << "Heap is empty" << endl;
        return 0;
    }
    MinItem = H->Elem[1];
    temp = H->Elem[H->Size--];
    for (Parent = 1; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2;
        if ((Child != H->Size) && (H->Elem[Child] > H->Elem[Child + 1]))
            Child++; // Chlid指向左右子结点的较大者
        if (temp <= H->Elem[Child])
            break;
        else // 移动temp元素到下一层
            H->Elem[Parent] = H->Elem[Child];
    }
    H->Elem[Parent] = temp;
    return MinItem;
}