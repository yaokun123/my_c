//
// Created by 姚坤 on 2023/3/7.
//

//
// Created by 姚坤 on 2022/2/25.
//

//// IPC通信包括共享内存、消息队列、信号灯
//// 查看IPC对象 ipcs -m           -q(消息队列)    -s(信号灯)
//// 删除IPC对象 ipcrm -m id
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


//// 共享内存的特点
// 1、共享内存创建后，一直存在于内核中，直到被删除或系统关闭
// 2、共享内存和管道不一样，读取后，内容仍在共享内存中。


// 共享内存的创建/打开
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/types.h>

// int shmget(key_t key, size_t size, int shmflg);
// key_t ftok(const char *pathname, int proj_id);
// key:IPC_PRIVATE 或 ftok返回值
// size:共享内存区大小
// shmflg:同open函数的权限位，也可以用8进制表示法
// 函数返回值：成功返回共享内存段标识符-ID-文件描述符。出错返回-1


//// 创建共享内存
// 如果使用IPC_PRIVATE创建共享内存，key的值始终都是0x00000000，而使用ftok()函数创建key不为0，参数不一样key也不一样
// 类似于无名管道与有名管道的区别，IPC_PRIVATE只能用于有亲缘关系的进程之间的通信，ftok()可用于无亲缘关系进程的通信

int main(){
    /*shmctl(65539, IPC_RMID, NULL);
    return 1;*/

    //int shmid = shmget(IPC_PRIVATE,128,0777);
    //int shmid = shmget(key,128,0777);


    int key = ftok("/tmp/demo.log",'a');
    if(key < 0){
        perror("");
        return -1;
    }
    printf("create key success key=%X\n",key);
    // key = IPC_PRIVATE;
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
// 参数一：shmid，ID号
// 参数二：映射到的地址。可以自己指定映射的地址，NULL为系统自动完成的映射
// 参数三：SHM_RDONLY共享内存只读，默认是0表示共享内存可读写。
// 返回值类似与malloc


//// 将进程里的地址映射删除（用户空间地址）
int shmdt(const void *);


//// 删除共享内存对象
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
// 参数一：shmid，ID号
// 参数二：cmd IPC_STAT（获取对象属性）/IPC_SET（设置对象属性）/IPC_RMID（删除对象）
// 参数三：指定IPC_STAT/IPC_SET时用于保存/设置属性






//
// Created by 姚坤 on 2022/3/1.
//

//// mmap()函数的主要用途有三个：

// 1、将一个普通文件映射到内存中，通常在需要对文件进行频繁读写时使用，这样用内存读写取代I/O读写，以获得较高的性能；
// 2、将特殊文件进行匿名内存映射，可以为关联进程提供共享内存空间
// 3、为无关联的进程提供共享内存空间，一般也是将一个普通文件映射到内存中

#include <sys/mman.h>
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

// 参数一：指向欲映射的内存起始地址，通常设为 NULL，代表让系统自动选定地址，映射成功后返回该地址
// 参数二：代表将文件中多大的部分映射到内存
// 参数三：映射区域的保护方式。可以为以下几种方式的组合
// PROT_EXEC       映射区域可被执行
// PROT_READ       映射区域可被读取
// PROT_WRITE      映射区域可被写入
// PROT_NONE       映射区域不能存取
// 参数四：影响映射区域的各种特性。在调用mmap()时必须要指定MAP_SHARED 或MAP_PRIVATE。
// MAP_FIXED                如果参数start所指的地址无法成功建立映射时，则放弃映射，不对地址做修正。通常不鼓励用此旗标。
// MAP_SHARED          对映射区域的写入数据会复制回文件内，而且允许其他映射该文件的进程共享
// MAP_PRIVATE            对映射区域的写入操作会产生一个映射文件的复制，即私人的“写入时复制”（copy on write）对此区域作的任何修改都不会写回原来的文件内容。
// MAP_ANONYMOUS  建立匿名映射。此时会忽略参数fd，不涉及文件，而且映射区域无法和其他进程共享。
// MAP_DENYWRITE   只允许对映射区域的写入操作，其他对文件直接写入的操作将会被拒绝。
// MAP_LOCKED          将映射区域锁定住，这表示该区域不会被置换（swap）。
// 参数五：要映射到内存中的文件描述符。如果使用匿名内存映射时，即flags中设置了MAP_ANONYMOUS，fd设为-1。
// 有些系统不支持匿名内存映射，则可以使用fopen打开/dev/zero文件，然后对该文件进行映射，可以同样达到匿名内存映射的效果。
// 参数六：文件映射的偏移量，通常设置为0，代表从文件最前方开始对应，offset必须是分页大小的整数倍。
