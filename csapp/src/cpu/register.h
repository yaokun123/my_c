#include <stdint.h>

// 寄存器结构
typedef struct REG_STRUCT{
    union {
        struct {
            uint8_t al;
            uint8_t ah;
        };
        uint16_t ax;
        uint32_t eax;
        uint64_t rax; // 返回值
    };

    union {
        struct {
            uint8_t bl;
            uint8_t bh;
        };
        uint16_t bx;
        uint32_t ebx;
        uint64_t rbx; // 被调用者保存
    };

    union {
        uint64_t rcx; // 第4个参数
    };

    union {
        uint64_t rdx; // 第3个参数
    };

    union {
        uint64_t rsi; // 第2个参数
    };

    union {
        uint64_t rdi; // 第1个参数
    };

    union {
        uint64_t rbp; // 被调用者保存
    };

    union {
        uint64_t rsp; // 栈指针
    };

    uint64_t rip;

    union {
        uint64_t r8; // 第5个参数
    };

    union {
        uint64_t r9; // 第6个参数
    };

    uint64_t r10; // 调用者保存
    uint64_t r11; // 调用者保存
    uint64_t r12; // 被调用者保存
    uint64_t r13; // 被调用者保存
    uint64_t r14; // 被调用者保存
    uint64_t r15; // 被调用者保存
} reg_t;

// 定义一个寄存器
reg_t reg;
