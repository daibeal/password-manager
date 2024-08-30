#include <iostream>
#include <string>
#include <vector>
#include "httplib.h"
#include "common.h"
#include "../include/json.hpp" // Include nlohmann/json for JSON handling

using namespace httplib;
using json = nlohmann::json;

void add_cors_headers(Response& res) {
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
}

void addRoutes(Server& svr) {
    svr.Options(".*", [](const Request& req, Response& res) {
        add_cors_headers(res);
        res.set_content("", "text/plain");
    });

    svr.Post("/add_password", [](const Request& req, Response& res) {
        auto site = req.get_param_value("site");
        auto username = req.get_param_value("username");
        auto password = req.get_param_value("password");

        std::cout << "POST /add_password" << std::endl;
        std::cout << "Site: " << site << ", Username: " << username << ", Password: " << password << std::endl;

        json response;
        if (addPassword(site, username, password)) {
            response["message"] = "Password added successfully";
            res.set_content(response.dump(), "application/json");
            std::cout << "Response: Password added successfully" << std::endl;
        } else {
            res.status = 500;
            response["message"] = "Failed to add password";
            res.set_content(response.dump(), "application/json");
            std::cout << "Response: Failed to add password" << std::endl;
        }
        add_cors_headers(res);
    });

    svr.Get("/get_password", [](const Request& req, Response& res) {
        auto site = req.get_param_value("site");
        auto username = req.get_param_value("username");

        std::cout << "GET /get_password" << std::endl;
        std::cout << "Site: " << site << ", Username: " << username << std::endl;

        json response;
        try {
            std::string retrievedPassword = getPassword(site, username);
            response["password"] = retrievedPassword;
            res.set_content(response.dump(), "application/json");
            std::cout << "Response: " << retrievedPassword << std::endl;
        } catch (const std::exception& e) {
            res.status = 500;
            response["message"] = e.what();
            res.set_content(response.dump(), "application/json");
            std::cout << "Response: " << e.what() << std::endl;
        }
        add_cors_headers(res);
    });

    svr.Put("/update_password", [](const Request& req, Response& res) {
        auto site = req.get_param_value("site");
        auto username = req.get_param_value("username");
        auto newPassword = req.get_param_value("new_password");

        std::cout << "PUT /update_password" << std::endl;
        std::cout << "Site: " << site << ", Username: " << username << ", New Password: " << newPassword << std::endl;

        json response;
        if (updatePassword(site, username, newPassword)) {
            response["message"] = "Password updated successfully";
            res.set_content(response.dump(), "application/json");
            std::cout << "Response: Password updated successfully" << std::endl;
        } else {
            res.status = 500;
            response["message"] = "Failed to update password";
            res.set_content(response.dump(), "application/json");
            std::cout << "Response: Failed to update password" << std::endl;
        }
        add_cors_headers(res);
    });

    svr.Delete("/delete_password", [](const Request& req, Response& res) {
        auto site = req.get_param_value("site");
        auto username = req.get_param_value("username");

        std::cout << "DELETE /delete_password" << std::endl;
        std::cout << "Site: " << site << ", Username: " << username << std::endl;

        json response;
        if (deletePassword(site, username)) {
            response["message"] = "Password deleted successfully";
            res.set_content(response.dump(), "application/json");
            std::cout << "Response: Password deleted successfully" << std::endl;
        } else {
            res.status = 500;
            response["message"] = "Failed to delete password";
            res.set_content(response.dump(), "application/json");
            std::cout << "Response: Failed to delete password" << std::endl;
        }
        add_cors_headers(res);
    });

    svr.Get("/list_passwords", [](const Request& req, Response& res) {
        std::cout << "GET /list_passwords" << std::endl;

        std::vector<std::string> passwords;
        listPasswords(passwords); // Assuming listPasswords fills the vector with passwords

        json response = passwords; // Convert vector to JSON array
        res.set_content(response.dump(), "application/json");
        std::cout << "Response: " << response.dump() << std::endl;
        add_cors_headers(res);
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