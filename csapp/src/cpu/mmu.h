//
// Created by 姚坤 on 2022/5/7.
//

#ifndef MY_C_MMU_H
#define MY_C_MMU_H

// memory management unit
#include <stdint.h>

// 虚拟地址转换为物理地址
uint64_t va2pa(uint64_t vaddr);
#endif //MY_C_MMU_H
