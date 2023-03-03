//
// Created by 姚坤 on 2023/3/3.
//

# include <stdio.h>
#include <sys/stat.h>

int main(){


    // ls -l
    // int stat(const char *restrict path, struct stat *restrict buf);
    // int fstat(int fildes, struct stat *buf);
    // int lstat(const char *restrict path, struct stat *restrict buf); // 当命名文件是一个符号连接时，返回连接的有关信息
    struct stat buf;
    stat("/tmp/demo.log", &buf);

    // 普通文件(-)、目录文件(d)、块特殊文件(b)、字符特殊文件(c)、FIFO(f)、套接字(s)、符号链接(l)
    if(S_ISREG(buf.st_mode)){
        printf("普通文件");
    }


    return 0;
}