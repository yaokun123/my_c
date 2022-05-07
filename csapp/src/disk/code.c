#include <stdlib.h>
#include "cpu/register.h"
#include "elf.h"

inst_t program[INST_LEN] = {
        {
                PUSH_REG,
                {REG, 0, 0, (uint64_t *)&reg.rbp, NULL},
                {EMPTY, 0, 0, NULL, NULL},
                "push %rbp"
        },
        {
                MOV_REG_REG,
                {REG, 0, 0, (uint64_t *)&reg.rsp, NULL},
                {REG, 0, 0, (uint64_t *)&reg.rbp, NULL},
                "mov %rsp,%rbp"
        },
        {
                MOV_REG_MEM,
                {REG, 0, 0, (uint64_t *)&reg.rdi, NULL},
                {MM_IMM_REG, -0x18, 0, (uint64_t *)&reg.rbp, NULL},
                "mov %rdi,-0x18(%rbp)"
        },
        {
                MOV_REG_MEM,
                {REG, 0, 0, (uint64_t *)&reg.rsi, NULL},
                {MM_IMM_REG, -0x20, 0, (uint64_t *)&reg.rbp, NULL},
                "mov %rsi,-0x20(%rbp)"
        },
        {
            "mov -0x18(%rbp),%rdx"
        },
        {
            "mov -0x20(%rbp),%rax"
        },
        {
            "add %rdx,%rax"
        },
        {
            "mov %rax,-0x8(%rbp)"
        },
        {
            "mov -0x8(%rbp),%rax"
        },
        {
            "pop %rbp"
        },
        {
            "retq"
        },

        // main entry point
        {
                MOV_REG_REG,
                {REG, 0, 0, (uint64_t *)&reg.rdx, NULL},
                {REG, 0, 0, (uint64_t *)&reg.rsi, NULL},
                "mov %rdx,%rsi"
        },
        {
            "mov %rax,%rdi"
        },
        {
            "callq 5fa <add>"
        },
        {
            "mov %rax,-0x8(%rbp)"
        }
};