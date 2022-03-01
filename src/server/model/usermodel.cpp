/*
 * @Author: Han Liu
 * @Date: 2022-02-28 12:19:22
 * @LastEditTime: 2022-02-28 18:56:21
 * @LastEditors: Han Liu
 * @Description:
 * @FilePath: /JayChat/src/server/usermodel.cpp
 * 不积跬步 无以至千里
 */
#include "usermodel.hpp"
#include "db.hpp"

namespace JayChat
{

    /**
     * @description: User表的增加方法
     * @param {User} &user
     * @return {bool}
     */
    bool UserModel::insert(User &user)
    {
        // 组装sql语句
        char sql[1024] = {0};
        sprintf(sql, "INSERT INTO user(name, password, state) VALUES('%s', '%s', '%s')",
                user.getName().c_str(), user.getPassword().c_str(), user.getState().c_str());

        MySQL __mysql;
        if (__mysql.connect())
        {
            if (__mysql.update(sql))
            {
                // 获取插入成功的用户数据生成的主键id
                user.setId(mysql_insert_id(__mysql.getConnection()));
                return true;
            }
        }
        return false;
    }

    /**
     * @description: 根据用户号码查询用户信息
     * @param {int} id
     * @return {User}
     */
    User UserModel::query(int id)
    {
        // 组装sql语句
        char sql[1024] = {0};
        sprintf(sql, "SELECT * FROM user where id = %d", id);

        MySQL mysql;
        if (mysql.connect())
        {
            MYSQL_RES *res = mysql.query(sql);
            if (res != nullptr)
            {
                MYSQL_ROW row = mysql_fetch_row(res);
                if (row != nullptr)
                {
                    User user;
                    user.setId(atoi(row[0]));
                    user.setName(row[1]);
                    user.setPassword(row[2]);
                    user.setState(row[3]);
                    mysql_free_result(res);
                    return user;
                }
            }
        }
        return User();
    }

    /**
     * @description: 更新用户状态信息
     * @param {User} user
     * @return {bool}
     */    
    bool UserModel::updateState(User user)
    {
        // 组装sql语句
        char sql[1024] = {0};
        sprintf(sql, "UPDATE user SET state = '%s' where id = %d", user.getState().c_str(), user.getId());
        MySQL mysql;
        if (mysql.connect())
        {
            if (mysql.update(sql))
            {
                return true;
            }
        }
        return false;
    }

    void UserModel::resetState()
    {
        // 组装sql语句
        char sql[1024] = "UPDATE user SET state = 'offline' where state = 'online'";
        MySQL mysql;
        if (mysql.connect())
        {
            mysql.update(sql);
        }
    }

} // namespace JayChat