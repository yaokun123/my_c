//
// Created by 姚坤 on 2023/3/7.
//

//
// Created by 姚坤 on 2022/1/27.
//

//// pipe兄弟通信

// 1、父进程创建读写描述符
// 2、fork两次后产生了两个子进程（互为兄弟进程），他们都继承父进程的读写描述符
// 3、在这里父进程不参与通信，因此父进程的读、写描述符都需要关闭掉
// 4、下面的代码,子1是写,所以关掉读 ; 子2是读,所以关掉写

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int pipefd[2];

    int res = pipe(pipefd);
    if(res <= -1){
        perror("pipe");
        exit(-1);
    }

    int pid = fork();
    if(pid == 0){// child 1，写
        close(pipefd[0]);
        for (int i = 0; i < 10; ++i) {
            write(pipefd[1],&i, sizeof(i));
            usleep(100000);
        }
        close(pipefd[1]);
        exit(-1);
    }

    pid = fork();
    if(pid == 0){// child 2，读
        close(pipefd[1]);
        int num = 0;
        while (1){
            res = read(pipefd[0],&num,sizeof(num));
            if(res <= 0){
                break;
            }
            printf("%d\n",num);
        }
        close(pipefd[0]);
        exit(-1);
    }

    // parent
    //父进程不通信,关闭读端和写端
    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);
    return 0;
}