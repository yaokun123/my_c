//
// Created by 姚坤 on 2023/3/3.
//

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/**
 * io fd
 * 不带buf的文件读写操作，建议一次操作4096 bytes
 * @return
 */

int main(){
    STDIN_FILENO;
    STDOUT_FILENO;
    STDERR_FILENO;

    // int open(const char *pathname, int flags);
    // int open(const char *pathname, int flags, mode_t mode);
    // int creat(const char *pathname, mode_t mode);
    // creat();
    int fd = open("/tmp/demo.log", O_RDWR|O_CREAT|O_TRUNC, S_IRWXU); // 2
    if(fd == -1){
        perror("");
        exit(1);
    }
    printf("文件描述符:%d\n", fd);


    // off_t lseek(int fd, off_t offset, int whence);
    off_t l = lseek(fd, 10, SEEK_END);
    printf("设置文件偏移量为:%lld\n", l);
    char * str = "hello world";

    // ssize_t write(int fildes, const void *buf, size_t nbyte);
    ssize_t wl = write(fd, str, strlen(str));
    printf("写入字节为:%ld\n", wl);

    // ssize_t read(int fd, void *buf, size_t count);
    char buf[4096];
    lseek(fd, 10, SEEK_SET);
    ssize_t rl = read(fd, buf, 100);
    printf("读取的数据为%d:%s\n", rl, buf);

    //int fcntl(int fildes, int cmd, ...);
    int fc = fcntl(fd, F_GETFL);
    if((fc & O_ACCMODE) == O_RDWR){
        printf("一致\n");
    }
    // printf("%X", fc & O_ACCMODE);

    close(fd);
    return 0;
}

