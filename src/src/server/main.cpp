/*
 * @Author: Han Liu
 * @Date: 2022-02-27 17:06:35
 * @LastEditTime: 2022-02-28 19:05:39
 * @LastEditors: Han Liu
 * @Description: 
 * @FilePath: /JayChat/src/server/main.cpp
 * 不积跬步 无以至千里
 */
#include "chatserver.hpp"
#include "chatservice.hpp"
#include <iostream>
#include <signal.h>
using namespace JayChat;

void resethandler(int)
{
    ChatService::instance()->reset();
    exit(0);
}

int main()
{
    struct sigaction act;
    act.sa_handler = resethandler;
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT, &act, nullptr);
    
    signal(SIGINT, resethandler);

    EventLoop loop;
    InetAddress addr("0.0.0.0", 10000);
    ChatServer server(&loop, addr, "JayChatServer");

    server.start();
    loop.loop();

    return 0;
}
