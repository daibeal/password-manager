#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <tuple>
#include "db_manager.h" // Include DBManager

extern DBManager dbManager;

bool initializeDB();
bool addPassword(const std::string& site, const std::string& username, const std::string& password);
std::string getPassword(const std::string& site, const std::string& username);
bool updatePassword(const std::string& site, const std::string& username, const std::string& newPassword);
bool deletePassword(const std::string& site, const std::string& username);
void listPasswords(std::vector<std::tuple<std::string, std::string, std::string>>& passwords);

#endif // COMMON_H