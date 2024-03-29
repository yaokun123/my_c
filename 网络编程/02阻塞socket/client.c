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

    //// 1、如果服务端断开连接，此时服务端会发送FIN包，客户端收到之后回复一个ACK包，这就是TCP连接终止工作的前半部分。
    //// 然而问题是客户端进程阻塞在fgets调用上，等待从终端接收一行文本。此时服务端的状态为FIN_WAIT2、客户端的状态为CLOSE_WAIT
    //// 此时如果客户端再发送，客户TCP接着把数据发送给服务器。TCP允许这么做。
    //// 当服务器TCP接受到来自客户端的数据时，既然先前打开那个套接字的进程已经终止，于是响应一个RST。
    //// 然而客户进程看不到这个RST，因为他在调用write后立即调用了read，此时立即返回0，然后客户端结束。

    while (fgets(sendbuf,sizeof(sendbuf),stdin) != NULL){
        write(socketfd, sendbuf, strlen(sendbuf));
        int res = read(socketfd, revbuf, sizeof(revbuf));
        // 如果在读的过程中，对方已经关闭，返回0
        if(res == 0){
            break;
        }else if(res < 0){
            perror("read fail\n");
            break;
        }

        //// 2、要是客户端不理会read函数的返回值，反而写入更多的数据到服务器上，那又会发生什么？
        //// 当一个进程想某个已收到RST的套接字执行写操作时，内核向该进程发送一个SIGPIPE信号，该信号的默认行为是终止进程。
        fputs(revbuf, stdout);


        memset(revbuf,0,sizeof(revbuf));
        memset(sendbuf,0,sizeof(sendbuf));
    }
    close(socketfd);

    return 0;
}

