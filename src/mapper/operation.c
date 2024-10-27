#include "operation.h"

char* op_string[NUMS_OF_OP] = {
    "add",
    "sub",
    "abs",
    "neg",
    "mul",
    "mod",
    "mac",
    "lt",
    "le",
    "eq",
    "and",
    "or",
    "not",
    "xor",
    "sel",
    "shr",
    "ashr",
    "shl",
    "rout",
    "load",
    "store",
    "const",
    // 顺序需要修改
    "udiv",
    "sdiv"
};

int get_op(char* str) 
{
    for (int i = 0; i < NUMS_OF_OP; i++) {
        if (!strcmp(str, op_string[i])) {
            return i;
        }
    }
    printf("cannot find op %s", str);
    exit(1);
    return -1;
}

char* get_op_name(int i) 
{
    return op_string[i];
}

int is_const(enum OP_ID op_id)
{
    return (1 << op_id) & OP_CONST;
}