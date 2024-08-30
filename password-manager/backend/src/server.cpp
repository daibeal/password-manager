#include <iostream>
#include <string>
#include "httplib.h"
#include "db_manager.h"
#include "encryption.h"

using namespace httplib;

DBManager dbManager("passwords.db");

bool initializeDB() {
    return dbManager.createTable();
}

void addRoutes(Server& svr) {
    svr.Post("/add_password", [](const Request& req, Response& res) {
        auto site = req.get_param_value("site");
        auto username = req.get_param_value("username");
        auto password = req.get_param_value("password");
        std::string encryptedPassword = Encryption::encrypt(password);
        if (dbManager.insertPassword(site, username, encryptedPassword)) {
            res.set_content("Password added successfully", "text/plain");
        } else {
            res.status = 500;
            res.set_content("Failed to add password", "text/plain");
        }
    });

    svr.Get("/get_password", [](const Request& req, Response& res) {
        auto site = req.get_param_value("site");
        auto username = req.get_param_value("username");
        try {
            auto passwords = dbManager.getPasswords();
            for (const auto& [storedSite, storedUsername, encryptedPassword] : passwords) {
                if (storedSite == site && storedUsername == username) {
                    std::string decryptedPassword = Encryption::decrypt(encryptedPassword);
                    res.set_content(decryptedPassword, "text/plain");
                    return;
                }
            }
            res.status = 404;
            res.set_content("Password not found", "text/plain");
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content(e.what(), "text/plain");
        }
    });

    svr.Put("/update_password", [](const Request& req, Response& res) {
        auto site = req.get_param_value("site");
        auto username = req.get_param_value("username");
        auto newPassword = req.get_param_value("new_password");
        std::string encryptedNewPassword = Encryption::encrypt(newPassword);
        if (dbManager.updatePassword(site, username, encryptedNewPassword)) {
            res.set_content("Password updated successfully", "text/plain");
        } else {
            res.status = 500;
            res.set_content("Failed to update password", "text/plain");
        }
    });

    svr.Delete("/delete_password", [](const Request& req, Response& res) {
        auto site = req.get_param_value("site");
        auto username = req.get_param_value("username");
        if (dbManager.deletePassword(site, username)) {
            res.set_content("Password deleted successfully", "text/plain");
        } else {
            res.status = 500;
            res.set_content("Failed to delete password", "text/plain");
        }
    });

    svr.Get("/list_passwords", [](const Request& req, Response& res) {
        auto passwords = dbManager.getPasswords();
        std::string response;
        for (const auto& [site, username, encryptedPassword] : passwords) {
            std::string decryptedPassword = Encryption::decrypt(encryptedPassword);
            response += "Site: " + site + ", Username: " + username + ", Password: " + decryptedPassword + "\n";
        }
        res.set_content(response, "text/plain");
    });
}

int main() {
    if (!initializeDB()) {
        std::cerr << "Failed to create table." << std::endl;
        return 1;
    }

    Server svr;
    addRoutes(svr);

    std::cout << "Starting server on port 8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}