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
const int MAXVEX = 10; /* 最大顶点数,应由用户定义 */

typedef int Status;      /* Status是函数的类型,其值是函数结果状态代码,如OK等 */
typedef char VertexType; /* 顶点类型应由用户定义 */
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
int main()
{
    GraphAdjList G;
    CreateALGraph(&G);
    return 0;
}