#ifndef ECB_H
#define ECB_H

int magmaEncryptECB(uint32_t* key, std::ifstream& source, std::ofstream& destination);
int magmaDecryptECB(uint32_t* key, std::ifstream& source, std::ofstream& destination);

#endif // ECB_H
