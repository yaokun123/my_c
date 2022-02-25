//
// Created by 姚坤 on 2022/2/25.
//

//// IPC通信包括共享内存、消息队列、信号灯
//// 查看IPC对象 ipcs -m           -q(消息队列)    -s(信号灯)
//// s删除IPC对象 ipcrm -m id
// 1、打开或创建IPC通道 -> open
// Msg_get（消息队列）
// Shm_get（共享内存）
// Sem_get（信号灯）


// 2、-> read/write
// msgsnd msgrecv
// shmat shmdt
// semop


// 3、close
// msgctrl
// shmctrl
// semctrl


// 共享内存的创建/打开
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/types.h>

int shmget(key_t key, size_t size, int shmflg);
key_t ftok(const char *pathname, int proj_id);
// key:IPC_PRIVATE 或 ftok返回值
// size:共享内存区大小
// shmflg:同open函数的权限位，也可以用8进制表示法
// 函数返回值：成功返回共享内存段标识符-ID-文件描述符。出错返回-1


//// 创建共享内存
// 如果使用IPC_PRIVATE创建共享内存，key的值始终都是0x00000000，而使用ftok()函数创建key不为0，参数不一样key也不一样
// 类似于无名管道与有名管道的区别，IPC_PRIVATE只能用于有亲缘关系的进程之间的通信，ftok()可用于无亲缘关系进程的通信

int main(){
    //int shmid = shmget(IPC_PRIVATE,128,0777);
    //int shmid = shmget(key,128,0777);


    int key = ftok("./a.c",'a');
    if(key < 0){
        printf("create key failure\n");
    }
    printf("create key success key=%X\n",key);
    int shmid = shmget(key,128,IPC_CREAT | 0777);

    if(shmid < 0){
        printf("create share memory failure\n");
        return -1;
    }
    printf("create share memory success shmid=%d\n",shmid);
    return 0;
}


//// shmat将共享内存映射到用户空间中，这样在用户空间即可操作共享内存不用每次操作都陷入内核空间
//// 能不能用read,write呢？
//// 为了方便用户空间对共享内存的操作，使用地址映射的方式
void *shmat(int shmid, const void *shmaddr, int shmflg);
// shmid，ID号
// 映射到的地址。可以自己指定映射的地址，NULL为系统自动完成的映射
// 返回值类似与malloc
