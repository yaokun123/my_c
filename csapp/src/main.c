//
// Created by 姚坤 on 2022/5/6.
//

#include <stdio.h>
#include "cpu/register.h"
#include "cpu/mmu.h"
#include "memory/dram.h"
#include "disk/elf.h"

int main(){
    init_handler_table();

    // init register
    reg.rax = 0x12340000;
    reg.rbx = 0x0;
    reg.rcx = 0x8000660;
    reg.rdx = 0xabcd;
    reg.rsi = 0x7ffffffee2f8;
    reg.rdi = 0x1;
    reg.rbp = 0x7ffffffee210;
    reg.rsp = 0x7ffffffee1f0;

    reg.rip = (uint64_t)&program[11];       // 入口

    // init memory
    write64bits_dram(va2pa(0x7ffffffee210), 0x08000660);    // rbp
    write64bits_dram(va2pa(0x7ffffffee208), 0x0);
    write64bits_dram(va2pa(0x7ffffffee200), 0xabcd);
    write64bits_dram(va2pa(0x7ffffffee1f8), 0x12340000);
    write64bits_dram(va2pa(0x7ffffffee1f0), 0x08000660);    // rsp

    // run inst
    for (int i = 0; i < INST_LEN; ++i) {
        instruction_cycle();
    }
    print_register();
    print_stack();

    // verity
    int match = 1;
    match = match && (reg.rax == 0x1234abcd);
    match = match && (reg.rbx == 0x0);
    match = match && (reg.rcx == 0x08000660);
    match = match && (reg.rdx == 0x12340000);
    match = match && (reg.rsi == 0xabcd);
    match = match && (reg.rdi == 0x12340000);
    match = match && (reg.rbp == 0x7ffffffee210);
    match = match && (reg.rsp == 0x7ffffffee1f0);
    if(match == 1){
        printf("register match\n");
    }else{
        printf("register not match\n");
    }

    match = match && (read64bits_dram(va2pa(0x7ffffffee210)) == 0x08000660); // rbp
    match = match && (read64bits_dram(va2pa(0x7ffffffee208)) == 0x1234abcd);
    match = match && (read64bits_dram(va2pa(0x7ffffffee200)) == 0xabcd);
    match = match && (read64bits_dram(va2pa(0x7ffffffee1f8)) == 0x12340000);
    match = match && (read64bits_dram(va2pa(0x7ffffffee1f0)) == 0x08000660); // rsp
    if(match == 1){
        printf("memory match\n");
    }else{
        printf("memory not match\n");
    }

    return 0;
}

