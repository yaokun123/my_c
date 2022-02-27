//
// Created by 姚坤 on 2022/2/27.
//

//// 消息队列
// 消息队列在内核中以链式队列的形式存在，每条消息都可以不一样
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

//// 1、创建/打开消息队列
int msgget(key_t key, int msgflg);
// 参数一：key和消息队列关联的key值,key:IPC_PRIVATE 或 ftok返回值
// 参数二：消息队列的访问权限
// 返回值：成功返回消息队列ID，失败返回-1
// 如果使用IPC_PRIVATE创建共享内存，key的值始终都是0x00000000，而使用ftok()函数创建key不为0，参数不一样key也不一样
// 类似于无名管道与有名管道的区别，IPC_PRIVATE只能用于有亲缘关系的进程之间的通信，ftok()可用于无亲缘关系进程的通信
int main(){
    int msgid = msgget(IPC_PRIVATE,077);
    if(msgid < 0){
        printf("create message queue failure\n");
        return -1;
    }
    printf("create message queue success msgid=%d\n",msgid);
    return 0;
}


//// 2、删除消息队列
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
// 参数一：消息队列的ID
// 参数二：IPC_STAT/IPC_SET/IPC_RMID
// 参数三：消息队列缓冲区

//// 3、发送/接受消息队列
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
// msgflg：IPC_NOWAIT消息没有发送完成函数也会立即返回。
//         0直到发送完成函数才会返回

ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,
               int msgflg);

