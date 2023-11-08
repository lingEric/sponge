#pragma once

enum class MsgTypeEnum {
    // 请求处理
    USER_LOGIN = 1,   // 用户登录请求
    USER_REG = 2,     // 用户注册请求
    USER_LOGOUT = 3,  // 用户注销请求

    USER_CHAT = 4,    // 用户聊天消息

    // 响应处理
    NORMAL_ACK = 200,  // 常规响应

    // 错误处理
    PARSE_JSON_ERROR = 401,      // json 字符串解析错误
    METHOD_NOT_FOUND = 404,      // 未找到请求的回调函数
    SERVER_PROCESS_ERROR = 500,  // 服务器出错
};