#include <iostream>
using namespace std;

typedef int Elem;
const int MAXN = 20;
typedef struct
{
    Elem data[MAXN];
    int front;
    int rear;
} SqQueue;

void InitQueue(SqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
}

void Enqueue(SqQueue *Q, Elem e)
{
}

int main()
{
    system("pause");
    return 0;
}