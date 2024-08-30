#include <iostream>
#include <string>
#include "httplib.h"
#include "common.h"

using namespace httplib;

void addRoutes(Server& svr) {
    svr.Post("/add_password", [](const Request& req, Response& res) {
        auto site = req.get_param_value("site");
        auto username = req.get_param_value("username");
        auto password = req.get_param_value("password");

        std::cout << "POST /add_password" << std::endl;
        std::cout << "Site: " << site << ", Username: " << username << ", Password: " << password << std::endl;

        if (addPassword(site, username, password)) {
            res.set_content("Password added successfully", "text/plain");
            std::cout << "Response: Password added successfully" << std::endl;
        } else {
            res.status = 500;
            res.set_content("Failed to add password", "text/plain");
            std::cout << "Response: Failed to add password" << std::endl;
        }
    });

    svr.Get("/get_password", [](const Request& req, Response& res) {
        auto site = req.get_param_value("site");
        auto username = req.get_param_value("username");

        std::cout << "GET /get_password" << std::endl;
        std::cout << "Site: " << site << ", Username: " << username << std::endl;

        try {
            std::string retrievedPassword = getPassword(site, username);
            res.set_content(retrievedPassword, "text/plain");
            std::cout << "Response: " << retrievedPassword << std::endl;
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content(e.what(), "text/plain");
            std::cout << "Response: " << e.what() << std::endl;
        }
    });

    svr.Put("/update_password", [](const Request& req, Response& res) {
        auto site = req.get_param_value("site");
        auto username = req.get_param_value("username");
        auto newPassword = req.get_param_value("new_password");

        std::cout << "PUT /update_password" << std::endl;
        std::cout << "Site: " << site << ", Username: " << username << ", New Password: " << newPassword << std::endl;

        if (updatePassword(site, username, newPassword)) {
            res.set_content("Password updated successfully", "text/plain");
            std::cout << "Response: Password updated successfully" << std::endl;
        } else {
            res.status = 500;
            res.set_content("Failed to update password", "text/plain");
            std::cout << "Response: Failed to update password" << std::endl;
        }
    });

    svr.Delete("/delete_password", [](const Request& req, Response& res) {
        auto site = req.get_param_value("site");
        auto username = req.get_param_value("username");

        std::cout << "DELETE /delete_password" << std::endl;
        std::cout << "Site: " << site << ", Username: " << username << std::endl;

        if (deletePassword(site, username)) {
            res.set_content("Password deleted successfully", "text/plain");
            std::cout << "Response: Password deleted successfully" << std::endl;
        } else {
            res.status = 500;
            res.set_content("Failed to delete password", "text/plain");
            std::cout << "Response: Failed to delete password" << std::endl;
        }
    });

    svr.Get("/list_passwords", [](const Request& req, Response& res) {
        std::cout << "GET /list_passwords" << std::endl;

        std::string response;
        listPasswords(response);
        res.set_content(response, "text/plain");
        std::cout << "Response: " << response << std::endl;
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