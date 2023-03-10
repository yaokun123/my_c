//
// Created by 姚坤 on 2023/3/10.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int sigaction(int signum, const struct sigaction *act,
              struct sigaction *oldact);
ssize_t read(int fd, void *buf, size_t count);

void signal_handler(int sig_no){
    printf("recv %d\n", sig_no);
}
int main(){
    printf("process id = %d\n", getpid());
    struct sigaction sc;
    sc.sa_handler = (void *)&signal_handler;
    sc.sa_flags = SA_RESTART;

    int res = sigaction(SIGUSR1, &sc, NULL);
    if(res == -1){
        perror("");
        return 1;
    }

//    char buf[1024]={0};
//    ssize_t rdl = read(STDIN_FILENO, &buf, sizeof(buf));
//    if(rdl == -1){
//        perror("");
//        return 2;
//    }
//    printf("read len=%d %s\n", rdl, buf);

    sleep(100);
    return 0;
}