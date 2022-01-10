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

