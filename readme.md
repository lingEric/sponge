# todo 
// 登录
{"msgType":1, "USERID":6, "password":"6"}
{"msgType":1, "USERID":7, "password":"7"}
// 注册用户
{"msgType":2, "name":"1", "password":"1"}
// 退出登录
{"msgType":3, "USERID":7}


// 用户聊天
{"msgType":4,"FROMID":6,"TOID":7,"msg":"hello 7号","sendTime":"20231107 18:05:01"}
{"msgType":4,"FROMID":6,"TOID":8,"msg":"你好 8号","sendTime":"20231107 18:05:01"}


// 请求添加好友
{"msgType":5,"FROMID":6,"TOID":7,"msg":"hello 7号","sendTime":"20231107 18:05:01"}
// 添加好友关系
{"msgType":6,"U1":1,"U2":2}
// 删除好友关系
{"msgType":7,"FROMID":6,"TOID":7}
// 查找好友关系
{"msgType":8,"FROMID":6}


// 群聊消息
{"msgType":9,"FROMID":6,"GROUPID":8,"msg":"你好 8号","sendTime":"20231107 18:05:01"}
// 添加群成员
{"msgType":10,"FROMID":6,"GROUPID":7}
// 查询用户所有群
{"msgType":11,"FROMID":6}
// 创建群
{"msgType":12,"FROMID":6,"name":"cpp","description":"cpp group."}
// 根据群名称查找群聊
{"msgType":13,"name":"cpp"}

