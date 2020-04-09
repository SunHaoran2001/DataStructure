#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>

using namespace std;
/*  Test
    4 5
    a b c d
    0 1
    0 2
    0 3
    1 2
    2 3
*/

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 9 /* 存储空间初始分配量 */
#define MAXEDGE 15
#define INFINITY 65535

const int MAXVEX = 10;   /* 最大顶点数,应由用户定义 */
typedef int Status;      /* Status是函数的类型,其值是函数结果状态代码,如OK等 */
typedef char VertexType; /* 顶点类型应由用户定义 */
typedef int Boolean;     /* Boolean是布尔类型,其值是TRUE或FALSE */
typedef int EdgeType;    /* 边上的权值类型应由用户定义 */

typedef struct EdgeNode /* 边表结点  */
{
    int adjvex;            /* 邻接点域,存储该顶点对应的下标 */
    EdgeType weight;       /* 用于存储权值,对于非网图可以不需要 */
    struct EdgeNode *next; /* 链域,指向下一个邻接点 */
};

typedef struct VertexNode
{
    VertexType data;     /* 顶点域,存储顶点信息 */
    EdgeNode *firstedge; /* 边表头指针 */
} VertexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int numVertexes, numEdges; /* 图中当前顶点数和边数 */
} GraphAdjList;

/* 循环队列的顺序存储结构 */
typedef struct
{
    int data[MAXSIZE];
    int front; /* 头指针 */
    int rear;  /* 尾指针,若队列不空,指向队列尾元素的下一个位置 */
} Queue;

/* 初始化一个空队列Q */
Status InitQueue(Queue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
Status QueueEmpty(Queue Q)
{
    if (Q.front == Q.rear) /* 队列空的标志 */
        return TRUE;
    else
        return FALSE;
}

/* 若队列未满,则插入元素e为Q新的队尾元素 */
Status EnQueue(Queue *Q, int e)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front) /* 队列满的判断 */
        return ERROR;
    Q->data[Q->rear] = e;              /* 将元素e赋值给队尾 */
    Q->rear = (Q->rear + 1) % MAXSIZE; /* rear指针向后移一位置, */
                                       /* 若到最后则转到数组头部 */
    return OK;
}

/* 用到的队列结构与函数********************************** */
/* 若队列不空,则删除Q中队头元素,用e返回其值 */
Status DeQueue(Queue *Q, int *e)
{
    if (Q->front == Q->rear) /* 队列空的判断 */
        return ERROR;
    *e = Q->data[Q->front];              /* 将队头元素赋值给e */
    Q->front = (Q->front + 1) % MAXSIZE; /* front指针向后移一位置, */
                                         /* 若到最后则转到数组头部 */
    return OK;
}
/* ****************************************************** */

void CreateALGraph(GraphAdjList *G)
{
    int i, j, k;
    EdgeNode *e;
    printf("Input the number of the vertexes and the number of the Edges.\n");
    scanf("%d%d", &G->numVertexes, &G->numEdges); /* 输入顶点数和边数 */
    getchar();                                    //吃掉回车
    for (i = 0; i < G->numVertexes; i++)          /* 读入顶点信息,建立顶点表 */
    {
        scanf("%c", &G->adjList[i].data); /* 输入顶点信息 */
        getchar();
        cout << i << endl;
        G->adjList[i].firstedge = NULL; /* 将边表置为空表 */
    }
    for (k = 0; k < G->numEdges; k++) /* 建立边表 */
    {
        printf("Input the edges of (vi,vj) Vertex sequence number.\n");
        scanf("%d %d", &i, &j);            /* 输入边(vi,vj)上的顶点序号 */
        e = new EdgeNode;                  /* 向内存申请空间,生成边表结点 */
        e->adjvex = j;                     /* 邻接序号为j */
        e->next = G->adjList[i].firstedge; /* 将e的指针指向当前顶点上指向的结点 */
        G->adjList[i].firstedge = e;       /* 将当前顶点的指针指向e */

        e = new EdgeNode;                  /* 向内存申请空间,生成边表结点 */
        e->adjvex = i;                     /* 邻接序号为i */
        e->next = G->adjList[j].firstedge; /* 将e的指针指向当前顶点上指向的结点 */
        G->adjList[j].firstedge = e;       /* 将当前顶点的指针指向e */
    }
}

Boolean visited[MAXSIZE]; /* 访问标志的数组 */

/* 邻接表的深度优先递归算法 */
void DFS(GraphAdjList *GL, int i)
{
    EdgeNode *p;
    visited[i] = TRUE;
    printf("%c ", GL->adjList[i].data);
    p = GL->adjList[i].firstedge;
    while (p)
    {
        if (!visited[p->adjvex])
            DFS(GL, p->adjvex);
        p = p->next;
    }
}

/* 邻接表的深度遍历操作 */
void DFSTraverse(GraphAdjList *GL)
{
    int i;
    for (i = 0; i < GL->numVertexes; i++)
        visited[i] = FALSE;
    for (i = 0; i < GL->numVertexes; i++)
        if (!visited[i])
            DFS(GL, i);
}

/* 邻接表的广度遍历算法 */
void BFSTraverse(GraphAdjList *GL)
{
    int i;
    EdgeNode *p;
    Queue Q;
    for (i = 0; i < GL->numVertexes; i++)
        visited[i] = FALSE;
    InitQueue(&Q);
    for (i = 0; i < GL->numVertexes; i++)
    {
        if (!visited[i])
        {
            visited[i] = TRUE;
            printf("%c ", GL->adjList[i].data); /* 打印顶点,也可以其它操作 */
            EnQueue(&Q, i);
            while (!QueueEmpty(Q))
            {
                DeQueue(&Q, &i);
                p = GL->adjList[i].firstedge; /* 找到当前顶点的边表链表头指针 */
                while (p)
                {
                    if (!visited[p->adjvex]) /* 若此顶点未被访问 */
                    {
                        visited[p->adjvex] = TRUE;
                        printf("%c ", GL->adjList[p->adjvex].data);
                        EnQueue(&Q, p->adjvex); /* 将此顶点入队列 */
                    }
                    p = p->next; /* 指针指向下一个邻接点 */
                }
            }
        }
    }
}

int main()
{
    GraphAdjList G;
    CreateALGraph(&G);
    DFSTraverse(&G);
    cout << endl;
    BFSTraverse(&G);
    return 0;
}