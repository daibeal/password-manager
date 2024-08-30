# Use a specific version of the Ubuntu image as a parent image
FROM ubuntu:20.04

# Set the working directory in the container
WORKDIR /usr/src/app

# Install dependencies
RUN echo "Updating package lists..." && \
    apt-get update && \
    echo "Installing required packages..." && \
    apt-get install -y \
    gcc \
    g++ \
    libssl-dev \
    libsodium-dev \
    sqlite3 \
    libsqlite3-dev \
    curl \
    build-essential && \
    echo "Cleaning up..." && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Copy the backend directory contents into the container at /usr/src/app/backend
COPY backend backend

# Download and install OpenSSL
RUN echo "Downloading OpenSSL..." && \
    curl -O https://www.openssl.org/source/openssl-1.1.1l.tar.gz && \
    echo "Extracting OpenSSL..." && \
    tar -xzf openssl-1.1.1l.tar.gz && \
    cd openssl-1.1.1l && \
    echo "Configuring OpenSSL..." && \
    ./config && \
    echo "Building OpenSSL..." && \
    make && \
    echo "Installing OpenSSL..." && \
    make install && \
    cd .. && \
    echo "Cleaning up OpenSSL files..." && \
    rm -rf openssl-1.1.1l.tar.gz openssl-1.1.1l

# Download and install cpp-httplib
RUN echo "Downloading cpp-httplib..." && \
    curl -O https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h && \
    echo "Creating include directory..." && \
    mkdir -p /usr/src/app/backend/include && \
    echo "Moving httplib.h to include directory..." && \
    mv httplib.h /usr/src/app/backend/include/

# Check if required libraries and include directories are available
RUN echo "Checking /usr/local/ssl/include..." && \
    ls -l /usr/local/ssl && \
    if [ ! -d "/usr/local/ssl/include" ]; then echo "Error: /usr/local/ssl/include not found"; exit 1; fi

RUN echo "Checking /usr/local/include..." && \
    ls -l /usr/local && \
    if [ ! -d "/usr/local/include" ]; then echo "Error: /usr/local/include not found"; exit 1; fi

RUN echo "Checking /usr/src/app/backend/include..." && \
    ls -l /usr/src/app/backend && \
    if [ ! -d "/usr/src/app/backend/include" ]; then echo "Error: /usr/src/app/backend/include not found"; exit 1; fi

RUN echo "Checking /usr/local/lib/libssl.so..." && \
    ls -l /usr/local/lib && \
    if [ ! -f "/usr/local/lib/libssl.so" ]; then echo "Error: /usr/local/lib/libssl.so not found"; exit 1; fi

RUN echo "Checking /usr/local/lib/libcrypto.so..." && \
    ls -l /usr/local/lib && \
    if [ ! -f "/usr/local/lib/libcrypto.so" ]; then echo "Error: /usr/local/lib/libcrypto.so not found"; exit 1; fi

RUN echo "Checking /usr/lib/x86_64-linux-gnu/libsodium.so.23..." && \
    ls -l /usr/lib/x86_64-linux-gnu && \
    if [ ! -f "/usr/lib/x86_64-linux-gnu/libsodium.so.23" ]; then echo "Error: /usr/lib/x86_64-linux-gnu/libsodium.so.23 not found"; exit 1; fi

RUN echo "Checking /usr/lib/x86_64-linux-gnu/libsqlite3.so.0..." && \
    ls -l /usr/lib/x86_64-linux-gnu && \
    if [ ! -f "/usr/lib/x86_64-linux-gnu/libsqlite3.so.0" ]; then echo "Error: /usr/lib/x86_64-linux-gnu/libsqlite3.so.0 not found"; exit 1; fi

# Compile the main application
RUN echo "Compiling main application..." && \
    g++ -std=c++17 -I/usr/local/ssl/include -I/usr/local/include -I/usr/src/app/backend/include -L/usr/local/lib -o main /usr/src/app/backend/src/main.cpp /usr/src/app/backend/src/encryption.cpp /usr/src/app/backend/src/db_manager.cpp -lssl -lcrypto -lsodium -lsqlite3 -lpthread

# Compile the server application
RUN echo "Compiling server application..." && \
    g++ -std=c++17 -I/usr/local/ssl/include -I/usr/local/include -I/usr/src/app/backend/include -L/usr/local/lib -o server /usr/src/app/backend/src/server.cpp /usr/src/app/backend/src/encryption.cpp /usr/src/app/backend/src/db_manager.cpp -lssl -lcrypto -lsodium -lsqlite3 -lpthread

# Expose the port the server will run on
EXPOSE 8080

# Run the server application
CMD echo "Starting server..." && ./server