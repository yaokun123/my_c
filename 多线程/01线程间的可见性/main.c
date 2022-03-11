//
// Created by 姚坤 on 2022/3/11.
//

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

// bool flag = true;
bool volatile flag = true;     // 使用volatile解决线程可见性问题


void * thread(void * arg) {
    pthread_t newthid;

    newthid = pthread_self();
    printf("this is a child thread, thread ID = %d\n", newthid);
    while (flag){       // 子进程与父进程共享全局变量flag
        //sleep(1);
        // 注意sleep会影响测试结果，猜测sleep被唤醒会更新寄存器缓存
        // 使用优化才能测试出效果gcc -O3 main.c -lpthread
    }
    printf("child thread exit");
    return NULL;
}

int main(argv){
    pthread_t thid;
    printf("main thread ,ID is %d\n",pthread_self());

    // int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
    // 参数一：是一个指针，线程创建成功时，用以返回创建的线程ID
    // 参数二：指定线程属性，NULL表示使用默认属性
    // 参数三：函数指针，指向线程创建后要调用的函数。这个被线程调用的函数也称为线程函数。
    // 参数四：该参数指向传递给线程函数的参数
    if(pthread_create(&thid, NULL, thread, NULL) != 0){
        printf("thread creation failed\n");
        exit(1);
    }
    printf("main child thread %d\n", thid);


    // 父进程如果不做任何操作直接退出，会导致子进程未启动或退出
    // int pthread_join(pthread_t thread, void **retval);
    // 参数一：等待退出线程的线程号
    // 参数二：退出线程的返回值
    sleep(5);
    flag = false;
    pthread_join(thid, NULL);
    return 0;
}
