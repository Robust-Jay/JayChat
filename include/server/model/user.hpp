/*
 * @Author: Han Liu
 * @Date: 2022-02-28 11:52:59
 * @LastEditTime: 2022-03-02 18:35:44
 * @LastEditors: Han Liu
 * @Description: User表的ORM类
 * @FilePath: /JayChat/include/server/model/user.hpp
 * 不积跬步 无以至千里
 */
#ifndef __USER_H
#define __USER_H

#include <string>

namespace JayChat
{

    class User
    {
    public:
        User(int id = -1, std::string name = "", std::string password = "", std::string state = "offline")
            : __id(id), __name(name), __password(password), __state(state) {}
        void setId(int id) { __id = id; }
        void setName(std::string name) { __name = name; }
        void setPassword(std::string password) { __password = password; }
        void setState(std::string state) { __state = state; }

        int getId() { return __id; }
        std::string getName() { return __name; }
        std::string getPassword() { return __password; }
        std::string getState() { return __state; }

    protected:
        int __id;
        std::string __name;
        std::string __password;
        std::string __state;
    };

} // namespace JayChat

#endif