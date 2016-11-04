#include <fstream>
#include <stdint.h>
#include <iostream>
#include "magma.h"

int magmaEncryptCTR(uint32_t* key, uint64_t init, std::ifstream& source, std::ofstream& destination)
{
    source.seekg(0, std::ios::end);
    unsigned long size = source.tellg();
    source.seekg(0, std::ios::beg);
    destination.write((char*) &size, sizeof(unsigned long));
    destination.write((char*) &init, sizeof(uint64_t));

    uint64_t buffer;
    unsigned long count = size%8 == 0 ? size/8: size/8+1;

    for(size_t i = 0; i< count; i++)
    {
        //std::cout<<std::hex<<init<<std::endl;
        source.read((char*) &buffer, sizeof(uint64_t));
        //std::cout<<buffer<<std::endl;
        buffer ^= magmaEncryptBlock(init, key);
        //std::cout<<buffer<<std::endl;
        init++;
        destination.write((char*) &buffer, sizeof(uint64_t));
        //std::cout<<std::endl;
    }

    return 0;
}

int magmaDecryptCTR(uint32_t* key, std::ifstream& source, std::ofstream& destination)
{
    unsigned long size;
    source.read((char*) &size, sizeof(unsigned long));

    uint64_t init;
    source.read((char*) &init, sizeof(uint64_t));

    //init = 0xfedcba9876543210;

    uint64_t buffer;

    for(int i = 0; i< size/8; i++)
    {
        source.read((char*) &buffer, sizeof(uint64_t));
        buffer ^= magmaEncryptBlock(init, key);
        init++;
        destination.write((char*) &buffer, sizeof(uint64_t));
        //init = buffer;
    }
    if(size%8 != 0)
    {
        source.read((char*) &buffer, sizeof(uint64_t));
        buffer ^= magmaEncryptBlock(init, key);
        destination.write((char*) &buffer, size%8);
    }

}
