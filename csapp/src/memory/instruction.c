//
// Created by 姚坤 on 2022/5/5.
//

//#include "memory/instruction.h"
#include "instruction.h"
#include "cpu/register.h"
#include "cpu/mmu.h"
#include <stdio.h>

uint64_t decode_od(od_t od){
    if(od.type == IMM){
        return od.imm;
    } else if(od.type == REG){
        return (uint64_t)od.reg1;
    }else{
        // mm
        uint64_t vaddr = 0;

        if(od.type == MM_IMM){
            vaddr = *((uint64_t *)&od.imm);
        }else if(od.type == MM_REG){
            vaddr = *(od.reg1);
        }else if(od.type == MM_IMM_REG){
            vaddr = od.imm + *(od.reg1);
        }else if(od.type == MM_REG1_REG2){
            vaddr = *(od.reg1) + *(od.reg2);
        }else if(od.type == MM_IMM_REG1_REG2){
            vaddr = od.imm + *(od.reg1) + *(od.reg2);
        }else if(od.type == MM_REG2_S){
            vaddr = od.scale * (*(od.reg2));
        }else if(od.type == MM_IMM_REG2_S){
            vaddr = od.imm + od.scale * (*(od.reg2));
        }else if(od.type == MM_REG1_REG2_S){
            vaddr = *(od.reg1)  + od.scale * (*(od.reg2));
        }else if(od.type == MM_IMM_REG1_REG2_S){
            vaddr = od.imm + *(od.reg1)  + od.scale * (*(od.reg2));
        }
        return va2pa(vaddr);
    }
}

// 指令周期
void instruction_cycle(){
    // 取址
    inst_t *inst = (inst_t *)reg.rip;
    // inst_t inst = program[reg.rip]

    // 译码
    // imm: imm
    // reg: value
    // mm:  paddr
    uint64_t src = decode_od(inst->src);
    uint64_t dst = decode_od(inst->dst);

    // 执行
    // add rax rbx
    // op = ADD_REG_REG = 3
    // handler_table[ADD_REG_REG] = handler_table[3] = add_reg_reg_handler
    handler_t handler = handler_table[inst->op]; // add_reg_reg_handler
    // add_reg_reg_handler(src = &rax,dst = &rbx)
    handler(src,dst);

    printf("%s\n", inst->code);
}

// 初始化指令的函数指针
void init_handler_table(){
    handler_table[ADD_REG_REG] = &add_reg_reg_handler;
    handler_table[MOV_REG_REG] = &mov_reg_reg_handler;
    handler_table[CALL] = &call_handler;
}
void call_handler(uint64_t src,uint64_t dst){
    reg.rsp = reg.rsp - 8;

    write64bits_dram(va2pa(reg.rsp), reg.rip+sizeof(inst_t));

    reg.rip = src;
}
void mov_reg_reg_handler(uint64_t src,uint64_t dst){
    *(uint64_t *)dst = *(uint64_t *)src;

    // 更新pc计数器
    reg.rip = reg.rip + sizeof(inst_t);
}

void add_reg_reg_handler(uint64_t src,uint64_t dst){
    // add_reg_reg_handler(src = &rax,dst = &rbx)
    /**
     rax pmm[0x1234] = 0x12340000;
     rbx pmm[0x1235] = 0xabcd;

     src: 0x1234
     dst: 0x1235

     *(uint64_t *)src = 0x12340000
     *(uint64_t *)dst = 0xabcd

     0x12340000 + 0xabcd = 0x1234abcd

     rbx pmm[0x1235] = 0x1234abcd;
     */
    *(uint64_t *)dst = *(uint64_t *)dst + *(uint64_t *)src;

    // 更新pc计数器
    reg.rip = reg.rip + sizeof(inst_t);
}