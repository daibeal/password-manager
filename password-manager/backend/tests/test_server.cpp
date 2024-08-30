#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "httplib.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"

using namespace httplib;

const std::string BASE_URL = "http://localhost:8080";

void print_result(bool success, const std::string& test_name) {
    if (success) {
        spdlog::info("Test {}: OK", test_name);
    } else {
        spdlog::error("Test {}: FAIL", test_name);
    }
}

bool add_password() {
    Client cli(BASE_URL.c_str());
    auto res = cli.Post("/add_password", "site=example.com&username=user&password=pass", "application/x-www-form-urlencoded");
    return res && res->status == 200;
}

bool get_password(const std::string& expected_password) {
    Client cli(BASE_URL.c_str());
    auto res = cli.Get("/get_password?site=example.com&username=user");
    return res && res->status == 200 && res->body == expected_password;
}

bool update_password() {
    Client cli(BASE_URL.c_str());
    auto res = cli.Put("/update_password", "site=example.com&username=user&new_password=newpass", "application/x-www-form-urlencoded");
    return res && res->status == 200;
}

bool delete_password() {
    Client cli(BASE_URL.c_str());
    auto res = cli.Delete("/delete_password?site=example.com&username=user");
    return res && res->status == 200;
}

bool list_passwords() {
    Client cli(BASE_URL.c_str());
    auto res = cli.Get("/list_passwords");
    return res && res->status == 200 && res->body.empty();
}

int main() {
    // Create a multi-sink logger
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/test_server.log", 1024 * 1024 * 5, 3);
    std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink};
    auto logger = std::make_shared<spdlog::logger>("multi_sink", sinks.begin(), sinks.end());
    spdlog::set_default_logger(logger);
    spdlog::set_level(spdlog::level::info); // Set global log level to info
    spdlog::flush_on(spdlog::level::info); // Flush logs on info level

    // Start the server
    spdlog::info("Starting server...");
    system("./server &");
    std::this_thread::sleep_for(std::chrono::seconds(5)); // Wait for the server to initialize

    // Run the tests
    print_result(add_password(), "Add Password");
    print_result(get_password("pass"), "Get Password");
    print_result(update_password(), "Update Password");
    print_result(get_password("newpass"), "Get Updated Password");
    print_result(delete_password(), "Delete Password");
    print_result(list_passwords(), "List Passwords");

    // Stop the server
    spdlog::info("Stopping server...");
    system("pkill server");

    return 0;
}