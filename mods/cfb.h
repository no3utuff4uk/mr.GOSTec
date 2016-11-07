#ifndef CFB_H
#define CFB_H

int magmaEncryptCFB(uint32_t* key, uint64_t initL, uint64_t initR, std::ifstream& source, std::ofstream& destination);
int magmaDecryptCFB(uint32_t* key, std::ifstream& source, std::ofstream& destination);

#endif // CFB_H
