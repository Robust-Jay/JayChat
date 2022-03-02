/*
 * @Author: Han Liu
 * @Date: 2022-02-27 16:45:51
 * @LastEditTime: 2022-02-28 15:46:12
 * @LastEditors: Han Liu
 * @Description:
 * @FilePath: /JayChat/src/server/chatserver.cpp
 * 不积跬步 无以至千里
 */
#include "chatserver.hpp"

namespace JayChat
{
    /**
     * @description: 构造函数（初始化聊天服务器对象）
     * @param {EventLoop} *loop
     * @param {InetAddress} &listenaddr
     * @param {string} &nameArg
     * @return {*}
     */
    ChatServer::ChatServer(EventLoop *loop, const InetAddress &listenaddr, const string &nameArg)
        : __server(loop, listenaddr, nameArg)
    {
        // 注册连接回调, typedef std::function<void (const TcpConnectionPtr&)> ConnectionCallback;
        __server.setConnectionCallback(std::bind(&ChatServer::onConnectionCallback, this, std::placeholders::_1));

        // 注册消息回调, typedef std::function<void (const TcpConnectionPtr&, Buffer*, Timestamp)> MessageCallback;
        __server.setMessageCallback(std::bind(&ChatServer::onMessageCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        // 设置线程数量
        __server.setThreadNum(4);
    }

    /**
     * @description: 启动服务
     * @param {*}
     * @return {*}
     */
    void ChatServer::start()
    {
        __server.start();
    }

    /**
     * @description: 连接回调
     * @param {TcpConnectionPtr} &conn
     * @return {*}
     */
    void ChatServer::onConnectionCallback(const TcpConnectionPtr &conn)
    {
        // 客户端断开连接
        if (!conn->connected())
        {
            ChatService::instance()->clientCloseException(conn);
            conn->shutdown();
        }
    }

    /**
     * @description: 消息回调
     * @param {TcpConnectionPtr} &conn
     * @param {Buffer} *buffer
     * @param {Timestamp} time
     * @return {*}
     */
    void ChatServer::onMessageCallback(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time)
    {
        std::string buf = buffer->retrieveAllAsString();
        json js = json::parse(buf); // 数据的反序列化
        // 目的：完全解耦网络模块的代码和业务模块的代码
        auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
        msgHandler(conn, js, time); // 回调消息绑定好的事件处理器，来执行相应的业务处理
    }

} // namespace JayChat