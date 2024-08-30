cmake_minimum_required(VERSION 3.10)
project(password_manager)

set(CMAKE_CXX_STANDARD 17)

add_executable(main backend/src/main.cpp)
add_executable(server server.cpp)

# Add the necessary libraries
target_link_libraries(main db_manager encryption)
target_link_libraries(server db_manager encryption httplib)