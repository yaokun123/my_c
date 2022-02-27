//
// Created by 姚坤 on 2022/1/29.
//
#include <pthread.h>

//// 概述
// 互斥锁把试图进入我们称之为临界区的所有其他线程都阻塞住。
// 读写锁分配规则如下：
// 1、只要没有线程持有某个给定的读写锁用于写，那么任意数目的线程可以持有该读写锁用于读。
// 2、仅当没有线程持有某个给定的读写锁用于读或用于写时，才能分配该读写锁用于写。


////  读写锁的初始化
// 读写锁的数据类型为pthread_rwlock_t
// 1、静态分配
pthread_rwlock_t rw_lock = PTHREAD_RWLOCK_INITIALIZER;

// 2、动态分配
pthread_rwlock_t lock;
pthread_rwlock_init(&lock,NULL);


//// 函数

// 1、获取一个读出锁，如果对应的读写锁已由某个写入者持有，那就阻塞
pthread_rwlock_rdlock(&rw_lock);
pthread_rwlock_tryrdlock(&rw_lock);     // 非阻塞

// 2、获取一个写入锁，如果对应的读写锁已由另一个写入者持有，或者已由一个或多个读出者持有，那就阻塞
pthread_rwlock_wrlock(&rw_lock);
pthread_rwlock_trywrlock(&rw_lock);     // 非阻塞

// 3、释放一个读出锁或写入锁
pthread_rwlock_unlock(&rw_lock);

// 4、当一个线程不再需要某个读写锁时
pthread_rwlock_destroy(&rw_lock);





















