# JayChat
基于muduo网络库的集群聊天服务器

#### nginx负载均衡配置
```
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
```