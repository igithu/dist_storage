#!/bin/sh
#
# chkconfig: 2345  80 50
# description: dist_client is for testing how to write service in Linux 
#              
# processname: dist_client
# 
# Source function library.
. /etc/rc.d/init.d/functions

ret=0

start() {
    # check fdb status
    echo "start dist_client"
    ./dist_client &
    ret=$?
} 

stop() {
    echo "stop dist_client" 
    kill -9 $(ps -ef | grep dist_client | grep -v grep | awk '{print $2}')
    ret=$?
} 

status() {
    local result
    echo "check status of dist_client..."
    result=$( ps -ef | grep -v dist_client | grep -v grep | wc -l )
    if [ $result -gt 0 ] ; then
        echo "dist_client is up"
        ret=0
    else
        echo "dist_client is down"
        ret=1
    fi
    echo "check status of dist_client...done."
} 

# See how we were called.
case "$1" in
  start)
        start
        ;;
  stop)
        stop
        ;;
  status)
        status 
        ;;
  restart)
        stop
        start
        ;;
  *)
        echo $"Usage: $0 {start|stop|status}"
        exit 1
esac

exit $ret
