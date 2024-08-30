#include "db_manager.h"
#include <iostream>

DBManager::DBManager(const std::string& dbFile) {
    if (sqlite3_open(dbFile.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
}

DBManager::~DBManager() {
    if (db) {
        sqlite3_close(db);
    }
}

bool DBManager::createTable() {
    const char* sql = "CREATE TABLE IF NOT EXISTS passwords ("
                      "site TEXT NOT NULL,"
                      "username TEXT NOT NULL,"
                      "password BLOB NOT NULL,"
                      "PRIMARY KEY (site, username));";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool DBManager::insertPassword(const std::string& site, const std::string& username, const std::string& password) {
    const char* sql = "INSERT INTO passwords (site, username, password) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, site.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 3, password.data(), password.size(), SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

bool DBManager::updatePassword(const std::string& site, const std::string& username, const std::string& newPassword) {
    const char* sql = "UPDATE passwords SET password = ? WHERE site = ? AND username = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_blob(stmt, 1, newPassword.data(), newPassword.size(), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, site.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, username.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

bool DBManager::deletePassword(const std::string& site, const std::string& username) {
    const char* sql = "DELETE FROM passwords WHERE site = ? AND username = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, site.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

std::vector<std::tuple<std::string, std::string, std::string>> DBManager::getPasswords() {
    const char* sql = "SELECT site, username, password FROM passwords;";
    sqlite3_stmt* stmt;
    std::vector<std::tuple<std::string, std::string, std::string>> passwords;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return passwords;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string site = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string password(reinterpret_cast<const char*>(sqlite3_column_blob(stmt, 2)), sqlite3_column_bytes(stmt, 2));
        passwords.emplace_back(site, username, password);
    }

    sqlite3_finalize(stmt);
    return passwords;
}