#pragma once
#include <vector>

#include "user.h"
class FriendModel {
public:
    // 插入好友数据
    bool insert(int userId, int friendId);

    // 返回用户好友列表
    std::vector<User> query(int userId);
};