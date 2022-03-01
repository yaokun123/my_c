//
// Created by 姚坤 on 2022/3/1.
//

///// 信号量
// 信号量是一种特殊变量，只取正数值，并且程序对其的访问都是原子操作

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


//// 1、创建/获取信号量
int semget(key_t key, int nsems, int semflg);
// 参数一：key和信号量关联的key值,key:IPC_PRIVATE 或 ftok返回值
// 参数二：用于指定需要的信号量的数量（不是信号量的初始值），它几乎总是取1（信号量集中信号量的个数(信号量集的长度)）
// 参数三：同open函数的权限位，也可以用8进制表示法
// 返回值：该函数成功时返回信号量的标识符，失败返回-1
// 如果使用IPC_PRIVATE创建信号量，key的值始终都是0x00000000，而使用ftok()函数创建key不为0，参数不一样key也不一样
// 类似于无名管道与有名管道的区别，IPC_PRIVATE只能用于有亲缘关系的进程之间的通信，ftok()可用于无亲缘关系进程的通信


//// 2、改变信号量的值（设置信号量集中信号量的初始计数）
// 参数一：信号量标识符
// 参数二：结构体数组
// 参数三：表明了数组的中有几个结构
struct sembuf {
    short sem_num;              // 信号量编号。除非你要使用一组信号量，否则它的取值一般为0。

    short sem_op;               // 为信号量再一次操作中需要改变的数值。通常只会用到两个：P操作-1，V操作+1。
                                // 当然，你也可以用一个非1的数值改变信号量。

    short sem_flg;              // 通常被设置为SEM_UNDO。它会让系统跟踪当前进程对这个信号量的修改情况，
                                // 如果这个进程在没有释放信号量的情况下终止，则操作系统将会自动释放该进程持有的信号量。
                                // 所以如果你对信号量没有特殊要求，请一定将sem_flg设置成SEM_UNDO。
};
int semop(int semid, struct sembuf *sops, unsigned nsops);


//// 3、控制信号量信息，在这里主要是用于信号量的初始化和删除。
int semctl(int semid, int semnum, int cmd, ...);
// 参数一：信号量标识符
// 参数二：信号量编号，只有一个信号量时取值为0，只有要用到成组的信号量时才会用它
// 参数三：要采取的行动SETVAL/IPC_RMID
// 参数：
// 返回值：成功返回0，失败返回-1

int main(){
    //创建一个二进制信号量
    int sem_id = semget(IPC_PRIVATE,1,0777);


    return 0;
}