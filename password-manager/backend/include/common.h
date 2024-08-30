#ifndef COMMON_H
#define COMMON_H

#include <string>
#include "db_manager.h"
#include "encryption.h"

extern DBManager dbManager;

bool initializeDB();
bool addPassword(const std::string& site, const std::string& username, const std::string& password);
std::string getPassword(const std::string& site, const std::string& username);
bool updatePassword(const std::string& site, const std::string& username, const std::string& newPassword);
bool deletePassword(const std::string& site, const std::string& username);
void listPasswords(std::string& response);

#endif // COMMON_H