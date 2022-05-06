#include <stdint.h>

#define NUM_INSTRTYPE 30
typedef enum OP{
    MOV,    // 0
    PUSH,   // 1
    CALL,   // 2
    ADD_REG_REG //3
} op_t;

// pointer pointing to the function
typedef void (*handler_t)(uint64_t,uint64_t);
handler_t handler_table[NUM_INSTRTYPE];
void add_reg_reg_handler(uint64_t src,uint64_t dst);

typedef enum OD_TYPE{
    IMM,
    REG,
    MM_IMM,
    MM_REG,
    MM_IMM_REG,
    MM_REG1_REG2,
    MM_IMM_REG1_REG2,
    MM_REG2_S,
    MM_IMM_REG2_S,
    MM_REG1_REG2_S,
    MM_IMM_REG1_REG2_S
} od_type_t;

typedef struct OD{
    od_type_t type;

    int64_t imm;   // 立即数，格式$Imm
    int64_t scale;
    uint64_t *reg1;
    uint64_t *reg2;
} od_t;

typedef struct INSTRUCT_STRUCT{
    op_t op;
    od_t src;
    od_t dst;

    char code[100];
} inst_t;

uint64_t decode_od(od_t od);

void instruction_cycle();

