/*
 * @Author: Han Liu
 * @Date: 2022-02-28 11:52:59
 * @LastEditTime: 2022-03-01 18:53:48
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
        User(int id = -1, std::string name = "", std::string password = "", std::string state = "offline");

        void setId(int id);
        void setName(std::string name);
        void setPassword(std::string password);
        void setState(std::string state);

        int getId();
        std::string getName();
        std::string getPassword();
        std::string getState();

    protected:
        int __id;
        std::string __name;
        std::string __password;
        std::string __state;
    };

} // namespace JayChat

#endif