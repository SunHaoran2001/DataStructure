#include <iostream>

using namespace std;

typedef struct Node
{
    int data;
    struct Node *next;
} * Linklist;

typedef struct DolNode
{
    int data;
    struct DolNode *next, *prior;
} * DolLinklist;

Linklist CreateLinklist_Head(Linklist L, int n)
{
    Linklist p = L, s;
    p->next = NULL;

    for (int i = 0; i < n; i++)
    {
        s = new Node;
        cin >> s->data;
        s->next = p->next;
        p->next = s;
    }
    return L->next;
}

Linklist CreateLinklist_Tail(Linklist L, int n)
{
    Linklist tail = L, s;
    L->next = NULL;

    for (int i = 0; i < n; i++)
    {
        s = new Node;
        cin >> s->data;
        tail->next = s;
        tail = s;
    }
    return L->next;
}

void Delete(Linklist L, int pos, int *e)
{
    Linklist p = L, q;
    int j = 1;
    while (j < pos - 1 && p)
    {
        p = p->next;
        j++;
    }
    q = p->next;
    p->next = q->next;
    *e = q->data;
    delete q;
}

DolLinklist CreateDolLinklist_Head(DolLinklist L, int n)
{
    DolLinklist head = L, s;
    head->next = NULL;
    head->prior = NULL;
    /*
    for (int i = 0; i < n; i++)
    {
        s = new DolNode;
        cin >> s->data;
        if (head->next)
        {
            s->next = head->next;
            s->prior = head;
            head->next->prior = s;
            head->next = s;
        }
        else
        {
            s->next = head->next;
            s->prior = head;
            head->next = s;
        }
    }*/

    for (int i = 0; i < n; i++)
    {
        s = new DolNode;
        cin >> s->data;
        s->next = head->next;
        s->prior = head;
        if (head->next)
            head->next->prior = s;
        head->next = s;
    }
    return L->next;
}

void Delete_Dol(DolLinklist L, int pos, int *e)
{
    DolLinklist p = L, q;
    int j = 1;
    while (j < pos - 1 && p)
    {
        p = p->next;
        j++;
    }
    q = p->next;
    p->next = q->next;
    q->next->prior = p;
    *e = q->data;
    delete q;
}

void ShowLinklist(Linklist L)
{
    Linklist p = L;
    while (p->next)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << p->data;
}

void ShowLinklist(DolLinklist L)
{
    DolLinklist p = L;
    while (p->next)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << p->data;
}

void ShowLinklist2(DolLinklist L)
{
    DolLinklist p = L;
    while (p->next != L)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << p->data;
}

int main()
{
    Linklist L = new Node;
    DolLinklist L2 = new DolNode;
    L2 = CreateDolLinklist_Head(L2, 5);
    int e;
    Delete_Dol(L2, 2, &e);
    cout << e << endl;
    ShowLinklist2(L2);

    system("pause");
    return 0;
}