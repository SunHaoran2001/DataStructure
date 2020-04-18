#ifndef _HUFF_TREE_H
#define _HUFF_TREE_H

#include <iostream>
#include <queue>
#include <map>
#include <string>

namespace huffman
{

struct Node
{
    uchar c;  //出现的字符
    int freq; //出现的频率
    Node *left;
    Node *right;
    Node(uchar _c, int f, Node *l = nullptr, Node *r = nullptr) //默认只有节点的二叉树
        : c(_c), freq(f), left(l), right(r)
    {
    }
    bool operator<(const Node &node) const
    { //重载，优先队列的底层数据结构std::heap是最大堆
        return freq > node.freq;
    }
};

class huffTree
{
public:
    huffTree(const std::map<uchar, int> &afMap)
    {
        for (auto i : afMap) //aotu自动遍历
        {
            Node n(i.first, i.second); //只有节点的树
            q.push(n);                 //压如最小堆
        }                              //构造森林
        makehuffTree();                //合并树。最后合并为哈夫曼树
    }
    void makehuffTree()
    {
        while (q.size() != 1) //最后只剩一个哈夫曼树
        {
            Node *left = new Node(q.top());
            q.pop();
            Node *right = new Node(q.top());
            q.pop();
            Node node('R', left->freq + right->freq, left, right);
            q.push(node);
        }
    }
    ~huffTree() //删除哈夫曼树
    {
        Node node = q.top();
        _deleteTree(node.left);
        _deleteTree(node.right);
    }

    void huffmanCode(std::map<uchar, std::string> &codeMap)
    {
        Node node = q.top();
        std::string prefix;
        _huffmanCode(&node, prefix, codeMap);
    }

    Node getHuffTree() //获取哈夫曼树
    {
        return q.top();
    }
    static bool _isLeaf(Node *n) //判断是不是叶子结点
    {
        return n->left == nullptr && n->right == nullptr;
    }

private:
    void _deleteTree(Node *n) //递归删除树
    {
        if (!n)
            return;
        _deleteTree(n->left);
        _deleteTree(n->right);
        delete n;
    }
    //编写哈夫曼编码，出现次数越多的字符编码越小
    void _huffmanCode(Node *root, std::string &prefix,
                      std::map<uchar, std::string> &codeMap)
    {
        std::string tmp = prefix;
        if (root->left != nullptr)
        {
            prefix += '0';
            if (_isLeaf(root->left))
            {
                codeMap[root->left->c] = prefix;
            }
            else
            {
                _huffmanCode(root->left, prefix, codeMap);
            }
        }
        if (root->right != nullptr)
        {
            prefix = tmp;
            prefix += '1';
            if (_isLeaf(root->right))
            {
                codeMap[root->right->c] = prefix;
            }
            else
            {
                _huffmanCode(root->right, prefix, codeMap);
            }
        }
    }

private:
    std::priority_queue<Node> q;
};
} // namespace huffman

#endif