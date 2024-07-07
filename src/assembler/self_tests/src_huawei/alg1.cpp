#include <iostream>
#include"alg1.h"

#define GRID_H 16
#define GRID_W 8
#define clip_bits(X, MIN, MAX)  (((X) < (MIN)) ? (MIN) : (((X) > (MAX-1)) ? (MAX-1) : (X)))

//这段代码实现了一个双线性插值（bilinear interpolation）的图像缩放算法，将输入图像 d2_in 转换为输出图像 d2_out。
/*
它通过计算输入图像的每个像素点的加权平均值来生成输出图像的像素值。
grid_length_wide 和 grid_length_high 用于计算输入和输出图像尺寸的比例。
通过 i_src_left、i_src_right、j_src_left、j_src_right 确定输入图像中四个像素点的位置。
使用加权计算生成输出图像的每个像素值。
*/
void alg1_func1(unsigned short d2_out[D2_HEIGHT_OUT][D2_WIDTH_OUT][3], unsigned short d2_in[D2_HEIGHT_IN][D2_WIDTH_IN][3])
{
	int i_src_left = 0;
	int i_src_right = 0;
	int j_src_left = 0;
	int j_src_right = 0;
	int weight_wide = 0;
	int weight_high = 0;
	int val0 = 0;
	int val1 = 0;
	int val2 = 0;
	int val3 = 0;
	int temp0 = 0;
	int temp1 = 0;
	int grid_length_wide = (D2_WIDTH_IN << 10) / D2_WIDTH_OUT; //2048
	int grid_length_high = (D2_HEIGHT_IN << 10) / D2_HEIGHT_OUT; //2048
    int i = 0, j = 0;
    for (int k = 0; k < D2_HEIGHT_OUT * D2_WIDTH_OUT; k++) {
        if (k % D2_WIDTH_OUT == 0 && k != 0) {
            i++;
        }
        j = k % D2_WIDTH_OUT;
        i_src_left = (i * grid_length_wide) >> 10;
        i_src_right = (i_src_left + 1) >= D2_HEIGHT_IN ? i_src_left : (i_src_left + 1);
        j_src_left = (j * grid_length_high) >> 10;
        j_src_right = (j_src_left + 1) >= D2_WIDTH_IN ? j_src_left : (j_src_left + 1);
        weight_high = i * grid_length_high - (i_src_left << 10);
        weight_wide = j * grid_length_wide - (j_src_left << 10);
        val0 = d2_in[i_src_left][j_src_left][0];
        val1 = d2_in[i_src_left][j_src_right][0];
        val2 = d2_in[i_src_right][j_src_left][0];
        val3 = d2_in[i_src_right][j_src_right][0];
        temp0 = (weight_wide*val0 + (1024 - weight_wide)*val1) >> 10;
        temp1 = (weight_wide*val2 + (1024 - weight_wide)*val3) >> 10;
        d2_out[i][j][0] = (weight_high*temp0 + (1024 - weight_high)*temp1) >> 10;
        val0 = d2_in[i_src_left][j_src_left][1];
        val1 = d2_in[i_src_left][j_src_right][1];
        val2 = d2_in[i_src_right][j_src_left][1];
        val3 = d2_in[i_src_right][j_src_right][1];
        temp0 = (weight_wide*val0 + (1024 - weight_wide)*val1) >> 10;
        temp1 = (weight_wide*val2 + (1024 - weight_wide)*val3) >> 10;
        d2_out[i][j][1] = (weight_high*temp0 + (1024 - weight_high)*temp1) >> 10;
        val0 = d2_in[i_src_left][j_src_left][2];
        val1 = d2_in[i_src_left][j_src_right][2];
        val2 = d2_in[i_src_right][j_src_left][2];
        val3 = d2_in[i_src_right][j_src_right][2];
        temp0 = (weight_wide*val0 + (1024 - weight_wide)*val1) >> 10;
        temp1 = (weight_wide*val2 + (1024 - weight_wide)*val3) >> 10;
        d2_out[i][j][2] = (weight_high*temp0 + (1024 - weight_high)*temp1) >> 10;
    }
}

// 最开始是注释掉的
/*
功能：这段代码实现了某种基于网格的统计计算，可能用于某种分布映射或直方图统计。
它首先计算某种比率（clip_bits）存储在 v1 和 v2 中，然后在一个网格上统计这些比率的分布。
v1 和 v2 是动态分配的数组，用于存储某种比率计算的中间结果。
第一部分循环计算 v1 和 v2 的值，使用 clip_bits 限制值的范围。
第二部分循环根据 v1 和 v2 的值计算网格索引，并更新输出数组 out。
*/
int * v1;
int * v2;
void alg1_func2(int out[GRID_H*GRID_W], unsigned short D1[D2_WIDTH_IN*D2_HEIGHT_IN])
{

	v1 = (int *)malloc((D2_WIDTH_IN / 2) * (D2_HEIGHT_IN / 2) * sizeof(int));
	v2 = (int *)malloc((D2_WIDTH_IN / 2) * (D2_HEIGHT_IN / 2) * sizeof(int));
	unsigned int i = 0, j = 0;
	for (int k = 0; k < D2_HEIGHT_IN * D2_WIDTH_IN; k++) {
        if (k % D2_WIDTH_IN == 0 && k != 0) {
            i++;
        }
        j = k % D2_WIDTH_IN;

        // v1[i*D2_WIDTH_IN/2+j] = clip_bits((D1[2 * (i*D2_WIDTH_IN + j)] << 10) / (D1[2 * (i*D2_WIDTH_IN + j) + 1]), 0, 4095);
        // v2[i*D2_WIDTH_IN/2+j] = clip_bits((D1[2 * (i*D2_WIDTH_IN + j) + 1+ D2_WIDTH_IN] << 10) / (D1[2 * (i*D2_WIDTH_IN + j) + 1]), 0, 4095);
    }
	int index_w = 0;
	int index_h = 0;
	int step_w = 4095 / GRID_H;
	int step_h = 4095 / GRID_W;
	for (int i = 0; i < GRID_H*GRID_W; i++) {
		out[i] = 0;
	}
    i = 0;
    j = 0;
	for (int k = 0; k < D2_HEIGHT_IN * D2_WIDTH_IN; k++) {
        if (k % D2_WIDTH_IN == 0 && k != 0) {
            i++;
        }
        j = k % D2_WIDTH_IN;

        // index_w = v1[i*D2_WIDTH_IN / 2 + j] / step_w;
        // index_h = v2[i*D2_WIDTH_IN / 2 + j] / step_h;
        index_w = clip_bits(index_w, 0, GRID_W);
        index_h = clip_bits(index_h, 0, GRID_H);
        out[index_w*GRID_H + index_h] += 1;
    }
}