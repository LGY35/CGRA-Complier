#include "utils.h"

// arithmetic operation
#define OP_ADD      (1 << 0)
#define OP_SUB      (1 << 1)
#define OP_ABS      (1 << 2)
#define OP_NEG      (1 << 3)
#define OP_MUL      (1 << 4)
#define OP_MOD      (1 << 5)
#define OP_MAC      (1 << 6)
// compare
#define OP_LT       (1 << 7)
#define OP_LE       (1 << 8)
#define OP_EQ       (1 << 9)
// logic operation
#define OP_AND      (1 << 10)
#define OP_OR       (1 << 11)
#define OP_NOT      (1 << 12)
#define OP_XOR      (1 << 13)
#define OP_SEL      (1 << 14)
// shift
#define OP_SHR      (1 << 15)
#define OP_ASHR     (1 << 16)
#define OP_SHL      (1 << 17)
// rout
#define OP_ROUT     (1 << 18)
// mem
#define OP_LOAD     (1 << 19)
#define OP_STORE    (1 << 20)
// const
#define OP_CONST    (1 << 21)
// 顺序需要修改
#define OP_UDIV     (1 << 22)   
#define OP_SDIV     (1 << 23)   

extern char* op_string[NUMS_OF_OP];

int get_op(char* str);
char* get_op_name(int i);
int is_const(enum OP_ID opcode);