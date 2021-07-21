//
// Created by 孟钦宇 on 2021/7/15.
//

#ifndef GRPC_TEST_UTILS_H
#define GRPC_TEST_UTILS_H

// internal stl
#include <cstdint>
#include <string>

// lib outside
#include "sqlite3.h"

// user lib

namespace utils {
    int32_t CreateDB(const char *sql_file_path, sqlite3 **db);
    int32_t GetDB(sqlite3 *db, const std::string &key, std::string *value);
    int32_t PutDB(sqlite3 *db, const std::string &key, const std::string &value);
};


#endif //GRPC_TEST_UTILS_H
