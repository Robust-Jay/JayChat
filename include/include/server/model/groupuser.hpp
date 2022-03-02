/*
 * @Author: Han Liu
 * @Date: 2022-03-01 18:52:24
 * @LastEditTime: 2022-03-01 19:00:37
 * @LastEditors: Han Liu
 * @Description: 群组用户，多了一个role角色信息，从User类直接继承，复用User的其它信息
 * @FilePath: /JayChat/include/server/model/groupuser.hpp
 * 不积跬步 无以至千里
 */
#ifndef __GROUPUSER_H
#define __GROUPUSER_H

#include "user.hpp"

namespace JayChat
{

    class GroupUser : public User
    {
    public:
        void setRole(std::string role) { __role = role; }
        std::string getRole() { return __role; }

    private:
        std::string __role; // 角色：管理员还是普通用户
    };

} // namespace JayChat

#endif