#include "common.h"
#include "encryption.h" // Include Encryption

DBManager dbManager("passwords.db");

bool initializeDB() {
    return dbManager.createTable();
}

bool addPassword(const std::string& site, const std::string& username, const std::string& password) {
    std::string encryptedPassword = Encryption::encrypt(password);
    return dbManager.insertPassword(site, username, encryptedPassword);
}

std::string getPassword(const std::string& site, const std::string& username) {
    auto passwords = dbManager.getPasswords();
    for (const auto& [storedSite, storedUsername, encryptedPassword] : passwords) {
        if (storedSite == site && storedUsername == username) {
            return Encryption::decrypt(encryptedPassword);
        }
    }
    throw std::runtime_error("Password not found");
}

bool updatePassword(const std::string& site, const std::string& username, const std::string& newPassword) {
    std::string encryptedNewPassword = Encryption::encrypt(newPassword);
    return dbManager.updatePassword(site, username, encryptedNewPassword);
}

bool deletePassword(const std::string& site, const std::string& username) {
    return dbManager.deletePassword(site, username);
}

void listPasswords(std::vector<std::tuple<std::string, std::string, std::string>>& passwords) {
    passwords = dbManager.getPasswords();
}