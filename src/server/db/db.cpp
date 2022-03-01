/*
 * @Author: Han Liu
 * @Date: 2022-02-27 23:28:43
 * @LastEditTime: 2022-02-28 12:36:02
 * @LastEditors: Han Liu
 * @Description:
 * @FilePath: /JayChat/src/server/db/db.cpp
 * 不积跬步 无以至千里
 */
#include "db.hpp"

namespace JayChat
{

    /**
     * @description: 构造函数
     * @param {*}
     * @return {*}
     */
    MySQL::MySQL()
    {
        __conn = mysql_init(nullptr);
    }

    /**
     * @description: 析构函数
     * @param {*}
     * @return {*}
     */
    MySQL::~MySQL()
    {
        if (__conn != nullptr)
        {
            mysql_close(__conn);
        }
    }

    /**
     * @description: 连接数据库
     * @param {*}
     * @return {bool}
     */
    bool MySQL::connect()
    {
        MYSQL *p = mysql_real_connect(__conn, server.c_str(), user.c_str(), password.c_str(), dbname.c_str(), 3306, nullptr, 0);
        if (p != nullptr)
        {
            mysql_query(__conn, "set names gbk");
            LOG_INFO << "connect mysql success!";
        }
        else
        {
            LOG_INFO << "connect mysql fail!";
        }
        return p;
    }

    /**
     * @description: 更新操作
     * @param {string} sql
     * @return {bool}
     */
    bool MySQL::update(string sql)
    {
        if (mysql_query(__conn, sql.c_str()))
        {
            LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "更新失败!";
            return false;
        }
        return true;
    }

    /**
     * @description: 查询操作
     * @param {string} sql
     * @return {MYSQL_RES *}
     */
    MYSQL_RES *MySQL::query(string sql)
    {
        if (mysql_query(__conn, sql.c_str()))
        {
            LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "查询失败!";
            return nullptr;
        }
        return mysql_use_result(__conn);
    }

    /**
     * @description: 获取连接
     * @param {*}
     * @return {*}
     */    
    MYSQL *MySQL::getConnection()
    {
        return __conn;
    }

} // JayChat