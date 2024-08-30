#include <iostream>
#include <string>
#include "db_manager.h"
#include "encryption.h"

// Function to add a password
bool addPassword(DBManager& dbManager, const std::string& site, const std::string& username, const std::string& password) {
    std::string encryptedPassword = Encryption::encrypt(password);
    return dbManager.insertPassword(site, username, encryptedPassword);
}

// Function to retrieve a password
std::string getPassword(DBManager& dbManager, const std::string& site, const std::string& username) {
    auto passwords = dbManager.getPasswords();
    for (const auto& [storedSite, storedUsername, encryptedPassword] : passwords) {
        if (storedSite == site && storedUsername == username) {
            return Encryption::decrypt(encryptedPassword);
        }
    }
    throw std::runtime_error("Password not found");
}

// Function to update a password
bool updatePassword(DBManager& dbManager, const std::string& site, const std::string& username, const std::string& newPassword) {
    std::string encryptedNewPassword = Encryption::encrypt(newPassword);
    return dbManager.updatePassword(site, username, encryptedNewPassword);
}

// Function to delete a password
bool deletePassword(DBManager& dbManager, const std::string& site, const std::string& username) {
    return dbManager.deletePassword(site, username);
}

// Function to list all passwords
void listPasswords(DBManager& dbManager) {
    auto passwords = dbManager.getPasswords();
    for (const auto& [site, username, encryptedPassword] : passwords) {
        std::string decryptedPassword = Encryption::decrypt(encryptedPassword);
        std::cout << "Site: " << site << ", Username: " << username << ", Password: " << decryptedPassword << std::endl;
    }
}

// Function to display the menu
void displayMenu() {
    std::cout << "\nPassword Manager Menu:\n";
    std::cout << "1. Add Password\n";
    std::cout << "2. Retrieve Password\n";
    std::cout << "3. Update Password\n";
    std::cout << "4. Delete Password\n";
    std::cout << "5. List All Passwords\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    std::cout << "Password Manager Backend" << std::endl;

    // Initialize DBManager
    DBManager dbManager("passwords.db");

    // Create the passwords table if it doesn't exist
    if (!dbManager.createTable()) {
        std::cerr << "Failed to create table." << std::endl;
        return 1;
    }

    int choice;
    std::string site, username, password, newPassword;

    while (true) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter site: ";
                std::cin >> site;
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                if (addPassword(dbManager, site, username, password)) {
                    std::cout << "Password added successfully.\n";
                } else {
                    std::cerr << "Failed to add password.\n";
                }
                break;

            case 2:
                std::cout << "Enter site: ";
                std::cin >> site;
                std::cout << "Enter username: ";
                std::cin >> username;
                try {
                    std::string retrievedPassword = getPassword(dbManager, site, username);
                    std::cout << "Retrieved Password: " << retrievedPassword << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;

            case 3:
                std::cout << "Enter site: ";
                std::cin >> site;
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter new password: ";
                std::cin >> newPassword;
                if (updatePassword(dbManager, site, username, newPassword)) {
                    std::cout << "Password updated successfully.\n";
                } else {
                    std::cerr << "Failed to update password.\n";
                }
                break;

            case 4:
                std::cout << "Enter site: ";
                std::cin >> site;
                std::cout << "Enter username: ";
                std::cin >> username;
                if (deletePassword(dbManager, site, username)) {
                    std::cout << "Password deleted successfully.\n";
                } else {
                    std::cerr << "Failed to delete password.\n";
                }
                break;

            case 5:
                listPasswords(dbManager);
                break;

            case 6:
                std::cout << "Exiting...\n";
                return 0;

            default:
                std::cerr << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}