#ifndef OFB_H
#define OFB_H

int magmaEncryptOFB(uint32_t* key, uint64_t initL, uint64_t initR, std::ifstream& source, std::ofstream& destination);
int magmaDecryptOFB(uint32_t* key, std::ifstream& source, std::ofstream& destination);

#endif // OFB_H
