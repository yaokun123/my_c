//
// Created by 姚坤 on 2022/5/7.
//

#ifndef MY_C_DRAM_H
#define MY_C_DRAM_H

#include <stdlib.h>
#define MM_LEN 1000
uint8_t mm[MM_LEN];     // physical memory

uint64_t read64bits_dram(uint64_t paddr);
void write64bits_dram(uint64_t paddr, uint64_t data);
void print_register();
void print_stack();


#endif //MY_C_DRAM_H
