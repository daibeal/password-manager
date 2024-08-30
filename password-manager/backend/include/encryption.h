#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <vector>

class Encryption {
public:
    static std::string encrypt(const std::string& plaintext);
    static std::string decrypt(const std::string& ciphertext);

private:
    static std::vector<unsigned char> generateKey();
    static std::vector<unsigned char> generateIV();
    static const int KEY_LENGTH = 32; // 256 bits
    static const int IV_LENGTH = 16;  // 128 bits
};

#endif // ENCRYPTION_H