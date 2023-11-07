#include "connectionhandler.h"

#include <mutex>
// 添加一个在线用户的TcpConnection
void ConnectionHandler::addConnection(int userId,
                                      muduo::net::TcpConnectionPtr tcpconn) {
    std::lock_guard<std::mutex> lock(_connMutex);
    _userConnMap.insert({userId, tcpconn});
}

// 删除一个即将离线用户的TcpConnection
int ConnectionHandler::delConnection(muduo::net::TcpConnectionPtr tcpconn) {
    std::lock_guard<std::mutex> lock(_connMutex);
    for (auto it = _userConnMap.begin(); it != _userConnMap.end(); ++it) {
        if (it->second == tcpconn) {
            int userId = it->first;
            _userConnMap.erase(it);
            return userId;
        }
    }
    return -1;  // 未知的TcpConnection
}

int ConnectionHandler::delConnection(int userId) {
    std::lock_guard<std::mutex> lock(_connMutex);
    auto it = _userConnMap.find(userId);
    if (it != _userConnMap.end()) {
        _userConnMap.erase(it);
        return userId;
    }
    return -1;  // 未知的用户Id
}

// 获取一个实例对象，线程安全
ConnectionHandler& ConnectionHandler::instance() {
    // 静态局部，底层汇编自动加锁解锁，保证线程安全
    static ConnectionHandler connectionHandler;
    return connectionHandler;
}

ConnectionHandler::ConnectionHandler() {
    // do nothing
}