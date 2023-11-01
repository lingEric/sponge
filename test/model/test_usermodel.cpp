#include <stdio.h>

#include <iostream>

#include "usermodel.h"
int main() {
    User user(1, "Eric", "123", "offline");
    UserModel usermodel;
    if (usermodel.insert(user)) {
        std::cout << "用户插入成功" << std::endl;
    }
    std::cout << "======================" << std::endl;
    User user2 = usermodel.query(5);
    std::cout << "用户查询成功" << std::endl << user2 << std::endl;

    std::cout << "======================" << std::endl;

    if (usermodel.updateState(5, "online")) {
        user2 = usermodel.query(5);
        std::cout << "修改之后的state为" << user2.state() << std::endl;
    };
    std::cout << "======================" << std::endl;
    if (usermodel.offlineAll()) {
        std::cout << "全部下线成功" << std::endl;
    }
}