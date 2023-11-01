#include "offlinemessagemodel.h"

#include <string>
#include <vector>

#include "logger.h"
#include "mysqlconnectionpool.h"

bool OfflineMsgModel::insert(int userId, std::string msg) {
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql),
             "insert into offlinemessage(userid, message) values(%d, '%s')",
             userId, msg.c_str());
    LOG_INFO("%s | %s", __func__, sql);

    return MysqlConnectionPool::getInstance().getConnection()->update(sql);
}

bool OfflineMsgModel::remove(int userId) {
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql), "delete from offlinemessage where userid=%d",
             userId);
    LOG_INFO("%s | %s", __func__, sql);

    return MysqlConnectionPool::getInstance().getConnection()->update(sql);
}

std::vector<std::string> OfflineMsgModel::query(int userId) {
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql),
             "select message from offlinemessage where userid = %d", userId);
    LOG_INFO("%s | %s", __func__, sql);

    std::shared_ptr<sql::ResultSet> rs =
        MysqlConnectionPool::getInstance().getConnection()->query(sql);
    std::vector<std::string> vec;
    while (rs->next()) {
        vec.emplace_back(rs->getString("message"));
    }
    return vec;
}