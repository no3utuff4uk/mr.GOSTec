#ifndef MAGMA_H
#define MAGMA_H

int testMagmaEncryptDecryptBlock();
uint64_t magmaEncryptBlock(uint64_t openBlock, uint32_t* key);
uint64_t magmaDecryptBlock(uint64_t encryptedBlock, uint32_t* key);

#endif // MAGMA_H
