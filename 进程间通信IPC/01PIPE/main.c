//
// Created by 姚坤 on 2022/1/27.
//

//// 无名管道(PIPE)
// 只能用于亲缘关系的进程（父子、兄弟），由他的机制决定，无名管道的管道文件在文件系统中不可见。


//// 使用方式
// 1、父进程调用pipe()函数创建无名管道，无名管道有读端、写端
// 2、用fork产生子进程，子进程自动继承父进程的描述符，也就是无名管道的读端、写端
// 3、这是一种半双工通信（单向通信），一条管道不能同时又进又出，想读就把写关了

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    //// 子进程写、父进程读
    // 读、写描述符
    // pipefd[0]    读端描述符，从管道文件读
    // pipefd[1]    写端描述符，从管道文件写
    int pipefd[2];

    // 创建无名管道
    int res = pipe(pipefd);
    if(res == -1){
        perror("pipe");
        exit(-1);
    }

    // 创建子进程
    int pid = fork();
    if(pid == 0){ // child

        close(pipefd[0]);           // 写的时候，要关闭读

        for (int j = 0; j < 10; ++j) {
            write(pipefd[1],&j, sizeof(j));     // 往管道文件里写
            usleep(100000);
        }

        close(pipefd[1]);           // 退出之前,顺便关了写描述符
        exit(0);
    }

    // parent
    printf("pid = %d\n",getpid());  // 打印一下父进程的id
    int num = 0;                    // 和子进程发送的数据类型保持一致

    close(pipefd[1]);               // 读的时候，要关闭写
    while (1){
        res = read(pipefd[0],&num,sizeof(num));             // 从管道文件读
        if(res <= 0){
            break;
        }
        printf("%d\n",num);
    }

    close(pipefd[0]);               // 退出之前,顺便关了写描述符
    wait(NULL);                     // 等待子进程退出,回收它的资源
    return 0;
}