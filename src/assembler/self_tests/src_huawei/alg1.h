#ifndef _ALG1_H
#define _ALG1_H
#define D2_WIDTH_IN 4608
#define D2_HEIGHT_IN 2592
#define D2_WIDTH_OUT  2304
#define D2_HEIGHT_OUT 1296
#define GRID_H 16
#define GRID_W 8

void alg1_func1(unsigned short d2_out[D2_HEIGHT_OUT][D2_WIDTH_OUT][3], unsigned short d2_in[D2_HEIGHT_IN][D2_WIDTH_IN][3]);
void alg1_func2(int out[GRID_H*GRID_W], unsigned short D1[D2_WIDTH_IN*D2_HEIGHT_IN]);
#endif
