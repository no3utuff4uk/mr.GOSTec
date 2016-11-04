#include <fstream>
#include <stdint.h>
#include "magma.h"


int magmaEncryptECB(uint32_t* key, std::ifstream& source, std::ofstream& destination)
{
    source.seekg(0, std::ios::end);
    unsigned long size = source.tellg();
    source.seekg(0, std::ios::beg);
    destination.write((char*) &size, sizeof(unsigned long));

    uint64_t intBuffer;
    unsigned long count = size%8 == 0 ? size/8: size/8+1;
    for(int i = 0; i< count; i++)
    {
        source.read((char*) &intBuffer ,8);
        intBuffer = magmaEncryptBlock(intBuffer, key);
        destination.write((char*) &intBuffer, 8);
    }

    return 0;
}

int magmaDecryptECB(uint32_t* key, std::ifstream& source, std::ofstream& destination)
{
    uint64_t intBuffer;

    unsigned long size;
    source.read((char*) &size, sizeof(unsigned long));

    for(int i = 0; i< size/8; i++)
    {
        source.read((char*) &intBuffer, 8);
        intBuffer = magmaDecryptBlock(intBuffer, key);
        destination.write((char*) &intBuffer, 8);

    }
    if(size%8 != 0)
    {
        source.read((char*) &intBuffer, 8);
        intBuffer = magmaDecryptBlock(intBuffer, key);
        destination.write((char*) &intBuffer, size%8);
    }

    return 0;
}
