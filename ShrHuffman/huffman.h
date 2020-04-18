#ifndef _HUFFMAN_H
#define _HUFFMAN_H

//得到index位的值，若index位为0，则GET_BYTE值为假，否则为真
#define GET_BYTE(vbyte, index) (((vbyte) & (1 << ((index) ^ 7))) != 0)
//index位置设置为1
#define SET_BYTE(vbyte, index) ((vbyte) |= (1 << ((index) ^ 7)))
//index位置设置为0
#define CLR_BYTE(vbyte, index) ((vbyte) &= (~(1 << ((index) ^ 7))))

using uchar = unsigned char;

struct fileHead
{
    char flag[3];       //压缩二进制文件头部标志 Shr
    uchar alphaVariety; //字符种类
    uchar lastValidBit; //最后一个字节的有效位数
    char unused[11];    //待用空间
};                      //这个结构体总共占用16个字节的空间

struct alphaFreq //af
{
    uchar alpha; //字符,考虑到文件中有汉字，所以定义成uchar
    int freq;    //字符出现的频度
    alphaFreq() {}
    alphaFreq(const std::pair<uchar, int> &x)
        : alpha(x.first), freq(x.second) {}
};

#endif