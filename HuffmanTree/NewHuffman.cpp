#include <iostream>
#include <cstdio>

typedef struct TreeNode *HuffmanTree;
typedef struct TreeNode
{
    int Weight; //权值
    HuffmanTree Left;
    HuffmanTree Right;
} HuffmanNode;

#define MinData -1 //随着堆元素的具体值而改变

typedef struct HeapStruct *MinHeap;
struct HeapStruct
{
    HuffmanTree *data; //存储堆元素的数组  存储时从下标1开始
    int Size;          //堆的当前元素的个数
    int Capacity;      //堆的最大容量
};

HuffmanTree NewHuffmanNode();
MinHeap CreateMinHeap(int MaxSize);
bool Insert(MinHeap H, HuffmanTree item);
HuffmanTree DeleteMin(MinHeap H);
MinHeap BuildMinHeap(MinHeap H);
HuffmanTree Huffman(MinHeap H);
void PreOrderTraversal(HuffmanTree BST);

int main()
{
    int i, N;
    MinHeap h;
    HuffmanTree T, BT = NULL;

    printf("请输入叶子结点的个数:\n");
    scanf("%d", &N);
    h = CreateMinHeap(2 * N); //创建最小堆
    printf("请输入%d个叶子结点对应的权值:\n", N);
    for (i = 1; i <= N; i++)
    { /*最小堆元素赋值*/
        T = NewHuffmanNode();
        scanf("%d", &(T->Weight));
        h->data[++(h->Size)] = T;
    }

    BT = Huffman(h); //构造哈夫曼树
    printf("先序遍历此哈夫曼树的权值:\n");
    PreOrderTraversal(BT); //先序遍历此哈夫曼树
    system("pause");
    return 0;
}

/*哈夫曼树构造算法*/
HuffmanTree Huffman(MinHeap H)
{ /*假设H->Size个权值已经存在H->data[]->Weight里*/
    int i, num;
    HuffmanTree T;

    BuildMinHeap(H); //将H->data[]按权值调整为最小堆
    /*此处必须将H->Size的值交给num,因为后面做DeleteMin()和 Insert()函数会改变H->Size的值*/
    num = H->Size;
    for (i = 1; i < num; i++)
    {                                                   //做 H->Size-1次合并   //此处教科书有问题！原书直接为H->Size
        T = NewHuffmanNode();                           //建立一个新的根结点
        T->Left = DeleteMin(H);                         //从最小堆中删除一个节点，作为新T的左子结点
        T->Right = DeleteMin(H);                        //从最小堆中删除一个节点，作为新T的右子结点
        T->Weight = T->Left->Weight + T->Right->Weight; //计算新权值
        //printf("%3d 0x%x 0x%x\n",T->Weight,T->Left,T->Right);
        Insert(H, T); //将新T插入到最小堆
    }
    T = DeleteMin(H);

    return T;
}

/*****先序遍历*****/
void PreOrderTraversal(HuffmanTree BST)
{
    if (BST)
    {
        printf("%d ", BST->Weight);    //先访问根节点
        PreOrderTraversal(BST->Left);  //再访问左子树
        PreOrderTraversal(BST->Right); //最后访问右子树
    }
}

HuffmanTree NewHuffmanNode()
{
    HuffmanTree BST = (HuffmanTree)malloc(sizeof(HuffmanNode));
    BST->Weight = 0;
    BST->Left = BST->Right = NULL;

    return BST;
}

MinHeap CreateMinHeap(int MaxSize)
{ /*创建容量为MaxSize的最小堆*/
    MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
    H->data = (HuffmanTree *)malloc((MaxSize + 1) * sizeof(HuffmanTree));
    H->Size = 0;
    H->Capacity = MaxSize;
    HuffmanTree T = NewHuffmanNode();
    T->Weight = MinData; /*定义哨兵-为小于堆中所有可能元素权值的值，便于以后更快操作*/
    H->data[0] = T;

    return H;
}

bool IsFull(MinHeap H)
{
    return (H->Size == H->Capacity);
}

bool IsEmpty(MinHeap H)
{
    return (H->Size == 0);
}

/*插入算法-将新增结点插入到从其父结点到根结点的有序序列中*/
bool Insert(MinHeap H, HuffmanTree item)
{ /*将元素item插入到最小堆H中，其中H->data[0]已被定义为哨兵*/
    int i;
    if (IsFull(H))
    {
        printf("Heap is full!\n");
        return false;
    }
    i = ++H->Size;                                        //i指向插入后堆中的最后一个元素的位置
    for (; H->data[i / 2]->Weight > item->Weight; i /= 2) //无哨兵，则增加判决条件 i>1
        H->data[i] = H->data[i / 2];                      //向下过滤结点
    H->data[i] = item;                                    //将item插入

    return true;
}

HuffmanTree DeleteMin(MinHeap H)
{ /*从最小堆H中取出权值为最小的元素，并删除一个结点*/
    int parent, child;
    HuffmanTree MinItem, temp = NULL;
    if (IsEmpty(H))
    {
        printf("最小堆为空\n");
        return NULL;
    }
    MinItem = H->data[1]; //取出根结点-最小的元素-记录下来
    /*用最小堆中的最后一个元素从根结点开始向上过滤下层结点*/
    temp = H->data[H->Size--]; //最小堆中最后一个元素，暂时将其视为放在了根结点
    for (parent = 1; parent * 2 <= H->Size; parent = child)
    {
        child = parent * 2;
        if ((child != H->Size) && (H->data[child]->Weight > H->data[child + 1]->Weight))
        {            /*有右儿子，并且左儿子权值大于右儿子*/
            child++; //child指向左右儿子中较小者
        }
        if (temp->Weight > H->data[child]->Weight)
        {
            H->data[parent] = H->data[child]; //向上过滤结点-temp存放位置下移到child位置
        }
        else
        {
            break; //找到了合适的位置
        }
    }
    H->data[parent] = temp; //temp存放到此处

    return MinItem;
}

MinHeap BuildMinHeap(MinHeap H)
{ /*这里假设所有的H->Size个元素已经存在H->data[]中*/
    /*本函数将H->data[]中的元素调整，使其满足堆的有序性*/
    int i, parent, child;
    HuffmanTree temp;
    for (i = H->Size / 2; i > 0; i--)
    { //从最后一个父结点开始，直到根结点
        temp = H->data[i];
        for (parent = i; parent * 2 <= H->Size; parent = child)
        {
            /*向下过滤*/
            child = parent * 2;
            if ((child != H->Size) && (H->data[child]->Weight > H->data[child + 1]->Weight))
            {            /*有右儿子，并且左儿子权值大于右儿子*/
                child++; //child指向左右儿子中较小者
            }
            if (temp->Weight > H->data[child]->Weight)
            {
                H->data[parent] = H->data[child]; //向上过滤结点-temp存放位置下移到child位置
            }
            else
            {
                break; //找到了合适的位置
            }
        } /*结束内部for循环对以H->data[i]为根的子树的调整*/

        H->data[parent] = temp; //temp（原H->data[i]）存放到此处
    }
    return H;
}
