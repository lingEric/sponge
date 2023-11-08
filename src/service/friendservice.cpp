#include "friendservice.h"

#include <string>
#include <unordered_map>

#include "connectionhandler.h"
#include "msgdispatcher.h"
#include "redisconnectionpool.h"

void FriendService::addFriend(const muduo::net::TcpConnectionPtr &conn,
                              nlohmann::json &js, muduo::Timestamp time) {
    if (js.contains("U1") && js.contains("U2")) {
        int u1 = js["U1"].get<int>();
        int u2 = js["U2"].get<int>();
        _friendModel.insert(u1, u2);
    } else {
        // 不合法的json
        MsgDispatcher::instance().getMsgHandler(MsgTypeEnum::PARSE_JSON_ERROR)(
            conn, js, time);
    }
}
void FriendService::requestAddFriend(const muduo::net::TcpConnectionPtr &conn,
                                     nlohmann::json &js,
                                     muduo::Timestamp time) {
    if (js.contains("TOID")) {
        int toUserId = js["TOID"].get<int>();
        if (!ConnectionHandler::instance().forwardMsg(toUserId, js.dump())) {
            // 不在本服务器或未登录
            User user = _userModel.query(toUserId);
            if (user.state() == "offline") {
                // 用户不在线，转存为离线消息
                _offlineMsgModel.insert(toUserId, js.dump());
            } else {
                // 用户不在本服务器
                RedisConnectionPool::instance().publish(
                    "sponge-user-" + std::to_string(toUserId), js.dump());
            }
        }
    } else {
        // 不合法的json
        MsgDispatcher::instance().getMsgHandler(MsgTypeEnum::PARSE_JSON_ERROR)(
            conn, js, time);
    }
}

void FriendService::delFriend(const muduo::net::TcpConnectionPtr &conn,
                              nlohmann::json &js, muduo::Timestamp time) {
    if (js.contains("FROMID") && js.contains("TOID")) {
        int fromId = js["FROMID"].get<int>();
        int toId = js["TOID"].get<int>();
        _friendModel.deleteFriend(fromId, toId);
    } else {
        // 不合法的json
        MsgDispatcher::instance().getMsgHandler(MsgTypeEnum::PARSE_JSON_ERROR)(
            conn, js, time);
    }
}

void FriendService::allFriends(const muduo::net::TcpConnectionPtr &conn,
                               nlohmann::json &js, muduo::Timestamp time) {
    if (js.contains("FROMID")) {
        int fromId = js["FROMID"].get<int>();
        std::vector<User> friendUsers = _friendModel.query(fromId);
        std::vector<std::unordered_map<std::string, std::string>> friends;
        for (auto &i : friendUsers) {
            std::unordered_map<std::string, std::string> obj;
            obj["id"] = std::to_string(i.id());
            obj["name"] = i.name();
            obj["password"] = i.password();
            obj["state"] = i.state();
            friends.push_back(obj);
        }

        nlohmann::json response;
        response["msgType"] = static_cast<int>(MsgTypeEnum::NORMAL_ACK);
        response["errno"] = 200;
        response["friends"] = friends;
        conn->send(response.dump());
    } else {
        // 不合法的json
        MsgDispatcher::instance().getMsgHandler(MsgTypeEnum::PARSE_JSON_ERROR)(
            conn, js, time);
    }
}

FriendService &FriendService::instance() {
    static FriendService friendService;
    return friendService;
}
FriendService::FriendService() {
    // do nothing
}