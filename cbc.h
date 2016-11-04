#ifndef CBC_H
#define CBC_H

int magmaEncryptCBC(uint32_t* key, uint64_t initL, uint64_t initR, std::ifstream& source, std::ofstream& destination);
int magmaDecryptCBC(uint32_t* key, std::ifstream& source, std::ofstream& destination);

#endif // CBC_H
