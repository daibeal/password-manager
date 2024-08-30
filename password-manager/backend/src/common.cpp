#include "common.h"

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

void listPasswords(std::vector<std::string>& passwords) {
    // Example implementation
    passwords.push_back("example_password_1");
    passwords.push_back("example_password_2");
    // Add more passwords as needed
}