#include <iostream>

using namespace std;

typedef double Elemtype;
typedef struct Node
{
    int val;
    struct Node *next;
} Node, *Linklist;

Linklist CreateLinklist_Tail(Linklist L, int n)
{
    Linklist s, tail;
    L->next = NULL;
    tail = L;

    for (int i = 0; i < n; i++)
    {
        s = new Node;
        cin >> s->val;
        tail->next = s;
        tail = s;
    }
    L = L->next;
    tail->next = NULL;

    return L;
}

void printLinklist(Linklist L)
{
    Linklist p = L;
    while (p->next->next != NULL)
    {
        cout << p->next->val << " ";
        p = p->next;
    }
    cout << p->next->val;
}

void Insert(Linklist L, int pos, Elemtype e)
{
    Linklist p, s;
    int j = 1;
    p = L;
    while (j < pos)
    {
        p = p->next;
        j++;
    }
    s = new Node;
    s->val = e;
    s->next = p->next;
    p->next = s;
}

Elemtype Delete(Linklist L, int pos)
{
    Linklist p, q;
    Elemtype e;
    int j = 1;
    p = L;
    while (j < pos)
    {
        p = p->next;
        j++;
    }
    q = p->next;
    e = q->val;
    p->next = q->next;
    delete q;
    return e;
}

int main()
{
    Linklist L = new Node;
    CreateLinklist_Tail(L, 5);
    Insert(L, 5, 6);
    cout << Delete(L, 5) << endl;
    printLinklist(L);
    system("pause");
    return 0;
}