/*
 * @Author: Han Liu
 * @Date: 2022-02-27 16:29:00
 * @LastEditTime: 2022-02-27 22:10:06
 * @LastEditors: Han Liu
 * @Description:
 * @FilePath: /JayChat/include/server/chatserver.hpp
 * 不积跬步 无以至千里
 */
#ifndef __CHATSERVER_H__
#define __CHATSERVER_H__

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Timestamp.h>
#include <functional>
#include <string>
#include "json.hpp"
#include "chatservice.hpp"

using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

namespace JayChat
{

    class ChatServer
    {
    public:
        ChatServer(EventLoop *loop, const InetAddress &listenaddr, const string &nameArg); // 构造函数（初始化聊天服务器对象）
        void start();                                                                      // 启动服务
    private:
        void onConnectionCallback(const TcpConnectionPtr &conn);                              // 连接相关信息的回调函数
        void onMessageCallback(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time); // 读写事件相关信息的回调函数

        TcpServer __server; // 组合muduo库，实现服务器功能的类的对象
        EventLoop *__loop;  // 指向事件循环对象的指针（epoll）
    };

} // namespace JayChat

#endif