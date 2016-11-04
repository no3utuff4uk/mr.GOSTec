#ifndef CTR_H
#define CTR_H

int magmaEncryptCTR(uint32_t* key, uint64_t init, std::ifstream& source, std::ofstream& destination);
int magmaDecryptCTR(uint32_t* key, std::ifstream& source, std::ofstream& destination);


#endif // CTR_H
