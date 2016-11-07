#include <fstream>
#include <stdint.h>
#include "magma.h"


uint32_t magmaGenerateMAC(uint32_t* key, std::ifstream& source)
{
    source.seekg(0, std::ios::end);
    unsigned long size = source.tellg();
    source.seekg(0, std::ios::beg);

    uint64_t K1=0, K2=0, R;
    R = magmaEncryptBlock(0, key);
    if(R >> 63 != 0)
    {
        K1 = (R << 1) + 0x1b;
        if(K1 >> 63 != 0)
            K2 = (K1 << 1) + 0x1b;
        else
            K2 = (K1 << 1);
    }else
    {
        K1 = (R << 1);
        if(K1 & 0xf000000000000000 != 0)
            K2 = (K1 << 1) + 0x1b;
        else
            K2 = (K1 << 1);
    }


    uint64_t intBuffer, tmpMAC = 0;

    //unsigned long count = size%8 == 0 ? size/8: size/8+1;
    for(int i = 0; i< size/8 - 1; i++)
    {
        source.read((char*) &intBuffer, sizeof(uint64_t));
        tmpMAC ^= intBuffer;
        tmpMAC = magmaEncryptBlock(tmpMAC, key);
    }

    source.read((char*) &intBuffer, sizeof(uint64_t));
    if(size%8 == 0)
        intBuffer ^= K1;
    else
        intBuffer ^= K2;

    tmpMAC ^= intBuffer;
    tmpMAC = magmaEncryptBlock(tmpMAC, key);

    return tmpMAC >> 32;
}
