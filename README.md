# JayChat
基于muduo网络库的集群聊天服务器


.
├── CMakeLists.txt
├── include
│   ├── public.hpp
│   └── server
│       ├── chatserver.hpp
│       ├── chatservice.hpp
│       ├── db
│       │   └── db.hpp
│       └── model
│           ├── friendmodel.hpp
│           ├── group.hpp
│           ├── groupmodel.hpp
│           ├── groupuser.hpp
│           ├── offlinemsgmodel.hpp
│           ├── user.hpp
│           └── usermodel.hpp
├── LICENSE
├── README.md
├── src
│   ├── client
│   ├── CMakeLists.txt
│   └── server
│       ├── chatserver.cpp
│       ├── chatservice.cpp
│       ├── CMakeLists.txt
│       ├── db
│       │   └── db.cpp
│       ├── main.cpp
│       └── model
│           ├── friendmodel.cpp
│           ├── groupmodel.cpp
│           ├── offlinemsgmodel.cpp
│           ├── user.cpp
│           └── usermodel.cpp
└── thirdparty
    └── json.hpp