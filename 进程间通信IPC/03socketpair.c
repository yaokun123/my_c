//
// Created by 姚坤 on 2023/3/7.
//

//
// Created by 姚坤 on 2022/2/23.
//



#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// int socketpair(int domain, int type, int protocol, int sv[2]);

// 这个方法可以创建一对关联的套接字 sv[2]，它是使用本机套接字实现的。
// domain：表示域，在 Linux 下通常取值为 AF_UNIX
// type：取值为 SOCK_STREAM 或 SOCK_DGRAM，它表示在套接字上使用的是 TCP 还是 UDP
// protocol：必须传递 0；
// sv[2]：是一个含有两个元素的整型数组，实际上就是两个套接字
// 当 socketpair 返回 0 时，sv[2] 这两个套接字创建成功，否则 sockpair 返回 -1 表示失败


//// 当 socketpair 执行成功时，sv[2] 这两个套接字具备下列关系：(双向通信)
// 向 sv[0] 套接字写入数据，将可以从 sv[1] 套接字中读取到刚写入的数据
// 向 sv[1] 套接字写入数据，也可以从 sv[0] 中读取到写入的数据
// 通常，在父、子进程通信前，会先调用 socketpair 方法创建这样一组套接字，在调用 fork 方法创建出子进程后，
// 将会在父进程中关闭 sv[1] 套接字，仅使用 sv[0] 套接字用于向子进程发送数据以及接收子进程发送来的数据
// 而在子进程中则关闭 sv[0] 套接字，仅使用 sv[1] 套接字既可以接收父进程发送来的数据，也可以向父进程发送数据

int main(){
    int socket_vector[2];
    int r = socketpair(AF_UNIX, SOCK_STREAM, 0, socket_vector);
    if(r == -1){
        perror("");
        exit(1);
    }
    printf("读：%d,写：%d\n", socket_vector[0], socket_vector[1]);

    int pid = fork();
    if(pid == 0){// child write
        close(socket_vector[0]);

        for (int i = 0; i < 10; ++i) {
            sleep(1);
            write(socket_vector[1], &i, sizeof(i));
        }
        close(socket_vector[1]);

    }else{// parent read
        close(socket_vector[1]);
        int num = 0;
        while (1){
            r = read(socket_vector[0],&num,sizeof(num));
            if(r <= 0){
                perror("");
                break;
            }
            printf("recv: %d\n", num);
        }
        close(socket_vector[0]);
        wait(NULL);
    }
    return 0;
}
