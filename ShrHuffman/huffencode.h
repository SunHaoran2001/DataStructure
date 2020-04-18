#ifndef _HUFF_ENCODE_H
#define _HUFF_ENCODE_H

#include <map>
#include <fstream>

#include "huffman.h"
#include "huffTree.h"

namespace huffman
{

class huffEncode
{
public:
    bool encode(const char *srcFilename, const char *destFilename) //编码
    {
        if (!_getAlphaFreq(srcFilename)) //如果没有找到文件返回false
            return false;
        huffTree htree(_afMap);                    //用字符和出现频率创建一个哈夫曼树（创建细节请见hufftree.h）
        htree.huffmanCode(_codeMap);               //通过哈夫曼树确定哈夫曼编码(编码细节请见hufftree.h)
        return _encode(srcFilename, destFilename); //将哈夫曼编码写入文件
    }

private:
    int _getLastValidBit() //获取最后的有效位数
    {
        int sum = 0;
        for (auto it : _codeMap)
        {
            sum += it.second.size() * _afMap.at(it.first);
            sum &= 0xFF; //如果不执行这一步，当数据长度超过int的表示范围，就会出错
            //0xFF化为二进制位1111 1111，这样做sum始终是最后一个字节,8位
        }
        //举例：若最后生成7位二进制，划分为一个字节，那么，这一个字节只有7位为有效位，其余都是垃圾位。
        //我们只需要取出这个字节的那7个有效位，所以sum和8取余即可
        //sum = sum % 8 <=> sum = sum & 0x7
        //返回最后一个字节的有效位数
        sum &= 0x7;
        return sum == 0 ? 8 : sum;
    }
    //获取文件的字符
    bool _getAlphaFreq(const char *filename)
    {
        uchar ch;
        std::ifstream input(filename, std::ios::binary);
        if (!input.is_open())
        {
            printf("read file failed! filename: %s", filename);
            return false;
        }
        //先读入一个字符，防止下面操作出错
        input.read((char *)&ch, sizeof(uchar));
        while (!input.eof())
        {
            _afMap[ch]++; //每个字符对应的频率加一
            //读取下一个字符
            input.read((char *)&ch, sizeof(uchar));
        }
        input.close();
        return true;
    }
    bool _encode(const char *srcFilename, const char *destFilename)
    {
        uchar ch;                                     //字符
        uchar value;                                  //写入用的临时数值
        int bitIndex = 0;                             //位数统计
        fileHead filehead = {'S', 'h', 'r'};          //识别文件的头
        filehead.alphaVariety = (uchar)_afMap.size(); //字符的种类
        filehead.lastValidBit = _getLastValidBit();   //最后一位有效数位

        std::ifstream input(srcFilename, std::ios::binary);
        if (!input.is_open())
        {
            printf("read file failed! filename: %s", srcFilename);
            return false;
        }
        std::ofstream output(destFilename, std::ios::binary);
        if (!output.is_open())
        {
            printf("read file failed! filename: %s", destFilename);
            return false;
        }

        //写入识别文件
        output.write((char *)&filehead, sizeof(fileHead));

        for (auto i : _afMap)
        {
            alphaFreq af(i);                              //使用alphaFreq构造函数构造af
            output.write((char *)&af, sizeof(alphaFreq)); //字符和频率写入
        }
        //先读取一个字符，防止下面操作出错
        input.read((char *)&ch, sizeof(uchar));
        while (!input.eof())
        {
            std::string code = _codeMap.at(ch); //code为每一个huffmancode的编码值
            for (auto c : code)                 //遍历每一位0或1
            {
                //设置value的每个字节的位数，通过value写入1个字节1个字节写入
                if ('0' == c)
                {
                    CLR_BYTE(value, bitIndex);
                }
                else
                {
                    SET_BYTE(value, bitIndex);
                }
                ++bitIndex;
                if (bitIndex >= 8)
                {
                    bitIndex = 0;
                    output.write((char *)&value, sizeof(uchar)); //一个字节一个写入
                }
                //这样写入最后一组数据前的编码（最后一组可能不够8位，会产生其他垃圾数据，对最后一组单独处理）
            }
            input.read((char *)&ch, sizeof(uchar));
        }
        //写入最后一组的编码
        if (bitIndex)
        {
            output.write((char *)&value, sizeof(uchar));
        }
        input.close();
        output.close();
        return true;
    }

private:
    std::map<uchar, int> _afMap;
    std::map<uchar, std::string> _codeMap;
};

} // namespace huffman

#endif