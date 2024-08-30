#include <iostream>
#include <string>
#include <vector>
#include "common.h"

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
    if (!initializeDB()) {
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
                if (addPassword(site, username, password)) {
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
                    std::string retrievedPassword = getPassword(site, username);
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
                if (updatePassword(site, username, newPassword)) {
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
                if (deletePassword(site, username)) {
                    std::cout << "Password deleted successfully.\n";
                } else {
                    std::cerr << "Failed to delete password.\n";
                }
                break;

            case 5: {
                std::vector<std::tuple<std::string, std::string, std::string>> passwords;
                listPasswords(passwords); // Updated to use a vector of tuples

                for (const auto& [site, username, password] : passwords) {
                    std::cout << "Site: " << site << ", Username: " << username << ", Password: " << password << std::endl;
                }
                break;
            }

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