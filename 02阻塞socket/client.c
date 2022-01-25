//
// Created by 姚坤 on 2022/1/9.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


int main(){
    // 1、创建socket
    int socketfd;
    socketfd = socket(PF_INET, SOCK_STREAM, 0);
    if(socketfd == -1){
        perror("create socket fail\n");
        exit(0);
    }

    // 2、连接服务端
    struct sockaddr_in srvaddr;
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(8001);
    srvaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(socketfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr));
    //// 客户在调用函数connect前不必非得调用bind函数，因为如果需要的话，内核会确定源IP地址，并选择一个临时端口作为源端口


    /*int keepAlive = 1; // 开启keepalive属性
    int keepIdle = 60; // 如该连接在60秒内没有任何数据往来,则进行探测
    int keepInterval = 5; // 探测时发包的时间间隔为5 秒
    int keepCount = 3; // 探测尝试的次数.如果第1次探测包就收到响应了,则后2次的不再发.
    setsockopt(socketfd, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepAlive, sizeof(keepAlive));
    setsockopt(socketfd, SOL_TCP, TCP_KEEPIDLE, (void*)&keepIdle, sizeof(keepIdle));
    setsockopt(socketfd, SOL_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
    setsockopt(socketfd, SOL_TCP, TCP_KEEPCNT, (void *)&keepCount, sizeof(keepCount));

    struct tcp_info info;
    int len=sizeof(info);
    getsockopt(socketfd, IPPROTO_TCP, TCP_INFO, &info, (socklen_t *)&len);
    // 则说明未断开  else 断开
    if((info.tcpi_state==TCP_ESTABLISHED))*/

    // 3、收发数据
    char revbuf[1024] = {0};
    char sendbuf[1024] = {0};
    while (fgets(sendbuf,sizeof(sendbuf),stdin) != NULL){
        write(socketfd, sendbuf, strlen(sendbuf));
        read(socketfd, revbuf, sizeof(revbuf));
        fputs(revbuf, stdout);


        memset(revbuf,0,sizeof(revbuf));
        memset(sendbuf,0,sizeof(sendbuf));
    }
    close(socketfd);

    return 0;
}

