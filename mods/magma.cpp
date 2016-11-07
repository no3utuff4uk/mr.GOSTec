#include <stdint.h>


void magmaRound(uint32_t roundKey, uint32_t* a1, uint32_t* a0)
{
    static int pi[8][16] =
    {
        12, 4, 6, 2, 10, 5, 11, 9, 14, 8, 13, 7, 0, 3, 15, 1, //pi0
        6, 8, 2, 3, 9, 10, 5, 12, 1, 14, 4, 7, 11, 13, 0, 15, //pi1
        11, 3, 5, 8, 2, 15, 10, 13, 14, 1, 7, 4, 12, 9, 6, 0, //pi2
        12, 8, 2, 1, 13, 4, 15, 6, 7, 0, 10, 5, 3, 14, 9, 11, //pi3
        7, 15, 5, 10, 8, 1, 6, 13, 0, 9, 3, 14, 11, 4, 2, 12, //pi4
        5, 13, 15, 6, 9, 2, 12, 10, 11, 7, 8, 1, 4, 3, 14, 0, //pi5
        8, 14, 2, 5, 6, 9, 1, 12, 15, 4, 11, 0, 13, 10, 3, 7, //pi6
        1, 7, 14, 13, 0, 5, 8, 3, 4, 15, 10, 6, 9, 12, 11, 2  //pi7
    };

    uint32_t tmp = 0;
    for(unsigned int i = 0; i < 8; i++)
    {
        tmp |= (pi[i][((*a0 + roundKey) & (0xf << 4*i)) >> 4*i] << 4*i);

    }
    tmp = (tmp << 11)|(tmp >> 21);

    *a1 ^= tmp;
}
//using namespace std;
uint64_t magmaEncryptBlock(uint64_t openBlock, uint32_t* key)
{
    uint32_t a1 = (openBlock >> 32) & 0xffffffff;
    uint32_t a0 = openBlock & 0xffffffff;

    magmaRound(key[0], &a1, &a0);
    magmaRound(key[1], &a0, &a1);
    magmaRound(key[2], &a1, &a0);
    magmaRound(key[3], &a0, &a1);
    magmaRound(key[4], &a1, &a0);
    magmaRound(key[5], &a0, &a1);
    magmaRound(key[6], &a1, &a0);
    magmaRound(key[7], &a0, &a1);

    magmaRound(key[0], &a1, &a0);
    magmaRound(key[1], &a0, &a1);
    magmaRound(key[2], &a1, &a0);
    magmaRound(key[3], &a0, &a1);
    magmaRound(key[4], &a1, &a0);
    magmaRound(key[5], &a0, &a1);
    magmaRound(key[6], &a1, &a0);
    magmaRound(key[7], &a0, &a1);

    magmaRound(key[0], &a1, &a0);
    magmaRound(key[1], &a0, &a1);
    magmaRound(key[2], &a1, &a0);
    magmaRound(key[3], &a0, &a1);
    magmaRound(key[4], &a1, &a0);
    magmaRound(key[5], &a0, &a1);
    magmaRound(key[6], &a1, &a0);
    magmaRound(key[7], &a0, &a1);

    magmaRound(key[7], &a1, &a0);
    magmaRound(key[6], &a0, &a1);
    magmaRound(key[5], &a1, &a0);
    magmaRound(key[4], &a0, &a1);
    magmaRound(key[3], &a1, &a0);
    magmaRound(key[2], &a0, &a1);
    magmaRound(key[1], &a1, &a0);
    magmaRound(key[0], &a0, &a1);

    return ((uint64_t)a0 << 32) | (uint64_t)a1;
}

uint64_t magmaDecryptBlock(uint64_t encryptedBlock, uint32_t* key)
{
    uint32_t a1 = (encryptedBlock >> 32) & 0xffffffff;
    uint32_t a0 = encryptedBlock & 0xffffffff;

    magmaRound(key[0], &a1, &a0);
    magmaRound(key[1], &a0, &a1);
    magmaRound(key[2], &a1, &a0);
    magmaRound(key[3], &a0, &a1);
    magmaRound(key[4], &a1, &a0);
    magmaRound(key[5], &a0, &a1);
    magmaRound(key[6], &a1, &a0);
    magmaRound(key[7], &a0, &a1);

    magmaRound(key[7], &a1, &a0);
    magmaRound(key[6], &a0, &a1);
    magmaRound(key[5], &a1, &a0);
    magmaRound(key[4], &a0, &a1);
    magmaRound(key[3], &a1, &a0);
    magmaRound(key[2], &a0, &a1);
    magmaRound(key[1], &a1, &a0);
    magmaRound(key[0], &a0, &a1);

    magmaRound(key[7], &a1, &a0);
    magmaRound(key[6], &a0, &a1);
    magmaRound(key[5], &a1, &a0);
    magmaRound(key[4], &a0, &a1);
    magmaRound(key[3], &a1, &a0);
    magmaRound(key[2], &a0, &a1);
    magmaRound(key[1], &a1, &a0);
    magmaRound(key[0], &a0, &a1);

    magmaRound(key[7], &a1, &a0);
    magmaRound(key[6], &a0, &a1);
    magmaRound(key[5], &a1, &a0);
    magmaRound(key[4], &a0, &a1);
    magmaRound(key[3], &a1, &a0);
    magmaRound(key[2], &a0, &a1);
    magmaRound(key[1], &a1, &a0);
    magmaRound(key[0], &a0, &a1);

    return ((uint64_t)a0 << 32) | (uint64_t)a1;
}
