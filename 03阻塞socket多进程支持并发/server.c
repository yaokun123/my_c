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
    socketfd = socket(PF_INET, SOCK_STREAM, 0);
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
    // 内核要维护两个队列：已完成连接队列、未完成连接队列
    if(listen(socketfd, SOMAXCONN) == -1){
        perror("listen fail\n");
        exit(0);
    }

    while (1){
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

        int pid = fork();
        if(pid == 0){// 子进程
            close(socketfd);// 子进程不需要监听套接字，关闭从父进程继承过来的被动套接字

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
            exit(0);
        }else if(pid > 0){// 父进程
            close(clientfd);// 父进程也不需要clientfd
        }else{// 出错
            close(clientfd);
            close(socketfd);
            exit(0);
        }
    }


    return 0;
}