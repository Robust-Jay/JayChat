/*
 * @Author: Han Liu
 * @Date: 2022-02-27 18:26:11
 * @LastEditTime: 2022-03-02 16:32:34
 * @LastEditors: Han Liu
 * @Description: server和client的公共文件
 * @FilePath: /JayChat/include/public.hpp
 * 不积跬步 无以至千里
 */
#ifndef __PUBLIC_H
#define __PUBLIC_H

namespace JayChat
{

    enum EnMsgType
    {
        LOGIN_MSG = 1,  // 登录消息
        LOGIN_MSG_ACK,  // 登录响应消息
        LOGOUT_MSG,     // 注销消息
        REG_MSG,        // 注册消息
        REG_MSG_ACK,    // 注册响应消息
        ONE_CHAT_MSG,   // 一对一聊天消息
        ADD_FRIEND_MSG, // 添加好友信息

        CREATE_GROUP_MSG, // 创建群组消息
        ADD_GROUP_MSG,    // 加入群组消息
        GROUP_CHAT_MSG,   // 群聊天消息

    };

} // namespace JayChat

#endif