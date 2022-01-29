//
// Created by 姚坤 on 2022/1/29.
//
//// 互斥锁用于上锁，条件变量用于等待
#include <pthread.h>

//// 互斥锁的初始化
// 1、静态分配
static pthread_mutex_t static_lock = PTHREAD_MUTEX_INITIALIZER;

// 2、动态分配
pthread_mutex_t dynamic_lock;
pthread_mutex_init(&dynamic_lock, NULL);

//// 互斥锁的上锁和解锁
// 1、阻塞式上锁，如果尝试给一个已由另外某个线程锁住的互斥锁上锁，那么pthread_mutex_lock将阻塞到该互斥锁解锁为止。
pthread_mutex_lock();

// 2、非阻塞式上锁，如果尝试给一个已由另外某个线程锁住的互斥锁上锁，则返回一个EBUSY错误。
pthread_mutex_trylock();

// 3、
pthread_mutex_unlock();


// 条件变量的类型是pthread_cond_t
// 每个条件变量总是有一个互斥锁与之关联，我们调用pthread_cond_wait等待某个条件为真时，还会指定其条件变量的地址和所关联的互斥锁的地址。


// 1、
struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} my_lock = {
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_COND_INITIALIZER
};
pthread_cond_wait(&my_lock.cond,&my_lock.mutex);//// 每个条件变量总是有一个互斥锁与之关联
// pthread_cond_wait 会原子地执行2个动作
// 给互斥锁&my_lock.mutex解锁
// 把调用线程投入睡眠，直到另外某个线程就本条件变量调用pthread_cond_signal, pthread_cond_wait返回前重新给&my_lock.mutex上锁

// 2、通常pthread_cond_signal只唤醒等待在相应条件变量上的一个线程。
pthread_cond_signal(&my_lock.cond);

// 3、唤醒阻塞在相应条件变量上的所有线程
pthread_cond_broadcast();

// 4、
pthread_cond_timedwait();























