
# include "register.h"
# include <stdio.h>

// 测试寄存器的
int main(){
    reg.rax = 0x1234abcd5678ff11;

    printf("eax: %08x\n", reg.eax);
    printf("ax: %04x\n", reg.ax);
    printf("ah: %02x\n", reg.ah);
    printf("al: %02x\n", reg.al);
    return 0;
}