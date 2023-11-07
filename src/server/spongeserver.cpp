#include "spongeserver.h"

#include <functional>
#include <string>

#include "logger.h"
#include "msgdispatcher.h"
#include "msgtypeenum.h"
#include "userservice.h"
SpongeServer::SpongeServer(muduo::net::EventLoop *loop,
                           const muduo::net::InetAddress &listenAddr,
                           const std::string &name)
    : _server(loop, listenAddr, name), _loop(loop) {
    _server.setConnectionCallback(
        std::bind(&SpongeServer::onConnection, this, std::placeholders::_1));
    _server.setMessageCallback(
        std::bind(&SpongeServer::onMessage, this, std::placeholders::_1,
                  std::placeholders::_2, std::placeholders::_3));
    _server.setThreadNum(4);
}

void SpongeServer::start() {
    _server.start();
}

void SpongeServer::onConnection(const muduo::net::TcpConnectionPtr &conn) {
    if (!conn->connected()) {
        UserService::instance().clientCloseException(conn);
        conn->shutdown();
    }
}

void SpongeServer::onMessage(const muduo::net::TcpConnectionPtr &conn,
                             muduo::net::Buffer *buffer,
                             muduo::Timestamp timestamp) {
    // TODO
    // 对接收到的消息进行扩展，使其支持图片或者其它二进制文件类型，可以对首部字节进行判断分类处理
    std::string buf = buffer->retrieveAllAsString();
    LOG_INFO("%s | recv:%s", __func__, buf.c_str());

    nlohmann::json js;
    MsgHandler msghandler;
    try {
        js = nlohmann::json::parse(buf);
        MsgTypeEnum msgType =
            static_cast<MsgTypeEnum>(js["msgType"].get<int>());
        msghandler = MsgDispatcher::instance().getMsgHandler(msgType);
    } catch (nlohmann::json::exception e) {
        msghandler = MsgDispatcher::instance().getMsgHandler(
            MsgTypeEnum::PARSE_JSON_ERROR);
    }

    msghandler(conn, js, timestamp);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " ip port" << std::endl;
        return 1;
    }

    std::string ip = argv[1];
    std::string port = argv[2];

    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr(ip, std::stoi(port));
    SpongeServer server(&loop, addr, "SPONGE-SERVER");

    server.start();
    loop.loop();
    return 0;
}