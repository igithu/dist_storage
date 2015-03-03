# dist_storage
分布式存储引擎，主要涵盖实现 RPC，一致性Hash，master-slave-client架构，心跳机制等。 数据迁移，数据副本容错等讲在本阶段后继续增加

总体说明

    1.一致性hash：仿照memcache原理下的ketama hash算法
    2.现阶段采用master-slave-client架构，slave：负责数据存储，master：记录更新slaves状态信息，client：按照一致性hash直接与slave通信，同时周期从master获取信息

编译说明：

    该项目使用gcc/g++编译，工具为automake，所以编译前需要安装好automake等编译工具，另外要下载third-64，pub_util两目录下的代码，并将这两个目录放在与本想项目顶层目录平行位置下才能顺利编译，最后是执行顶层目录下build.sh 若编译所有项目请执行build.sh all
    最后生成目录为dist_storage,所有需要的生成文件均在该目录下

src下的代码说明

    1.common:内部还有日志，通用函数，以及md5等通用工具函数
    2.config:该目录主要的代码主要负责配置文件的加载和参数的设置
    3.rpc:公共的通信基础组件，主要负责分布式存储系统内部各个组件的之间的网络通信
    4.proto:该目录主要为protobuf文件以及对应生成的protobuf代码，主要定义了各个组件之间的通信协议，包括请求响应字段信息，rpc调用函数等
    5.name_server:分布式存储系统的master，现阶段主要实现：对各个data_server 状态监控以及记录，构建一致性hash表负载均衡使用，另外提供对外信息rpc接口调用。后面将实现：数据节点增加与挂机时的容错功能，副本容错数据生成，数据迁移计划制定，主备服务功能等
    6.data_server:分布式存储系统主要数据存储载体，现阶段包括实现：对外数据的读写rpc调用，内部leveldb的封装以及抽象存储接口，心跳信息功能等。后面将增加实现增加其他（除了leveldb之外）存储实体的接入，针对leveldb读性能不稳定增加缓存结构等功能
    7.dist_client:分布式存储系统的客户端访问，现阶段主要实现：从name_server定时更新信息（包括一致性hash表，存活节点列表等），一致性hash(ketamahash)的rpc调用访问。后面将实现shell操作，http server接入 多语言的支持(例如对Python，Java的支持)以及一些其他增强型功能
  
