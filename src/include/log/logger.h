#pragma once
#include <string.h>

#include <string>

#include "blockingqueue.h"

// 使用示例
// LOG_INFO("xxx %d %s", 20, "xxxx")

#define LOG_INFO(logmsgformat, ...)                                  \
    do {                                                             \
        Logger &logger = Logger::GetInstance();                      \
        char buffer[128 + 1024] = {0};                               \
        snprintf(buffer, 128, "[INFO] %s:%d |", __FILE__, __LINE__); \
        char msg[1024] = {0};                                        \
        snprintf(msg, 1024, logmsgformat, ##__VA_ARGS__);            \
        strcat(buffer, msg);                                         \
        logger.Log(buffer);                                          \
    } while (0)

#define LOG_ERROR(logmsgformat, ...)                                  \
    do {                                                              \
        Logger &logger = Logger::GetInstance();                       \
        char buffer[128 + 1024] = {0};                                \
        snprintf(buffer, 128, "[ERROR] %s:%d |", __FILE__, __LINE__); \
        char msg[1024] = {0};                                         \
        snprintf(msg, 1024, logmsgformat, ##__VA_ARGS__);             \
        strcat(buffer, msg);                                          \
        logger.Log(buffer);                                           \
    } while (0)

// 线程安全的异步日志工具类
class Logger {
public:
    static Logger &GetInstance();
    void Log(std::string msg);

private:
    BlockingQueue<std::string> _logQue;  // 线程安全的日志队列

    Logger();
    Logger(const Logger &) = delete;
    Logger(Logger &&) = delete;
};