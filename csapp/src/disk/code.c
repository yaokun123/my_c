#include <stdlib.h>
#include "cpu/register.h"
#include "elf.h"

inst_t program[INST_LEN] = {
        {
                ADD_REG_REG,
                {REG, 0, 0, (uint64_t *)&reg.rax, NULL},
                {REG, 0, 0, (uint64_t *)&reg.rbx, NULL},
                "add rax rbx"
        },
};