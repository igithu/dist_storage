#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include "rpc/socket_util.h"

#define MAXCLINE 5
#define BUF_SIZE 200

using namespace std;
using namespace dist_storage;


int32_t fd[MAXCLINE];
int32_t conn_amount;

void ShowClient() {
    int32_t i;
    printf("client amount:%d\n",conn_amount);
    for(i = 0; i < MAXCLINE; ++i) {
        printf("[%d]:%d ", i, fd[i]);
    }
    printf("\n\n");
}


int main() {
    int32_t new_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    socklen_t sin_size;
    char buf[BUF_SIZE];
    int32_t yes = 1, ret, i;

    const char* addr = "127.0.0.1";
    const char* port = "9910";
    int32_t sock_fd = TcpListen(addr, port, AF_UNSPEC);

    if (sock_fd < 0) {
        printf("Listen failed!\n");
        printf("errno is %s\n", strerror(errno));
        return 0;
    }

    fd_set fdsr;
    int maxsock;
    struct timeval tv;

    conn_amount =0;
    sin_size = sizeof(client_addr);
    maxsock = sock_fd;
    string send_str;

    while(1) {
        FD_ZERO(&fdsr);
        FD_SET(sock_fd, &fdsr);
        tv.tv_sec = 30;
        tv.tv_usec =0;

        for(i = 0; i < MAXCLINE; ++i) {
          if (fd[i]!=0) {
              FD_SET(fd[i], &fdsr);
          }
        }

        ret = select(maxsock +1, &fdsr, NULL, NULL, &tv);
        if (ret <0) {
            perror("select error!\n");
            break;
        } else if(ret ==0) {
            printf("timeout \n");
            continue;
        }

        for (i = 0; i < conn_amount; ++i) {
            if(FD_ISSET(fd[i], &fdsr)) {
                string recv_msg_str;
                if (RecvMsg(fd[i], recv_msg_str) < 0) {
                    printf("recv msg failed!\n");
                    close(fd[i]);
                    FD_CLR(fd[i], &fdsr);
                    fd[i]=0;
                    conn_amount--;
                    continue;
                }
                printf("recv_msg_str is %s.\n", recv_msg_str.c_str());
                send_str = recv_msg_str;
                memset(&buf[ret],'\0', 1);
                printf("max connections arrive ,exit\n");
                if (SendMsg(new_fd, send_str) < 0) {
                    printf("send msg failed!\n");
                }
            }
        }

        if (FD_ISSET(sock_fd, &fdsr)) {
            new_fd = Accept(sock_fd, client_addr, sin_size);
            if (new_fd <= 0) {
                perror("accept error\n");
                continue;
            }
            if (conn_amount < MAXCLINE) {
              for (i = 0; i < MAXCLINE; ++i) {
                if (fd[i] == 0) {
                    fd[i] = new_fd;
                    break;
                }
              }
              conn_amount++;
              printf("new connection client[%d]%s:%d\n",conn_amount,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
              if (new_fd > maxsock) {
                  maxsock = new_fd;
              }
            } else {
                send(new_fd, "bye", 4, 0);
                close(new_fd);
                continue;
            }
        }
        ShowClient();
    }
    for (i = 0; i < MAXCLINE; ++i) {
        if (fd[i] != 0) {
            close(fd[i]);
        }
    }
    exit(0);
}
