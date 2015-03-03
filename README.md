# dist_storage
分布式存储引擎，主要涵盖实现 RPC，一致性Hash，master-slave-client架构，心跳机制等。 数据迁移，数据副本容错等讲在本阶段后继续增加

总体说明：
  1.rpc通信：采用libevrpc
  2.一致性hash：仿照memcache原理下的ketama hash算法
  3.现阶段采用master-slave-client架构，slave：负责数据存储，master：记录更新slaves状态信息，client：按照一致性hash直接与slave通信，同时周期从master获取信息

编译说明：
  该项目使用gcc/g++编译，工具为automake，所以编译前需要安装好automake等编译工具，另外要下载third-64，pub_util两目录下的代码，并将这两个目录放在与本想项目顶层目录平行位置下才能顺利编译，最后是执行顶层目录下build.sh 若编译所有项目请执行build.sh all
  最后生成目录为dist_storage,所有需要的生成文件均在该目录下

src下的代码说明

1.common
  内部还有日志，通用函数，以及md5等通用工具函数
  
2.config
  该目录主要的代码主要负责配置文件的加载和参数的设置
  
  
