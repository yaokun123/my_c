//
// Created by 姚坤 on 2023/3/3.
//
#include <stdio.h>
#include <wchar.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/**
 * io stream with buffer
 * 全缓冲、行缓冲（当流涉及到一个终端时，通常使用行缓冲）、无缓冲（标准错误流通常是不带缓冲的）
 * @return
 */
int main(){
    stdin;
    stdout;
    stderr;
    BUFSIZ;

    // 流的定向决定了读、写的字符是单字节还是多字节。当一个流最初被创建时，他并没有定向。
    // 如果在未定向的流上使用一个多字节的io函数，则将该流的定向设置未宽定向。
    // 如果在未定向的流上使用一个单字节的io函数，则将该流的定向设置未字节定向。
    // 只有两个函数可以改变流的定向 freopen()清除一个流的定向，fwide()设置流的定向
    // FILE *freopen(const char *path, const char *mode, FILE *stream);
    // int fwide(FILE *stream, int mode);


    // FILE *fopen(const char *path, const char *mode);
    // FILE *fdopen(int fd, const char *mode);
    // FILE *freopen(const char *path, const char *mode, FILE *stream);
    FILE * fp = fopen("/tmp/demo.log", "r");
    if(fp == NULL){
        perror("");
        exit(1);
    }

    int fd = fileno(fp);
    printf("文件描述符：%d\n", fd);


    // 清除文件出错标志、结束标志
    clearerr(fp);


    // 每次一个字符的IO    getc(fp);fgetc(fp);putc();fputc()
    // 每次一行的IO          gets();fgets();puts();fputs();
    // 直接IO
    char buf[1024];
    //fseek()
    fseeko(fp,10,SEEK_SET);
    fgets(buf, 5, fp);
    printf("读取的字符串为%d：%s\n",strlen(buf), buf);




    // int fclose(FILE *fp);
    fclose(fp);


    // 行缓冲
    printf("hello world\n");
    printf("hello world");fflush(NULL);
    printf("hello world");

    sleep(2);

    return 0;
}