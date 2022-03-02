/*
 * @Author: Han Liu
 * @Date: 2022-03-01 19:01:52
 * @LastEditTime: 2022-03-01 19:09:25
 * @LastEditors: Han Liu
 * @Description:
 * @FilePath: /JayChat/include/server/model/group.hpp
 * 不积跬步 无以至千里
 */
#ifndef __GROUP_H
#define __GROUP_H

#include "groupuser.hpp"
#include <vector>

namespace JayChat
{

    class Group
    {
    public:
        Group(int id = -1, std::string name = "", std::string desc = "") : __id(id), __name(name), __desc(desc) {}
        void setId(int id) { __id = id; }
        void setName(std::string name) { __name = name; }
        void setDesc(std::string desc) { __desc = desc; }
        
        int getId() { return __id; }
        std::string getName() { return __name; }
        std::string getDesc() { return __desc; }
        std::vector<GroupUser> &getUsers() { return __users; }


    private:
        int __id;
        std::string __name;
        std::string __desc;
        std::vector<GroupUser> __users;
    };

} // namespace JayChat

#endif