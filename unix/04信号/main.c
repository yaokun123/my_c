//
// Created by 姚坤 on 2023/3/3.
//

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
void test(int no){
    printf("recv %d\n", no);
}
int main(){
    signal(SIGUSR1, test);

    int mod = 30;
    sleep(mod);
    /*while (1){
        int i = sleep(mod);
        if(errno == EINTR){
            mod = i;
            printf("剩余 %d s\n", mod);
            continue;
        }else{
            break;
        }
    }*/
}