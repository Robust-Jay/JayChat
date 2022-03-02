/*
 * @Author: Han Liu
 * @Date: 2022-02-27 17:06:35
 * @LastEditTime: 2022-03-02 21:56:38
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

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "command invalid! example: ./JayChatServer 10000" << std::endl;
    }

    struct sigaction act;
    act.sa_handler = resethandler;
    sigemptyset(&act.sa_mask);
    sigaction(SIGINT, &act, nullptr);
    
    signal(SIGINT, resethandler);

    EventLoop loop;
    InetAddress addr(atoi(argv[1])); // TcpServer listening
    ChatServer server(&loop, addr, "JayChatServer");

    server.start();
    loop.loop();

    return 0;
}
