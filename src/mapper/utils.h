#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define IN_VALID (-1)
//这个地方需要修改 否则导致数据越界
#define NUMS_OF_OP 24

#pragma region enumerations
enum OP_ID {
    // arithmetic IDeration
    ID_ADD = 0,
    ID_SUB, 
    ID_ABS,
    ID_NEG,
    ID_MUL,
    ID_UDIV,
    ID_SDIV,
    ID_MOD,
    ID_MAC,
    // compare
    ID_LT,
    ID_LE,
    ID_EQ,
    // logic IDeration
    ID_AND,
    ID_OR,
    ID_NOT,
    ID_XOR,
    ID_SEL,
    // shift
    ID_SHR,
    ID_ASHR,
    ID_SHL,
    // rout
    ID_ROUT,
    // mem
    ID_LOAD,
    ID_STORE,
    // const
    ID_CONST
};

enum Edge_Attr {
    ATTR_IN_VALID = -1,
    ATTR_CONST    = 1,
    ATTR_REV,
    ATTR_ORDER,
    ATTR_CONST_BASE
};
enum Conn_Type {
    CGRA_SIMPLE, 
    CGRA_CROSS
};

enum Degree_Dir {
    IN_DEGREE, 
    OUT_DEGREE
};
#pragma endregion

#pragma region struct definition
struct Bit_Matrix;
struct Deg_Pack;
typedef struct STK_stack_* STK_stack;
#define STACK_SIZE 128
struct STK_stack_ {
    int data[STACK_SIZE];
    STK_stack next;
    int top;
};
#pragma endregion

char* read_file(const char *filename);
STK_stack STK_init();
void STK_push(STK_stack *stack, int value);
int STK_pop(STK_stack *stack);
void STK_clear(STK_stack stack);