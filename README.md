# dist_storage
分布式存储引擎，主要涵盖实现 RPC，一致性Hash，master-slave-client架构，心跳机制等 数据迁移，数据副本等尚未实现

rpc通信：采用libevrpc

一致性hash：仿照memcache原理下的ketama hash算法

现阶段采用master-slave-client架构，slave：负责数据存储，master：记录更新slaves状态信息，client：按照一致性hash直接与slave通信，同时周期从master获取信息
