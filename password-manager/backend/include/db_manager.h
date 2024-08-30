#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <string>
#include <vector>
#include <tuple>
#include <sqlite3.h>

class DBManager {
public:
    DBManager(const std::string& dbFile);
    ~DBManager();

    bool createTable();
    bool insertPassword(const std::string& site, const std::string& username, const std::string& password);
    bool updatePassword(const std::string& site, const std::string& username, const std::string& newPassword);
    bool deletePassword(const std::string& site, const std::string& username);
    std::vector<std::tuple<std::string, std::string, std::string>> getPasswords();

private:
    sqlite3* db;
};

#endif // DB_MANAGER_H