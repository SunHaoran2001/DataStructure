#include <iostream>

using namespace std;
#define GET_BYTE(vbyte, index) (((vbyte) & (1 << ((index) ^ 7))) != 0)
#define SET_BYTE(vbyte, index) ((vbyte) |= (1 << ((index) ^ 7)))
#define CLR_BYTE(vbyte, index) ((vbyte) &= (~(1 << ((index) ^ 7))))
typedef struct ALPHA_FREQ
{
    unsigned char alpha; //字符,考虑到文件中有汉字，所以定义成unsigned char
    int freq;            //字符出现的频度
} ALPHA_FREQ;

int main()
{
    system("pause");
    return 0;
}