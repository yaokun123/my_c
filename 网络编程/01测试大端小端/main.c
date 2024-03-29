//
// Created by 姚坤 on 2022/1/8.
//
#include <stdio.h>
#include <arpa/inet.h>

/**
 * 大端：低字节放在高位（IBM、网络字节序）
 * 小端：低字节放在低位（X86、）
 *
 */
void main(){
                            // 大端        0    1    2    3
    unsigned int data = 0x12345678;   // 0x12 0x34 0x56 0x78
                            // 小端        3    2   1     0

    char *p = &data;
    printf("%x %x %x %x\n", p[0], p[1], p[2], p[3]);

    if(p[0] == 0x78){
        printf("小端\n");
    }else{
        printf("大端\n");
    }

    printf("将主机字节序转换为网络字节序\n");
    unsigned int net_data = htonl(data);
    p = &net_data;
    printf("%x %x %x %x\n", p[0], p[1], p[2], p[3]);

    if(p[0] == 0x78){
        printf("小端\n");
    }else{
        printf("大端\n");
    }
}
////   字节序转换函数
//     #include <arpa/inet.h>
//
//     uint32_t
//     htonl(uint32_t hostlong);
//
//     uint16_t
//     htons(uint16_t hostshort);
//
//     uint32_t
//     ntohl(uint32_t netlong);
//
//     uint16_t
//     ntohs(uint16_t netshort);

//// 地址转换函数（点分IP char *   <->   32bit）
//     #include <arpa/inet.h>
//
//     in_addr_t
//     inet_addr(const char *cp);//如今inet_addr已被废除，新的代码应该该用inet_aton

//
//     int
//     inet_aton(const char *cp, struct in_addr *pin);

//
//     char *
//     inet_ntoa(struct in_addr in);


//// 新函数
// int inet_pton(int af, const char *src, void *dst);
// af:AF_INET|AF_INET6


//const char *inet_ntop(int af, const void *src,char *dst, socklen_t size);
// af:AF_INET|AF_INET6