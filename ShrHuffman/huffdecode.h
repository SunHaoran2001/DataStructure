#ifndef _HUFF_DECODE_H
#define _HUFF_DECODE_H

#include <map>
#include <fstream>

#include "huffman.h"
#include "huffTree.h"

namespace huffman
{

class huffDecode
{
public:
    huffDecode() : _fileHead(nullptr), _htree(nullptr)
    {
        _fileHead = new fileHead();
    }
    ~huffDecode()
    {
        if (!_fileHead)
            delete _fileHead;
        if (!_htree)
            delete _htree;
    }

private:
    static bool _isLeaf(Node *n) //判断是不是叶子节点
    {
        return n->left == nullptr && n->right == nullptr;
    }
    long _getFileSize(const char *strFileName) //获取文件大小
    {
        std::ifstream input(strFileName);
        if (!input.is_open())
            return 0;

        input.seekg(0, std::ios_base::end);
        std::streampos sp = input.tellg();
        input.close();
        return sp;
    }
    bool _getAlphaFreq(const char *filename)
    {
        std::ifstream is(filename, std::ios::binary);
        if (!is)
        {
            printf("read file failed! filename: %s", filename);
            return false;
        }
        //读取文件识别的文件
        is.read((char *)_fileHead, sizeof(fileHead));
        if (!(_fileHead->flag[0] == 'S' &&
              _fileHead->flag[1] == 'h' &&
              _fileHead->flag[2] == 'r'))
        {
            printf("not support this file format! filename: %s\n", filename);
            return false;
        }
        //根据字符种类按照alphaFreq大小读取
        for (int i = 0; i < static_cast<int>(_fileHead->alphaVariety); ++i)
        {
            alphaFreq af;
            is.read((char *)&af, sizeof(af));
            _afMap.insert(std::pair<char, int>(af.alpha, af.freq)); //写入操作的逆过程
        }
        is.close();
        return true;
    }
    bool _decode(const char *srcFilename,
                 const char *destFilename)
    {
        long fileSize = _getFileSize(srcFilename);

        std::ifstream is(srcFilename, std::ios::binary);
        if (!is)
        {
            printf("read file failed! filename: %s", srcFilename);
            return false;
        }
        //文件指针跳过头文件和写入的字符和其频率，读取哈夫曼编码,创建哈夫曼树还原源码
        is.seekg(sizeof(fileHead) + sizeof(alphaFreq) * _fileHead->alphaVariety);

        Node node = _htree->getHuffTree(); //获取哈夫曼的根节点
        Node *pNode = &node;

        std::ofstream io(destFilename, std::ios::binary);
        if (!io)
        {
            printf("create file failed! filename: %s", destFilename);
            return false;
        }

        uchar value;
        std::string code;
        int index = 0;
        long curLocation = is.tellg(); //获取当前文件指针的位置
        is.read((char *)&value, sizeof(uchar));
        while (true)
        {
            if (_isLeaf(pNode))
            {
                uchar alpha = _decodeMap[code];
                io.write((char *)&alpha, sizeof(uchar));
                if (curLocation >= fileSize && index >= _fileHead->lastValidBit) //读取完所有数据，结束
                {
                    break;
                }
                code.clear(); //清空数组
                pNode = &node;
            }

            if (GET_BYTE(value, index))
            {
                code += '1';
                pNode = pNode->right;
            }
            else
            {
                pNode = pNode->left;
                code += '0';
            }
            if (++index >= 8)
            {
                index = 0;
                is.read((char *)&value, sizeof(uchar));
                curLocation = is.tellg();
            }
        }

        is.close();
        io.close();
        return true;
    }

public:
    bool decode(const char *srcFilename, const char *destFilename)
    {
        if (!_getAlphaFreq(srcFilename))
            return false;
        long fileSize = _getFileSize(srcFilename);
        _htree = new huffTree(_afMap);
        _htree->huffmanCode(_codeMap);

        for (auto it : _codeMap)
        {
            _decodeMap.insert(std::pair<std::string, uchar>(it.second, it.first));
        }

        return _decode(srcFilename, destFilename);
    }

private:
    fileHead *_fileHead;
    huffTree *_htree;
    std::map<uchar, int> _afMap;
    std::map<uchar, std::string> _codeMap;
    std::map<std::string, uchar> _decodeMap;
};

} // namespace huffman

#endif
