/*
 * @Author: Han Liu
 * @Date: 2022-02-28 17:53:34
 * @LastEditTime: 2022-02-28 18:24:54
 * @LastEditors: Han Liu
 * @Description:
 * @FilePath: /JayChat/src/server/offlinemsgmodel.cpp
 * 不积跬步 无以至千里
 */
#include "offlinemsgmodel.hpp"

namespace JayChat
{

    /**
     * @description: 存储用户的离线消息
     * @param {int} userid
     * @param {string} msg
     * @return {*}
     */
    void OfflineMsgModel::insert(int userid, std::string msg)
    {
        // 组装sql语句
        char sql[1024] = {0};
        sprintf(sql, "INSERT INTO offlinemessage values(%d, '%s')", userid, msg.c_str());

        MySQL mysql;
        if (mysql.connect())
        {
            mysql.update(sql);
        }
    }

    /**
     * @description: 删除用户的离线消息
     * @param {int} userid
     * @return {*}
     */
    void OfflineMsgModel::remove(int userid)
    {
        // 组装sql语句
        char sql[1024] = {0};
        sprintf(sql, "DELETE FROM offlinemessage WHERE userid = %d", userid);

        MySQL mysql;
        if (mysql.connect())
        {
            mysql.update(sql);
        }
    }

    /**
     * @description: 查询用户的离线消息
     * @param {int} userid
     * @return {std::vector<std::string>}
     */
    std::vector<std::string> OfflineMsgModel::query(int userid)
    {
        // 组装sql语句
        char sql[1024] = {0};
        sprintf(sql, "SELECT message FROM offlinemessage WHERE userid = %d", userid);

        std::vector<std::string> vec;
        MySQL mysql;
        if (mysql.connect())
        {
            MYSQL_RES *res = mysql.query(sql);
            if (res != nullptr)
            {
                // 把userid用户的所有离线消息放入vec中返回
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(res)) != nullptr)
                {
                    vec.push_back(row[0]);
                }
                mysql_free_result(res);
                return vec;
            }
        }
        return vec;
    }

} // namespace JayChat
