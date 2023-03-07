//
// Created by 姚坤 on 2023/3/7.
//

//
// Created by 姚坤 on 2022/2/24.
//
#include <stdio.h>
#include <unistd.h>


#include <sys/types.h>
#include <signal.h>

// 1、信号的发送（linux系统中sig有64种信号）
// int kill(pid_t pid, int sig);
// int raise(int sig);                  // 发信号给自己 == kill(getpid(), sig)
// unsigned int alarm(unsigned int seconds); // 发送闹钟信号的函数（只会发一种信号SIGALRM）,默认操作是终止进程
// 该信号当一个定时器到时的时候发出
// 只能发送信号给当前进程，不能发送给其他进程
int main(){
    //printf("raise before");
    printf("raise before\n");           // 打印需要加上\n来刷新行缓存
    raise(9);                           // 调用的是系统函数_exit() 而不是库函数exit()
    printf("raise end\n");
    return 0;
}



// 2、信号的接收
// pause()/sleep/while(1)
// pause会使进程状态为S，相当睡眠，如果没有信号唤醒，将会一直处于睡眠状态

// 3、信号的处理
// sighandler_t signal(int signum, sighandler_t handler);

