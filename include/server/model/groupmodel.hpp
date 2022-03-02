/*
 * @Author: Han Liu
 * @Date: 2022-03-01 19:09:58
 * @LastEditTime: 2022-03-02 14:59:47
 * @LastEditors: Han Liu
 * @Description:
 * @FilePath: /JayChat/include/server/model/groupmodel.hpp
 * 不积跬步 无以至千里
 */
#ifndef __GROUPMODEL_H
#define __GROUPMODEL_H

#include "group.hpp"
#include "db.hpp"

namespace JayChat
{

    class GroupModel
    {
    public:
        bool createGroup(Group &group);                            // 创建群组
        void addGroup(int userid, int groupid, std::string role);  // 加入群组
        std::vector<Group> queryGroups(int userid);                // 查询用户所在群组信息
        std::vector<int> queryGroupUsers(int userid, int groupid); // 根据指定的groupid查询群组用户id列表，除userid自己，主要用户群聊业务给群组其他成员发送群消息
    };

} // namspace JayChat

#endif