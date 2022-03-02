<!--
 * @Author: Han Liu
 * @Date: 2022-03-01 19:52:50
 * @LastEditTime: 2022-03-02 22:16:10
 * @LastEditors: Han Liu
 * @Description: 
 * @FilePath: /JayChat/README.md
 * 不积跬步 无以至千里
-->
# JayChat
基于muduo网络库的集群聊天服务器

# nginx tcp loadbalance config
stream {
    upstream MyServer {
        server ip:port1 weight=1 max_fails=3 fail_timeout=30s;
        server ip:port2 weight=1 max_fails=3 fail_timeout=30s;
        server ip:port3 weight=1 max_fails=3 fail_timeout=30s;
    }

    server {
        proxy_connect_timeout 1s;
        #proxy_timeout 3s;
        listen 8000;
        proxy_pass MyServer;
        tcp_nodelay on;
    }
}