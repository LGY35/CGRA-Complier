#include <stdio.h>
#include "alg0.h"
#define GAIN_LUT_X_NUM (8)
#define GAIN_LUT_Y_NUM (6)
#define GAIN_FRAC_FRACTION_BITS (10)
#define clip_bits(X, MIN, MAX)  (((X) < (MIN)) ? (MIN) : (((X) > (MAX-1)) ? (MAX-1) : (X)))
void alg0_func(unsigned short* d1_in, unsigned short* d1_out, unsigned int width, unsigned int height)
{
	int gain1[GAIN_LUT_Y_NUM][GAIN_LUT_X_NUM] = {
		{1624, 1524, 1024, 1024, 1024, 1024, 1624, 1824},
		{1624, 1424, 1024, 1024, 1024, 1024, 1524, 1724},
		{1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024},
		{1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024},
		{1624, 1424, 1024, 1024, 1024, 1024, 1324, 1624},
		{1824, 1524, 1024, 1024, 1024, 1024, 1524, 1724}
	};
	int gain2[GAIN_LUT_Y_NUM][GAIN_LUT_X_NUM] = {
		{1624, 1524, 1024, 1024, 1024, 1024, 1624, 1784},
		{1624, 1424, 1024, 1024, 1024, 1024, 1584, 1664},
		{1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024},
		{1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024},
		{1524, 1324, 1024, 1024, 1024, 1024, 1424, 1664},
		{1724, 1424, 1024, 1024, 1024, 1024, 1554, 1784}
	};
	int gain3[GAIN_LUT_Y_NUM][GAIN_LUT_X_NUM] = {
		{1224, 1154, 1024, 1024, 1024, 1024, 1184, 1324},
		{1164, 1124, 1024, 1024, 1024, 1024, 1124, 1164},
		{1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024},
		{1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024},
		{1324, 1224, 1024, 1024, 1024, 1024, 1264, 1324},
		{1424, 1264, 1024, 1024, 1024, 1024, 1314, 1484}
	};

	int gain_pos_x[GAIN_LUT_X_NUM] = {0};
	int gain_pos_y[GAIN_LUT_Y_NUM] = {0};
	for (int i = 0; i < GAIN_LUT_X_NUM; i++) // ii = 1
	{
		gain_pos_x[i] = i * (width - 1) / (GAIN_LUT_X_NUM - 1);
	}
	gain_pos_x[GAIN_LUT_X_NUM - 1] = (width - 1);
	for (int i = 0; i < GAIN_LUT_Y_NUM; i++) // ii = 1
	{
		gain_pos_y[i] = i * (height - 1) / (GAIN_LUT_Y_NUM - 1);
	}
	gain_pos_y[GAIN_LUT_Y_NUM - 1] = (height - 1);
	
	int x = 0, y = 0;
	for (int k = 0; k < height * width; k++) // ii = 10
	{

		if(k % width == 0 && k != 0)
			y++;
		x = k % width;	

		int x_idx = 0;
		int x1 = 0, x2 = 0;
		// 循环展开
		if (x <= gain_pos_x[1]) {
			x_idx = 0;
			x1 = x - gain_pos_x[0];
			x2 = gain_pos_x[1] - x;
		}
		else if (x <= gain_pos_x[2]) {
			x_idx = 1;
			x1 = x - gain_pos_x[1];
			x2 = gain_pos_x[2] - x;
		}
		else if (x <= gain_pos_x[3]) {
			x_idx = 2;
			x1 = x - gain_pos_x[2];
			x2 = gain_pos_x[3] - x;
		}
		else if (x <= gain_pos_x[4]) {
			x_idx = 3;
			x1 = x - gain_pos_x[3];
			x2 = gain_pos_x[4] - x;
		}
		else if (x <= gain_pos_x[5]) {
			x_idx = 4;
			x1 = x - gain_pos_x[4];
			x2 = gain_pos_x[5] - x;
		}
		else if (x <= gain_pos_x[6]) {
			x_idx = 5;
			x1 = x - gain_pos_x[5];
			x2 = gain_pos_x[6] - x;
		}
		else if (x <= gain_pos_x[7]) {
			x_idx = 6;
			x1 = x - gain_pos_x[6];
			x2 = gain_pos_x[7] - x;
		}
		else {
			x_idx = 7;
			x1 = x - gain_pos_x[7];
			x2 = 0; // 因为这是最后一个位置，x2 无法取到正值
		}

		int y_idx = 0;
		int y1 = 0, y2 = 0;
		// 循环展开
		if (y <= gain_pos_y[1]) {
			y_idx = 1 - 1;
			y1 = y - gain_pos_y[y_idx];
			y2 = gain_pos_y[y_idx + 1] - y;
		} 
		else if (y <= gain_pos_y[2]) {
			y_idx = 2 - 1;
			y1 = y - gain_pos_y[y_idx];
			y2 = gain_pos_y[y_idx + 1] - y;
		} 
		else if (y <= gain_pos_y[3]) {
			y_idx = 3 - 1;
			y1 = y - gain_pos_y[y_idx];
			y2 = gain_pos_y[y_idx + 1] - y;
		} 
		else if (y <= gain_pos_y[4]) {
			y_idx = 4 - 1;
			y1 = y - gain_pos_y[y_idx];
			y2 = gain_pos_y[y_idx + 1] - y;
		} 
		else if (y <= gain_pos_y[5]) {
			y_idx = 5 - 1;
			y1 = y - gain_pos_y[y_idx];
			y2 = gain_pos_y[y_idx + 1] - y;
		}
		
		int grid_w = x1 + x2;
		int grid_h = y1 + y2;
		int corner_gain[4] = {0};
		if (y % 2 == 0 && x % 2 == 0) 
		{
			corner_gain[0] = gain1[y_idx][x_idx];
			corner_gain[1] = gain1[y_idx][x_idx + 1];
			corner_gain[2] = gain1[y_idx + 1][x_idx];
			corner_gain[3] = gain1[y_idx + 1][x_idx + 1];
		}
		else if (y % 2 == 0 && x % 2 == 1) 
		{
			corner_gain[0] = gain2[y_idx][x_idx];
			corner_gain[1] = gain2[y_idx][x_idx + 1];
			corner_gain[2] = gain2[y_idx + 1][x_idx];
			corner_gain[3] = gain2[y_idx + 1][x_idx + 1];
		}
		else if (y % 2 == 1 && x % 2 == 0) 
		{
			corner_gain[0] = gain2[y_idx][x_idx];
			corner_gain[1] = gain2[y_idx][x_idx + 1];
			corner_gain[2] = gain2[y_idx + 1][x_idx];
			corner_gain[3] = gain2[y_idx + 1][x_idx + 1];
		}
		else 
		{
			corner_gain[0] = gain3[y_idx][x_idx];
			corner_gain[1] = gain3[y_idx][x_idx + 1];
			corner_gain[2] = gain3[y_idx + 1][x_idx];
			corner_gain[3] = gain3[y_idx + 1][x_idx + 1];
		}
		int gain = (x2 * y2 * corner_gain[0] + x1 * y2 * corner_gain[1] + x2 * y1 * corner_gain[2] + x1 * y1 * corner_gain[3]) / (grid_h * grid_w);
		d1_out[y*width+x] = clip_bits((d1_in[y*width + x] * gain) >> GAIN_FRAC_FRACTION_BITS,0,4096);
	}
}