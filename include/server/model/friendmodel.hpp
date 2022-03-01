/*
 * @Author: Han Liu
 * @Date: 2022-02-28 19:15:27
 * @LastEditTime: 2022-02-28 19:24:56
 * @LastEditors: Han Liu
 * @Description: 维护好友信息的操作接口方法
 * @FilePath: /JayChat/include/server/friendmodel.hpp
 * 不积跬步 无以至千里
 */

#ifndef __FRIENDMODEL_H
#define __FRIENDMODEL_H

#include <vector>
#include "user.hpp"
#include "db.hpp"

namespace JayChat
{

    class FriendModel
    {
    public:
        void insert(int userid, int frientid); // 添加好友关系
        std::vector<User> query(int userid);   // 查询好友列表

    private:
    };

} // namespace JayChat

#endif