#include <iostream>

using namespace std;

typedef struct Node
{
    int coefficient;
    int power;
    struct Node *next;
} Node, *Linklist;

Linklist Create(Linklist L, int n)
{
    L->next = NULL;
    Linklist tail = L, s;
    for (int i = 0; i < n; i++)
    {
        s = new Node;
        //cout << "Enter coefficient:";
        cin >> s->coefficient;
        //cout << "Enter power:";
        cin >> s->power;
        tail->next = s;
        tail = s;
    }
    tail->next = NULL;
    return L->next; //没头节点
}

Linklist Solve(Linklist node1, Linklist node2)
{
    Linklist s, node = new Node;
    Linklist node3 = node;
    int temp;
    while (node1 && node2)
    {
        if (node1->power == node2->power)
        {
            s = new Node;
            temp = node1->coefficient + node2->coefficient;
            s->coefficient = temp;
            s->power = node1->power;
            node->next = s;
            node1 = node1->next;
            node2 = node2->next;
        }
        else if (node1->power < node2->power)
        {
            node->next = node1;
            node1 = node1->next;
        }
        else if (node1->power > node2->power)
        {
            node->next = node2;
            node2 = node2->next;
        }
        node = node->next;
    }
    node->next = NULL;
    if (node1)
    {
        node->next = node1;
    }
    if (node2)
    {
        node->next = node2;
    }
    return node3->next; //没头节点
}

void show(Linklist node)
{
    while (node->next != NULL)
    {
        cout << node->coefficient << "x^" << node->power << " + ";
        node = node->next;
    }
    cout << node->coefficient << "x^" << node->power << endl;
}

/*记得销毁操作*/
void Delete(Linklist node)
{
    if (node == NULL)
        return;
    Linklist p;
    while (node != NULL)
    {
        p = node->next;
        delete node;
        node = p;
    }
}

int main()
{
    Linklist node = new Node;
    Linklist node1 = new Node;
    Linklist node2 = new Node;
    node1 = Create(node1, 2);
    node2 = Create(node2, 2);
    node = Solve(node1, node2);
    show(node);
    Delete(node); //共享结点,直接删除node即可
    system("pause");
    return 0;
}