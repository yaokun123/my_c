#include "cpu/mmu.h"
#include "memory/dram.h"

// 虚拟地址转为物理地址的实现
uint64_t va2pa(uint64_t vaddr){
    return vaddr % MM_LEN;
}
