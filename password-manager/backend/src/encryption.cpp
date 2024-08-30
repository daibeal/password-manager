#include "encryption.h"
#include <sodium.h>
#include <vector>
#include <stdexcept>
#include <cstring>

std::vector<unsigned char> Encryption::generateKey() {
    std::vector<unsigned char> key(crypto_secretbox_KEYBYTES);
    randombytes_buf(key.data(), crypto_secretbox_KEYBYTES);
    return key;
}

std::vector<unsigned char> Encryption::generateIV() {
    std::vector<unsigned char> iv(crypto_secretbox_NONCEBYTES);
    randombytes_buf(iv.data(), crypto_secretbox_NONCEBYTES);
    return iv;
}

std::string Encryption::encrypt(const std::string& plaintext) {
    std::vector<unsigned char> key = generateKey();
    std::vector<unsigned char> iv = generateIV();

    std::vector<unsigned char> ciphertext(crypto_secretbox_MACBYTES + plaintext.size());
    if (crypto_secretbox_easy(ciphertext.data(), reinterpret_cast<const unsigned char*>(plaintext.data()), plaintext.size(), iv.data(), key.data()) != 0) {
        throw std::runtime_error("Encryption failed");
    }

    // Append IV and key to the ciphertext for decryption
    ciphertext.insert(ciphertext.end(), iv.begin(), iv.end());
    ciphertext.insert(ciphertext.end(), key.begin(), key.end());

    return std::string(ciphertext.begin(), ciphertext.end());
}

std::string Encryption::decrypt(const std::string& ciphertext) {
    if (ciphertext.size() < crypto_secretbox_NONCEBYTES + crypto_secretbox_KEYBYTES + crypto_secretbox_MACBYTES) {
        throw std::runtime_error("Invalid ciphertext");
    }

    std::vector<unsigned char> iv(ciphertext.end() - crypto_secretbox_NONCEBYTES - crypto_secretbox_KEYBYTES, ciphertext.end() - crypto_secretbox_KEYBYTES);
    std::vector<unsigned char> key(ciphertext.end() - crypto_secretbox_KEYBYTES, ciphertext.end());
    std::vector<unsigned char> encrypted_data(ciphertext.begin(), ciphertext.end() - crypto_secretbox_NONCEBYTES - crypto_secretbox_KEYBYTES);

    std::vector<unsigned char> decrypted_data(encrypted_data.size() - crypto_secretbox_MACBYTES);
    if (crypto_secretbox_open_easy(decrypted_data.data(), encrypted_data.data(), encrypted_data.size(), iv.data(), key.data()) != 0) {
        throw std::runtime_error("Decryption failed");
    }

    return std::string(decrypted_data.begin(), decrypted_data.end());
}