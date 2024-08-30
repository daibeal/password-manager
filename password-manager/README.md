# Password Manager

## Backend (C++)

- Uses SQLite for database management.
- Uses OpenSSL for encryption.

## Frontend (React)

- User-friendly interface for managing passwords.
- Connects to the backend API to fetch and store passwords.

## Folder Structure

```
password-manager/
├── backend/
│   ├── build/
│   ├── include/
│   │   ├── db_manager.h
│   │   └── encryption.h
│   └── src/
│       └── main.cpp
└── frontend/
    ├── public/
    ├── src/
    ├── package.json
    └── ...
```

## Getting Started

### Backend

1. Navigate to the `backend` directory.
2. Build the project using your preferred C++ build system.

### Frontend

1. Navigate to the `frontend` directory.
2. Run `npm start` to start the development server.

