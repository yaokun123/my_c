//
// Created by 姚坤 on 2022/3/14.
//
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

//// 线程间有序性
// 导致线程乱序的原因是cpu的指令重排序(cpu对指令的优化)
// 乱序存在的条件as-if-serial：不影响单线程的最终一致性（在多线程的情况下容易造成bug）


bool volatile ready = false;         //// 注意线程的可见性问题
int num;
void * thread(void * arg) {
    while (!ready){

    }
    printf("%d", num);
    return NULL;
}


int main(){
    pthread_t pthread_1;

    if(pthread_create(&pthread_1, NULL, thread, NULL) != 0){
        printf("thread creation failed\n");
        exit(1);
    }

    sleep(2);

    num = 42;               //// 这两行可能会被cpu优化顺序，导致多线程的有序性问题
    ready = true;           //// 导致打印的不是42  而是 0

    pthread_join(pthread_1, NULL);

    return 0;
}
