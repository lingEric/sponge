#include "friendmodel.h"

#include "logger.h"
#include "mysqlconnectionpool.h"
bool FriendModel::insert(int userId, int friendId) {
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql),
             "insert into friend(userid, friendid) values(%d, %d)", userId,
             friendId);
    LOG_INFO("%s | %s", __func__, sql);
    return MysqlConnectionPool::getInstance().getConnection()->update(sql);
}

std::vector<User> FriendModel::query(int userId) {
    char sql[1024] = {0};

    snprintf(sql, sizeof(sql),
             "select a.id, a.name, a.state from user a inner join friend b on "
             "b.friendid = a.id where b.userid=%d",
             userId);
    LOG_INFO("%s | %s", __func__, sql);
    std::vector<User> vec;

    std::shared_ptr<sql::ResultSet> rs =
        MysqlConnectionPool::getInstance().getConnection()->query(sql);
    while (rs->next()) {
        vec.emplace_back(User(rs->getInt("id"), rs->getString("name"), "",
                              rs->getString("state")));
    }
    return vec;
}