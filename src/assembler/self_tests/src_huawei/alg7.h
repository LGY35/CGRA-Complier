// #include <Windows.h> //change due to compilation error
#include <thread>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#ifndef uchar
typedef unsigned char uchar;
#endif // !uint8_t
#define INIT_XSIZE            2304
#define INIT_YSIZE            1296
#define BITWIDTH1              10
unsigned short alg7_func_1(unsigned short* alg7_1_input, int32_t positionX, int32_t positionY, int32_t deltaX, int32_t deltaY);
void alg7_func(unsigned short src_d3_data[INIT_YSIZE * INIT_XSIZE * 2], unsigned short dst_d3_data[INIT_YSIZE * INIT_XSIZE * 2]);