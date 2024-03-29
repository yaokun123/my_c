//
// Created by 姚坤 on 2022/1/9.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    // 1、创建服务端socket
    int socketfd;
    socketfd = socket(PF_INET, SOCK_STREAM, 0);// PF_INET = AF_INET
    //// 1、socket函数的family常值
    // PF_INET = AF_INET        ipv4协议
    // PF_INET6 = AF_INET6      ipv6协议
    // PF_LOCAL = AF_LOCAL      unix域协议
    // PF_ROUTE = AF_ROUTE      路由套接字
    // PF_KEY = pseudo_AF_KEY   密钥套接字
    //// 2、socket函数的type常值
    // SOCK_STREAM              字节流套接字
    // SOCK_DGRAM               数据报套接字
    // SOCK_RAW                 有序分组套接字
    // SOCK_SEQPACKET           原始套接字
    //// 3、socket函数AF_INET或AF_INET6的protocol常值
    // IPPROTO_IP 0             TCP传输协议
    // IPPROTO_UDP 17           UDP传输协议
    // IPPROTO_SCTP 132         SCTP传输协议
    if(socketfd == -1){
        perror("create socket fail\n");
        exit(0);
    }

    // 设置套接字选项-地址复用（解决服务端挂掉客户端没有挂掉，服务端无法重启）
    int optval = 1;
    if(setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1){
        perror("setsockopt fail\n");
        exit(0);
    }

    // 设置非阻塞io
    //fcntl(socketfd, F_SETFL, O_NONBLOCK);


    // 设置tcp层心跳包（默认2h）。  on 是 1 表示打开 keepalive 选项，为 0 表示关闭，0 是默认值
    //int on = 1;
    //setsockopt(socketfd, SOL_SOCKET, SO_KEEPALIVE, &on , sizeof(on));

    // 2、绑定端口
    // sockaddr为通用的数据结构，sockaddr_in为具体的TCP/IP协议数据结构。大小相同可以强制转换
    struct sockaddr_in srvaddr;
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = htons(8001);
    srvaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(bind(socketfd, (struct sockaddr *)&srvaddr, sizeof(srvaddr)) == -1){
        perror("bind fail\n");
        exit(0);
    }

    //3、监听
    // 一旦调用了listen函数，这个套接字将会变成被动套接字（只能接受连接不能发送连接）
    if(listen(socketfd, SOMAXCONN) == -1){
        perror("listen fail\n");
        exit(0);
    }
    //// 本函数的第二个参数规定了内核应该为相应套接字排队的最大连接个数。backlog
    //// 为了理解其中的backlog参数，我们必须认识到内核为任何一个给定的监听套接字维护两个队列
    // 1、未完成连接队列，每个这样的SYN分节对应其中一项：已由某个客户发出并到达服务器，而服务器正在等待完成相应的TCP三次握手，这些套接字处于SYN_RCVD状态。
    // 2、已完成连接队列，每个已完成TCP三次握手过程的客户对应其中一项，这些套接字处于ESTABLISHED状态
    //// 两个队列之和不超过backlog

    //4、接受连接（后两个参数是接受对方的）
    struct sockaddr_in peeraddr;
    socklen_t peeraddrlen;
    peeraddrlen = sizeof(peeraddr);
    int clientfd = accept(socketfd, (struct sockaddr *)&peeraddr,&peeraddrlen);
    if(clientfd == -1){
        perror("accept fail\n");
        exit(0);
    }
    printf("client ip %s\n", inet_ntoa(peeraddr.sin_addr));
    printf("client port %d\n", ntohs(peeraddr.sin_port));

    // 5、读取接受到的数据
    char revbuf[1024] = {0};
    while (1){
        int ret = read(clientfd, revbuf, sizeof(revbuf));
        // 如果在读的过程中，对方已经关闭，返回0
        if(ret == 0){
            printf("client closed\n");
            break;
        } else if(ret < 0){
            perror("read fail\n");
            break;
        }else{
            printf("client data:");
            fputs(revbuf, stdout);
            // 6、写客户端
            write(clientfd, revbuf, ret);
        }
    }
    close(clientfd);
    close(socketfd);


    return 0;
}