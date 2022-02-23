//
// Created by 姚坤 on 2022/1/27.
//

//// FIFO
// FIFO不同于管道之处在于它提供一个路径名与之关联，以FIFO的文件形式存储文件系统中。
// 命名管道是一个设备文件，因此即使进程与创建FIFO的进程不存在亲缘关系，只要可以访问该路径，就能够通过FIFO相互通信。
// 用于所有进程的通信，不局限父子、兄弟进程
// 有名管道在文件系统中是可见，虽然可见，但是是在内存当中

//// 使用方法
// 1、进程1创建一个有名管道文件，可以在文件系统中看到，然后和它通信的进程2打开这个文件即可通信
// 2、没有读写描述符，这里只有文件描述符，用它进行读或写
// 3、这里也是一个半双工通信

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    char buf[100] = {};

    // 1、创建管道文件
    int res = mkfifo("/tmp/a.fifo",0666);
    if(res == -1){
        perror("mkfifo");
        exit(-1);
    }

    // 打开管道文件 读
    int fd = open("/tmp/a.fifo",O_RDONLY);
    if(fd == -1){
        perror("open");
        exit(-1);
    }

    // 读管道
    while (1){
        res = read(fd,buf, sizeof(buf));
        if(res <= 0){
            break;
        }
        printf("buf = %s\n",buf);
    }
    close(fd);

    return 0;
}