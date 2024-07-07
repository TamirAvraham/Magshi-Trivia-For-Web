#include "SqlliteDatabase.h"
#include "UserException.h"
#include "sqlite3.h"
#include "UserManager.h"
#include <iostream>


SqlliteDatabase::SqlliteDatabase()
{
    int exit = 0;
    exit = sqlite3_open("game.db", &_db);
    if (exit) {
        std::cerr << "Error open DB " << sqlite3_errmsg(_db) << std::endl;
        throw UserException(sqlite3_errmsg(_db));
    }
    std::string sql = R"(CREATE TABLE IF NOT EXISTS users (
    ID INTEGER PRIMARY KEY AUTOINCREMENT,
    USERNAME TEXT NOT NULL,
    PASSWORD TEXT NOT NULL,
    EMAIL TEXT NOT NULL
);
)";
    char* messaggeError;
    exit = sqlite3_exec(_db, sql.c_str(), NULL, 0, &messaggeError);

    if (exit != SQLITE_OK) {
        std::cerr << "Error Create Table" << std::endl;
        sqlite3_free(messaggeError);
        throw UserException(sqlite3_errmsg(_db));
    }
}

int callback(void* data, int argc, char** argv, char** azColName)
{
    bool* userFound = static_cast<bool*> (data);
    *userFound = true;
    return 0;
}
User SqlliteDatabase::login(const std::string& username, const std::string& password)
{
    bool userFound = false;
    std::string sql = std::string("SELECT username FROM users WHERE username='") + username + std::string("' AND password='") + password + std::string("';");
    int rc = sqlite3_exec(_db, sql.c_str(),callback, &userFound, nullptr);
    if (rc) {
        throw UserException(sqlite3_errmsg(_db));
    }
    return UserManager::getInstance().login(username);
}

User SqlliteDatabase::signup(const std::string& username, const std::string& password, const std::string& email)
{
    const char* sql = "INSERT INTO users (username, password, email) VALUES (?, ?, ?)";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(_db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw UserException(sqlite3_errmsg(_db));
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, email.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        throw UserException(sqlite3_errmsg(_db));
    }

    sqlite3_finalize(stmt);
    return UserManager::getInstance().login(username);
}

SqlliteDatabase::~SqlliteDatabase()
{
    sqlite3_close(_db);
}
