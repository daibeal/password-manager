#!/bin/bash

# Create the build directory if it doesn't exist
mkdir -p backend/build

# Create the logs directory if it doesn't exist
mkdir -p backend/logs

# Set the include and library paths
INCLUDE_PATHS="-I/usr/local/ssl/include -I/usr/local/include -Ibackend/include -I/usr/local/include/spdlog"
LIBRARY_PATHS="-L/usr/local/lib"
LIBRARIES="-lssl -lcrypto -lsodium -lsqlite3 -lpthread"

# Compile the main application
echo "Compiling main application..."
g++ -std=c++17 $INCLUDE_PATHS -c backend/src/main.cpp -o backend/build/main.o
g++ -std=c++17 $INCLUDE_PATHS -c backend/src/encryption.cpp -o backend/build/encryption.o
g++ -std=c++17 $INCLUDE_PATHS -c backend/src/db_manager.cpp -o backend/build/db_manager.o
g++ -std=c++17 $INCLUDE_PATHS -c backend/src/common.cpp -o backend/build/common.o
g++ -std=c++17 $LIBRARY_PATHS -o backend/build/main backend/build/main.o backend/build/encryption.o backend/build/db_manager.o backend/build/common.o $LIBRARIES
if [ $? -ne 0 ]; then
    echo "Failed to compile main application"
    exit 1
fi

# Compile the server application
echo "Compiling server application..."
g++ -std=c++17 $INCLUDE_PATHS -c backend/src/server.cpp -o backend/build/server.o
g++ -std=c++17 $LIBRARY_PATHS -o backend/build/server backend/build/server.o backend/build/encryption.o backend/build/db_manager.o backend/build/common.o $LIBRARIES
if [ $? -ne 0 ]; then
    echo "Failed to compile server application"
    exit 1
fi

# Compile the test application
echo "Compiling test application..."
g++ -std=c++17 $INCLUDE_PATHS -c backend/tests/test_server.cpp -o backend/build/test_server.o
g++ -std=c++17 $LIBRARY_PATHS -o backend/build/test_server backend/build/test_server.o $LIBRARIES
if [ $? -ne 0 ]; then
    echo "Failed to compile test application"
    exit 1
fi

echo "All applications compiled successfully"