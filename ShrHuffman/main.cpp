#include "huffencode.h"
#include "huffdecode.h"

using namespace huffman;

void testHuffTree(const std::string &filename)
{
    std::string destFilename = "en" + filename;
    huffEncode he;
    he.encode(filename.data(), destFilename.data());
}

void testHuffDecode(const std::string &filename)
{
    std::string destFilename = "de" + filename;
    huffDecode hd;
    hd.decode(filename.data(), destFilename.data());
}

int main()
{
    int n;
    std::string filename;
    std::cout << "Encode Enter 1\nDecode Enter 2" << std::endl;
    std::cin >> n;
    if (n == 1)
    {
        std::cin >> filename;
        testHuffTree(filename);
    }
    else if (n == 2)
    {
        std::cin >> filename;
        testHuffDecode("en" + filename);
    }
    std::cout << "ok" << std::endl;
    system("pause");
    return 0;
}
