/*
 * @Author: Han Liu
 * @Date: 2022-02-27 18:31:35
 * @LastEditTime: 2022-03-02 13:58:57
 * @LastEditors: Han Liu
 * @Description:
 * @FilePath: /JayChat/src/server/chatservice.cpp
 * 不积跬步 无以至千里
 */
#include "chatservice.hpp"

namespace JayChat
{

    /**
     * @description: 获取单例对象的接口函数
     * @param {*}
     * @return {ChatService *}
     */
    ChatService *ChatService::instance()
    {
        static ChatService service;
        return &service;
    }

    /**
     * @description: 构造函数
     * @param {*}
     * @return {ChatService}
     */
    ChatService::ChatService()
    {
        __msgHandlerMap.insert({LOGIN_MSG, std::bind(&ChatService::login, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
        __msgHandlerMap.insert({REG_MSG, std::bind(&ChatService::reg, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
        __msgHandlerMap.insert({ONE_CHAT_MSG, std::bind(&ChatService::oneChat, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
        __msgHandlerMap.insert({ADD_FRIEND_MSG, std::bind(&ChatService::addFriend, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
        __msgHandlerMap.insert({CREATE_GROUP_MSG, std::bind(&ChatService::createGroup, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
        __msgHandlerMap.insert({ADD_GROUP_MSG, std::bind(&ChatService::addGroup, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
        __msgHandlerMap.insert({GROUP_CHAT_MSG, std::bind(&ChatService::groupChat, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)});
    }

    /**
     * @description: 获取消息对应的处理器
     * @param {int} msgid
     * @return {std::function<void(const TcpConnectionPtr &, json &, Timestamp)>}
     */
    MsgHandler ChatService::getHandler(int msgid)
    {
        auto it = __msgHandlerMap.find(msgid);
        if (it == __msgHandlerMap.end())
        {
            return [=](const TcpConnectionPtr &conn, json &js, Timestamp time)
            {
                LOG_ERROR << "msgid:" << msgid << " can not find handler!";
            };
        }
        else
        {
            return __msgHandlerMap[msgid];
        }
    }

    /**
     * @description: 处理登录业务
     * @param {TcpConnectionPtr} &conn
     * @param {json} &js
     * @param {Timestamp} time
     * @return {*}
     */
    void ChatService::login(const TcpConnectionPtr &conn, json &js, Timestamp time)
    {
        int id = js["id"].get<int>();
        std::string password = js["password"];

        User user = __userModel.query(id);
        if (user.getId() != -1 && user.getPassword() == password)
        {
            if (user.getState() == "online")
            {
                // 该用户已经登录，不允许重复登录
                json response;
                response["msgid"] = LOGIN_MSG_ACK;
                response["errno"] = 2;
                response["errmsg"] = "该账号已经登录，请输入新账号";
                conn->send(response.dump());
            }
            else
            {
                // 登录成功
                {
                    std::lock_guard<std::mutex> lock(__connMutex);
                    __userConnctionMap.insert({id, conn}); // 记录用户连接
                }
                user.setState("online");
                __userModel.updateState(user); // 更新用户状态信息

                json response;
                response["msgid"] = LOGIN_MSG_ACK;
                response["errno"] = 0;
                response["id"] = user.getId();
                response["name"] = user.getName();

                // 查询该用户是否有离线消息
                std::vector<std::string> vec = __offlinemsgModel.query(id);
                if (!vec.empty())
                {
                    response["offlinemsg"] = vec;
                    __offlinemsgModel.remove(id);
                }

                // 查询该用户的好友信息并返回
                std::vector<User> userVec = __friendModel.query(id);
                if (!userVec.empty())
                {
                    std::vector<string> u_js_vec;
                    for (User user : userVec)
                    {
                        json u_js;
                        u_js["id"] = user.getId();
                        u_js["name"] = user.getName();
                        u_js["state"] = user.getState();
                        u_js_vec.push_back(u_js.dump());
                    }
                    response["friends"] = u_js_vec;
                }

                conn->send(response.dump());
            }
        }
        else
        {
            // 该用户不存在，登录失败
            json response;
            response["msgid"] = LOGIN_MSG_ACK;
            response["errno"] = 1;
            response["errmsg"] = "用户名或密码错误";
            conn->send(response.dump());
        }
    }

    /**
     * @description: 处理注册业务，提供name、password
     * @param {TcpConnectionPtr} &conn
     * @param {json} &js
     * @param {Timestamp} time
     * @return {*}
     */
    void ChatService::reg(const TcpConnectionPtr &conn, json &js, Timestamp time)
    {
        std::string name = js["name"];
        std::string password = js["password"];

        User user;
        user.setName(name);
        user.setPassword(password);
        bool flag = __userModel.insert(user);
        if (flag)
        {
            // 注册成功
            json response;
            response["msgid"] = REG_MSG_ACK;
            response["errno"] = 0;
            response["id"] = user.getId();
            conn->send(response.dump());
        }
        else
        {
            // 注册失败
            json response;
            response["msgid"] = REG_MSG_ACK;
            response["errno"] = 1;
            conn->send(response.dump());
        }
    }

    /**
     * @description: 处理客户端异常退出
     * @param {TcpConnectionPtr} &conn
     * @return {*}
     */
    void ChatService::clientCloseException(const TcpConnectionPtr &conn)
    {
        User user;
        {
            std::lock_guard<std::mutex> lock(__connMutex);
            for (auto it = __userConnctionMap.begin(); it != __userConnctionMap.end(); ++it)
            {
                if (it->second == conn)
                {
                    // 从map表中删除用户的连接信息
                    user.setId(it->first);
                    __userConnctionMap.erase(it);
                    break;
                }
            }
        }

        // 更新用户的状态信息
        if (user.getId() != -1)
        {
            user.setState("offline");
            __userModel.updateState(user);
        }
    }

    /**
     * @description: 一对一聊天业务
     * @param {TcpConnectionPtr} &conn
     * @param {json} &js
     * @param {Timestamp} time
     * @return {*}
     */
    void ChatService::oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time)
    {
        int toid = js["to"].get<int>();
        {
            std::lock_guard<std::mutex> lock(__connMutex);
            auto it = __userConnctionMap.find(toid);
            if (it != __userConnctionMap.end())
            {
                // toid在线，转发消息 服务器中转消息
                it->second->send(js.dump());
                return;
            }
        }

        // toid不在线，存储离线消息
        __offlinemsgModel.insert(toid, js.dump());
    }

    /**
     * @description: 服务器异常，业务重置方法
     * @param {*}
     * @return {*}
     */
    void ChatService::reset()
    {
        // 把online的用户，设置成offline
        __userModel.resetState();
    }

    /**
     * @description: 添加好友业务
     * @param {TcpConnectionPtr} &conn
     * @param {json} &js
     * @param {Timestamp} time
     * @return {*}
     */
    void ChatService::addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time)
    {
        int userid = js["id"].get<int>();
        int friendid = js["friendid"].get<int>();

        // 存储好友信息
        __friendModel.insert(userid, friendid);
    }

    /**
     * @description: 创建群组业务
     * @param {TcpConnectionPtr} &conn
     * @param {json} &js
     * @param {Timestamp} time
     * @return {*}
     */
    void ChatService::createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time)
    {
        int userid = js["id"].get<int>();
        std::string name = js["groupname"];
        std::string desc = js["groupdesc"];

        // 存储新创建的群组信息
        Group group(-1, name, desc);
        if (__groupModel.createGroup(group))
        {
            // 存储群组创建人信息
            __groupModel.addGroup(userid, group.getId(), "creator");
        }
    }

    /**
     * @description: 加入群组业务
     * @param {TcpConnectionPtr} &conn
     * @param {json} &js
     * @param {Timestamp} time
     * @return {*}
     */
    void ChatService::addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time)
    {
        int userid = js["id"].get<int>();
        int groupid = js["groupid"].get<int>();
        __groupModel.addGroup(userid, groupid, "normal");
    }

    /**
     * @description: 群组聊天业务
     * @param {TcpConnectionPtr} &conn
     * @param {json} &js
     * @param {Timestamp} time
     * @return {*}
     */
    void ChatService::groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time)
    {
        int userid = js["id"].get<int>();
        int groupid = js["groupid"].get<int>();
        std::vector<int> idVec = __groupModel.queryGroupUsers(userid, groupid);

        std::lock_guard<std::mutex> lock(__connMutex);
        for(int id : idVec)
        {
            auto it = __userConnctionMap.find(id);
            if (it != __userConnctionMap.end())
            {
                // 转发消息
                it->second->send(js.dump());
            }
            else
            {
                // 存储离线消息
                __offlinemsgModel.insert(id, js.dump());
            }
        }
    }

} // namespace JayChat