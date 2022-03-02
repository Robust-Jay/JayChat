/*
 * @Author: Han Liu
 * @Date: 2022-02-28 17:48:13
 * @LastEditTime: 2022-02-28 17:55:57
 * @LastEditors: Han Liu
 * @Description:  提供离线消息表的操作接口方法
 * @FilePath: /JayChat/include/server/offlinemsgmodel.hpp
 * 不积跬步 无以至千里
 */

#ifndef __OFFLINEMSGMODEL_H
#define __OFFLINEMSGMODEL_H

#include <string>
#include <vector>
#include "db.hpp"

namespace JayChat
{

    class OfflineMsgModel
    {
    public:
        void insert(int userid, std::string msg);   // 存储用户的离线消息
        void remove(int userid);                    // 删除用户的离线消息
        std::vector<std::string> query(int userid); // 查询用户的离线消息

    private:
    };

} // namespace JayChat

#endif