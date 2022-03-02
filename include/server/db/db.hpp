/*
 * @Author: Han Liu
 * @Date: 2022-02-27 23:21:01
 * @LastEditTime: 2022-03-02 18:44:28
 * @LastEditors: Han Liu
 * @Description: 数据库操作
 * @FilePath: /JayChat/include/server/db/db.hpp
 * 不积跬步 无以至千里
 */

#ifndef __DB_H
#define __DB_H

#include <muduo/base/Logging.h>
#include <mysql/mysql.h>
#include <string>

using namespace muduo;

namespace JayChat
{

    class MySQL
    {
    public:
        MySQL();
        ~MySQL();
        bool connect();               // 连接数据库
        bool update(string sql);      // 更新操作
        MYSQL_RES *query(string sql); // 查询操作
        MYSQL *getConnection();       // 获取连接

    private:
        MYSQL *__conn;
    };

} // namespace JayChat

#endif