/*
 * @Author: Han Liu
 * @Date: 2022-02-28 12:01:12
 * @LastEditTime: 2022-02-28 12:12:51
 * @LastEditors: Han Liu
 * @Description:
 * @FilePath: /JayChat/src/server/user.cpp
 * 不积跬步 无以至千里
 */
#include "user.hpp"

namespace JayChat
{

    /**
     * @description: 构造函数
     * @param {int} id
     * @param {string} name
     * @param {string} password
     * @param {string} state
     * @return {*}
     */    
    User::User(int id, std::string name, std::string password, std::string state)
        : __id(id), __name(name), __password(password), __state(state)
    {
    }

    /**
     * @description: 获取用户id
     * @param {int} id
     * @return {*}
     */    
    void User::setId(int id)
    {
        __id = id;
    }

    /**
     * @description: 获取用户姓名
     * @param {string} name
     * @return {*}
     */    
    void User::setName(std::string name)
    {
        __name = name;
    }

    /**
     * @description: 获取用户密码
     * @param {string} password
     * @return {*}
     */    
    void User::setPassword(std::string password)
    {
        __password = password;
    }

    /**
     * @description: 获取用户状态
     * @param {string} state
     * @return {*}
     */    
    void User::setState(std::string state)
    {
        __state = state;
    }

    /**
     * @description: 设置用户id
     * @param {*}
     * @return {*}
     */    
    int User::getId()
    {
        return __id;
    }

    /**
     * @description: 设置用户姓名
     * @param {*}
     * @return {*}
     */    
    std::string User::getName()
    {
        return __name;
    }

    /**
     * @description: 设置用户密码
     * @param {*}
     * @return {*}
     */    
    std::string User::getPassword()
    {
        return __password;
    }

    /**
     * @description: 设置用户状态
     * @param {*}
     * @return {*}
     */    
    std::string User::getState()
    {
        return __state;
    }

} // JayChat