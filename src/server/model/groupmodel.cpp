/*
 * @Author: Han Liu
 * @Date: 2022-03-01 19:19:45
 * @LastEditTime: 2022-03-02 15:08:32
 * @LastEditors: Han Liu
 * @Description:
 * @FilePath: /JayChat/src/server/model/groupmodel.cpp
 * 不积跬步 无以至千里
 */
#include "groupmodel.hpp"

namespace JayChat
{

    /**
     * @description: 创建群组
     * @param {Group} &group
     * @return {bool}
     */
    bool GroupModel::createGroup(Group &group)
    {
        // 组装sql语句
        char sql[1024] = {0};
        sprintf(sql, "INSERT INTO allgroup(groupname, groupdesc) values('%s', '%s')", group.getName().c_str(), group.getDesc().c_str());

        MySQL mysql;
        if (mysql.connect())
        {
            if (mysql.update(sql))
            {
                group.setId(mysql_insert_id(mysql.getConnection()));
                return true;
            }
        }
        return false;
    }

    /**
     * @description: 加入群组
     * @param {int} userid
     * @param {int} groupid
     * @param {string} role
     * @return {*}
     */
    void GroupModel::addGroup(int userid, int groupid, std::string role)
    {
        // 组装sql语句
        char sql[1024] = {0};
        sprintf(sql, "INSERT INTO groupuser values(%d, %d, %s)", groupid, userid, role.c_str());

        MySQL mysql;
        if (mysql.connect())
        {
            mysql.update(sql);
        }
    }

    /**
     * @description: 联合groupuser和allgroup进行多表联合查询，查询userid所在的所有群组的信息
     * 再根据群组信息，查询属于该群组的所有用户的userid，并且和user表进行多表联合查询，查出用户的详细信息
     * @param {int} userid
     * @return {std::vector<Group>}
     */
    std::vector<Group> GroupModel::queryGroups(int userid)
    {
        //查询userid所在的所有群组的信息
        // 组装sql语句
        char sql[1024] = {0};
        sprintf(sql, "SELECT a.groupid, a.groupname, a.groupdesc FROM allgroup a INNER JOIN groupuser b ON a.id = b.groupid where b.userid = %d", userid);

        std::vector<Group> groupVec;
        MySQL mysql;
        if (mysql.connect())
        {
            MYSQL_RES *res = mysql.query(sql);
            if (res != nullptr)
            {
                MYSQL_ROW row;
                // 查询出userid的所有群组信息
                while ((row = mysql_fetch_row(res)) != nullptr)
                {
                    Group group;
                    group.setId(atoi(row[0]));
                    group.setName(row[1]);
                    group.setDesc(row[2]);
                    groupVec.push_back(group);
                }
                mysql_free_result(res);
            }
        }

        // 查询群组的用户信息
        for (Group &group : groupVec)
        {
            // 组装sql语句
            sprintf(sql, "SELECT a.id, a.name, a.state, b.grouprole FROM user a INNER JOIN groupuser b ON a.id = b.userid where b.groupid = %d", group.getId());

            MYSQL_RES *res = mysql.query(sql);
            if (res != nullptr)
            {
                MYSQL_ROW row = mysql_fetch_row(res);
                if (row != nullptr)
                {
                    GroupUser user;
                    user.setId(atoi(row[0]));
                    user.setName(row[1]);
                    user.setState(row[2]);
                    user.setRole(row[3]);
                    group.getUsers().push_back(user);
                }
                mysql_free_result(res);
            }
        }
        return groupVec;
    }

    /**
     * @description: 根据指定的groupid查询群组用户id列表，除去userid自己，用于给群组其他成员发送群消息
     * @param {int} userid
     * @param {int} groupid
     * @return {std::vector<int>}
     */    
    std::vector<int> GroupModel::queryGroupUsers(int userid, int groupid)
    {
        // 组装sql语句
        char sql[1024] = {0};
        sprintf(sql, "SELECT userid FROM groupuser where groupid = %d and userid != %d", groupid, userid);

        std::vector<int> idVec;
        MySQL mysql;
        if (mysql.connect())
        {
            MYSQL_RES *res = mysql.query(sql);
            if (res != nullptr)
            {
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(res)) != nullptr)
                {
                    idVec.push_back(atoi(row[0]));
                }
                mysql_free_result(res);
            }
        }
        return idVec;
    }

} // namespace JayChat