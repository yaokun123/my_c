//
// Created by 姚坤 on 2022/1/27.
//

// 用于所有进程的通信，不局限父子、兄弟进程
// 有名管道在文件系统中是可见，虽然可见，但是是在内存当中

//// 使用方法
// 1、进程1创建一个有名管道文件，可以在文件系统中看到，然后和它通信的进程2打开这个文件即可通信
// 2、没有读写描述符，这里只有文件描述符，用它进行读或写
// 3、这里也是一个半双工通信

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){
    // 而进程2不需要创建管道文件, 打开进程1创建的并获取文件描述符、接着进行用描述符来写管道文件
    char buf[10] = {};

    // 直接打开管道文件 写
    int fd = open("/tmp/a.fifo",O_WRONLY);
    if(fd == -1){
        perror("open");
        exit(-1);
    }

    // 写管道
    while (1){
        printf("请输入：");
        fgets(buf, sizeof(buf), stdin);
        write(fd,buf,sizeof(buf));
    }
    close(fd);
    return 0;
}