//
// Created by badcw on 2021/7/15.
//

#include "utils.h"

namespace utils {

// Check it, result code should be SQLITE_OK
    int32_t CreateDB(const char *sql_file_path, sqlite3 **db) {
        std::string exec = "create table key_server(key text primary key not null,value blob not null);";
        printf("start to create db.\n");
        int result_code = SQLITE_OK;
        sqlite3_stmt *stmt = nullptr;
        do {
            if ((result_code = sqlite3_open_v2(sql_file_path, db,
                                               SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX |
                                               SQLITE_OPEN_SHAREDCACHE,
                                               nullptr)) != SQLITE_OK) {
                printf("create db file fail: %d, %s\n", result_code, sqlite3_errmsg(*db));
                break;
            }
            if ((result_code = sqlite3_prepare_v2(*db, exec.c_str(), -1, &stmt, nullptr)) != SQLITE_OK) {
                printf("ERROR when prepare sql exec: %d\n", result_code);
                break;
            }
            // shouldn't break, table may exist already.
            if ((result_code = sqlite3_step(stmt)) != SQLITE_DONE) {
                printf("ERROR when step stmt, maybe table exist: %d\n", result_code);
            }
            result_code = SQLITE_OK;
        } while (0);
        return result_code;
    }

// Check it, result code should be SQLITE_OK
    int32_t GetDB(sqlite3 *db, const std::string &key, std::string *value) {
        std::string exec = "select value from key_server where key='" + key + "';";
        printf("start to get db, SQL exec : %s\n", exec.c_str());
        sqlite3_stmt *stmt = nullptr;
        int result_code = SQLITE_OK;
        do {
            if ((result_code = sqlite3_prepare_v2(db, exec.c_str(), -1, &stmt, nullptr)) != SQLITE_OK) {
                printf("ERROR when prepare sql exec: %d\n", result_code);
                break;
            }
            if ((result_code = sqlite3_step(stmt)) != SQLITE_ROW) {
                printf("ERROR when get key from db, maybe key don't exist: %d\n", result_code);
                break;
            }
            const void *ptr = sqlite3_column_blob(stmt, 0);
            *value = static_cast<std::string>(static_cast<const char *>(ptr));
            result_code = SQLITE_OK;
        } while (0);
        return result_code;
    }

// Check it, result code should be SQLITE_OK
    int32_t PutDB(sqlite3 *db, const std::string &key, const std::string &value) {
        std::string exec = "insert into key_server (key, value) values ('" + key + "', ?);";
        printf("start to put db, SQL exec : %s\n", exec.c_str());
        sqlite3_stmt *stmt = nullptr;
        int result_code = SQLITE_OK;
        do {
            if ((result_code = sqlite3_prepare_v2(db, exec.c_str(), -1, &stmt, nullptr)) != SQLITE_OK) {
                printf("ERROR when prepare sql exec: %d\n", result_code);
                break;
            }
            if ((result_code = sqlite3_bind_blob(stmt, 1, value.c_str(), value.size(), SQLITE_STATIC)) != SQLITE_OK) {
                printf("ERROR when bind blob to sql stmt: %d, %s\n", result_code, sqlite3_errmsg(db));
                break;
            }
            if ((result_code = sqlite3_step(stmt)) != SQLITE_DONE) {
                printf("ERROR when step stmt: %d\n", result_code);
                break;
            }
            result_code = SQLITE_OK;
        } while (0);
        return result_code;
    }
}