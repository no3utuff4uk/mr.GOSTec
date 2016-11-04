#include <fstream>
#include <stdint.h>
#include "magma.h"


int magmaEncryptCBC(uint32_t* key, uint64_t initL, uint64_t initR, std::ifstream& source, std::ofstream& destination)
{
    source.seekg(0, std::ios::end);
    unsigned long size = source.tellg();
    source.seekg(0, std::ios::beg);
    destination.write((char*) &size, sizeof(unsigned long));
    destination.write((char*) &initL, sizeof(uint64_t));
    destination.write((char*) &initR, sizeof(uint64_t));

    uint64_t intBuffer;
    unsigned long count = size%8 == 0 ? size/8: size/8+1;
    for(int i = 0; i< count; i++)
    {
        source.read((char*) &intBuffer ,8);
        intBuffer ^= initL;
        intBuffer = magmaEncryptBlock(intBuffer, key);
        initL = initR;
        initR = intBuffer;
        destination.write((char*) &intBuffer, sizeof(uint64_t));
    }

    return 0;
}

int magmaDecryptCBC(uint32_t* key, std::ifstream& source, std::ofstream& destination)
{
    unsigned long size;
    source.read((char*) &size, sizeof(unsigned long));

    uint64_t initL, initR;
    source.read((char*) &initL, sizeof(uint64_t));
    source.read((char*) &initR, sizeof(uint64_t));

    //init = 0xfedcba9876543210;

    uint64_t buffer;
    uint64_t tmp;

    for(int i = 0; i< size/8; i++)
    {
        source.read((char*) &buffer, sizeof(uint64_t));
        tmp = buffer;
        buffer = magmaDecryptBlock(buffer, key);
        buffer ^= initL;
        destination.write((char*) &buffer, sizeof(uint64_t));
        initL = initR;
        initR = tmp;
    }
    if(size%8 != 0)
    {
        source.read((char*) &buffer, sizeof(uint64_t));
        buffer = magmaDecryptBlock(buffer, key);
        buffer ^= initL;
        destination.write((char*) &buffer, size%8);
    }
}
