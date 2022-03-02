/*
 * @Author: Han Liu
 * @Date: 2022-02-28 12:00:37
 * @LastEditTime: 2022-02-28 18:54:17
 * @LastEditors: Han Liu
 * @Description: User表的数据操作类
 * @FilePath: /JayChat/include/server/usermodel.hpp
 * 不积跬步 无以至千里
 */
#ifndef __USERMODEL_H
#define __USERMODEL_H

#include "user.hpp"

namespace JayChat
{

    class UserModel
    {
    public:
        bool insert(User &user);
        User query(int id);
        bool updateState(User user); // 更新用户状态
        void resetState();           // 重置用户状态信息

    private:
    };

} // namespace JayChats

#endif
