/*
 * @Author: Han Liu
 * @Date: 2022-02-28 19:20:55
 * @LastEditTime: 2022-02-28 20:01:08
 * @LastEditors: Han Liu
 * @Description:
 * @FilePath: /JayChat/src/server/friendmodel.cpp
 * 不积跬步 无以至千里
 */
#include "friendmodel.hpp"

namespace JayChat
{

    /**
     * @description: 插入好友关系
     * @param {int} userid
     * @param {int} friendid
     * @return {*}
     */    
    void FriendModel::insert(int userid, int friendid)
    {
        // 组装sql语句
        char sql[1024] = {0};
        sprintf(sql, "INSERT INTO friend VALUES(%d, %d)", userid, friendid);

        MySQL mysql;
        if (mysql.connect())
        {
            mysql.update(sql);
        }
    }

    /**
     * @description: 返回用户好友列表
     * @param {int} userid
     * @return {std::vector<User>}
     */    
    std::vector<User> FriendModel::query(int userid)
    {
        // 组装sql语句
        char sql[1024] = {0};
        sprintf(sql, "SELECT a.id, a.name, a.state FROM user a INNER JOIN friend b on b.friendid = a.id where b.userid = %d", userid);

        std::vector<User> vec;
        MySQL mysql;
        if (mysql.connect())
        {
            MYSQL_RES *res = mysql.query(sql);
            if (res != nullptr)
            {
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(res)) != nullptr)
                {
                    User user;
                    user.setId(atoi(row[0]));
                    user.setName(row[1]);
                    user.setState(row[2]);
                    vec.push_back(user);
                }
                mysql_free_result(res);
                return vec;
            }
        }
        return vec;
    }

} // namespace JayChat