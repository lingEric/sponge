#include "groupmodel.h"

#include <vector>

#include "logger.h"
#include "mysqlconnectionpool.h"
bool GroupModel::createGroup(Group &group) {
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql),
             "insert into `group`(name, description) values('%s', '%s')",
             group.name().c_str(), group.desc().c_str());
    LOG_INFO("%s | %s", __func__, sql);

    return MysqlConnectionPool::getInstance().getConnection()->update(sql);
}

bool GroupModel::addGroup(int userId, int groupId, std::string role) {
    char sql[1024] = {0};
    snprintf(
        sql, sizeof(sql),
        "insert into groupuser(groupid, userid, role) values(%d, %d, '%s')",
        groupId, userId, role.c_str());
    LOG_INFO("%s | %s", __func__, sql);

    return MysqlConnectionPool::getInstance().getConnection()->update(sql);
}

std::vector<Group> GroupModel::queryGroups(int userId) {
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql),
             "select a.id, a.name, a.description from `group` a inner join \
         groupuser b on a.id = b.groupid where b.userid=%d",
             userId);
    LOG_INFO("%s | %s", __func__, sql);

    std::shared_ptr<sql::ResultSet> rs =
        MysqlConnectionPool::getInstance().getConnection()->query(sql);
    std::vector<Group> vec;
    while (rs->next()) {
        vec.emplace_back(Group(rs->getInt("id"), rs->getString("name"),
                               rs->getString("description")));
    }
    return vec;
}

std::vector<Group> GroupModel::queryGroups(std::string groupname) {
    char sql[1024] = {0};
    snprintf(
        sql, sizeof(sql),
        "select a.id, a.name, a.description from `group` a where a.name like '%%%s%%'",
        groupname.c_str());
    LOG_INFO("%s | %s", __func__, sql);

    std::shared_ptr<sql::ResultSet> rs =
        MysqlConnectionPool::getInstance().getConnection()->query(sql);
    std::vector<Group> vec;
    while (rs->next()) {
        vec.emplace_back(Group(rs->getInt("id"), rs->getString("name"),
                               rs->getString("description")));
    }
    return vec;
}

std::vector<int> GroupModel::queryGroupUsers(int groupId) {
    char sql[1024] = {0};
    snprintf(sql, sizeof(sql),
             "select userid from groupuser where groupid = %d", groupId);
    LOG_INFO("%s | %s", __func__, sql);

    std::shared_ptr<sql::ResultSet> rs =
        MysqlConnectionPool::getInstance().getConnection()->query(sql);
    std::vector<int> vec;
    while (rs->next()) {
        vec.emplace_back(rs->getInt("userid"));
    }
    return vec;
}