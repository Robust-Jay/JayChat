# JayChat
基于muduo网络库的集群聊天服务器

### Requirements
1. muduo (依赖boost)：网络库
2. json (位于thirdparty文件夹)：序列化和反序列化
3. mysql：存储项目数据（user、offlinemessage、friend、allgroup、groupuser）
4. redis：基于发布-订阅实现集群服务器之间的通信
5. nginx：负载均衡

### nginx负载均衡配置
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