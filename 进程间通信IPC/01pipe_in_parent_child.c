//
// Created by 姚坤 on 2023/3/7.
//

//
// Created by 姚坤 on 2022/1/27.
//

//// 匿名管道(PIPE)
// 只能用于亲缘关系的进程（父子、兄弟），由他的机制决定，无名管道的管道文件在文件系统中不可见。
// 内核会创建一个队列，管道是用环形队列实现的
// 读写都是会阻塞的，读的阻塞是发生在队列中无数据的情况，写的阻塞是发生在队列被写满的时候（写满的临界值待测试）

// 调用pipe函数时在内核中开辟一块缓冲区用于通信,它有一个读端，一个写端：pipefd[0]指向管道的读端，pipefd[1]指向管道的写端。
// 所以管道在用户程序看起来就像一个打开的文件,通过read(pipefd[0])或者write(pipefd[1])向这个文件读写数据，其实是在读写内核缓冲区。


//// 使用方式
// 1、父进程调用pipe()函数创建无名管道，无名管道有读端、写端
// 2、用fork产生子进程，子进程自动继承父进程的描述符，也就是无名管道的读端、写端
// 3、这是一种半双工通信（单向通信），一条管道不能同时又进又出，想读就把写关了
// 进程通过一个管道只能实现单向通信，如果想双向通信必须再重新创建一个管道或者使用sockpair才可以解决这类问题


//// 管道出现的四种特殊情况：
// 1、写端关闭，读端不关闭：那么管道中剩余的数据都被读取后,再次read会返回0,就像读到文件末尾一样。
// 2、读端关闭，写端不关闭：此时该进程会收到信号SIGPIPE，通常会导致进程异常终止
// 3、写端不关闭，但是也不写数据，读端不关闭：此时管道中剩余的数据都被读取之后再次read会被阻塞，直到管道中有数据可读了才重新读取数据并返回
// 4、读端不关闭，但是也不读取数据，写端不关闭：此时当写端被写满之后再次write会阻塞，直到管道中有空位置了才会写入数据并重新返回


//// 示例
// redis 在进行aof重写的时候主进程和子进程会使用pipe匿名管道通信，由于是单向通信，所以会创建出三个管道
// int fds[6] = {-1, -1, -1, -1, -1, -1};
// int j;
//
// if (pipe(fds) == -1) goto error; /* parent -> children data. */
// if (pipe(fds+2) == -1) goto error; /* children -> parent ack. */
// if (pipe(fds+4) == -1) goto error; /* children -> parent ack. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    //// 子进程写、父进程读
    // pipefd[0]    读端描述符，从管道文件读
    // pipefd[1]    写端描述符，从管道文件写
    int pipefd[2];                  // 读、写描述符

    // 创建无名管道
    int res = pipe(pipefd);
    if(res == -1){
        perror("pipe");
        exit(-1);
    }

    // 创建子进程
    int pid = fork();
    if(pid == 0){ // child write

        close(pipefd[0]);           // 写的时候，要关闭读

        for (int j = 0; j < 10; ++j) {
            write(pipefd[1],&j, sizeof(j));     // 往管道文件里写
            usleep(100000);
        }

        close(pipefd[1]);           // 退出之前,顺便关了写描述符
        exit(0);
    }

    // parent read
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