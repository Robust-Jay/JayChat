/*
 * @Author: Han Liu
 * @Date: 2022-02-27 18:07:34
 * @LastEditTime: 2022-03-02 16:03:55
 * @LastEditors: Han Liu
 * @Description:
 * @FilePath: /JayChat/include/server/chatservice.hpp
 * 不积跬步 无以至千里
 */
#ifndef __CHATSERVICE_H
#define __CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <muduo/base/Logging.h>
#include <unordered_map>
#include <functional>
#include <mutex>
#include "json.hpp"
#include "public.hpp"
#include "usermodel.hpp"
#include "offlinemsgmodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"

using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;
using MsgHandler = std::function<void(const TcpConnectionPtr &, json &, Timestamp)>;

namespace JayChat
{

    class ChatService
    {
    public:
        static ChatService *instance(); // 获取单例对象的接口函数

        void login(const TcpConnectionPtr &conn, json &js, Timestamp time);       // 处理登录业务
        void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);         // 处理注册业务
        void logout(const TcpConnectionPtr &conn, json &js, Timestamp time);      // 处理注销业务
        void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);     // 一对一聊天业务
        void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);   // 添加好友业务
        void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time); // 创建群组业务
        void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);    // 加入群组业务
        void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);   // 群组聊天业务

        MsgHandler getHandler(int msgid);                        // 获取消息对应的处理器
        void clientCloseException(const TcpConnectionPtr &conn); // 处理客户端异常退出
        void reset();                                            // 服务器异常，业务重置方法
    private:
        std::unordered_map<int, MsgHandler> __msgHandlerMap;          // 存储消息id和其对应的业务处理方法
        std::unordered_map<int, TcpConnectionPtr> __userConnctionMap; // 存储在线用户的通信连接
        UserModel __userModel;                                        // 用户表数据操作类对象
        OfflineMsgModel __offlinemsgModel;                            // 离线消息表数据操作对象
        FriendModel __friendModel;                                    // 好友表数据操作对象
        GroupModel __groupModel;                                      // 群组表数据操作对象
        std::mutex __connMutex;                                       // 定义互斥锁，保证__userConnectionMap的线程安全

        ChatService();
    };

} // namespace JayChat

#endif