#include <stdio.h>
#include "alg0.h"
#define GAIN_LUT_X_NUM (8)	// 增益查找表（LUT）的尺寸
#define GAIN_LUT_Y_NUM (6)
#define GAIN_FRAC_FRACTION_BITS (10)	// 增益值的分数位，用于固定小数点计算。
#define clip_bits(X, MIN, MAX)  (((X) < (MIN)) ? (MIN) : (((X) > (MAX-1)) ? (MAX-1) : (X)))

/*
这段代码实现了一个图像增益调整算法。通过查找表（Look-Up Table，LUT）来对输入图像的每个像素应用不同的增益值，
然后将调整后的结果存储到输出图像中。
*/
//width和height是图像的宽度和高度
void alg0_func(unsigned short* d1_in, unsigned short* d1_out, unsigned int width, unsigned int height)
{
	//定义了三个不同的增益查找表。每个查找表有不同的增益值，用于处理不同位置和类型的像素。
	//3组写进代码的固定增益
	//尺寸6组*8个
	unsigned int gain1[GAIN_LUT_Y_NUM][GAIN_LUT_X_NUM] = {
		{1624, 1524, 1024, 1024, 1024, 1024, 1624, 1824},
		{1624, 1424, 1024, 1024, 1024, 1024, 1524, 1724},
		{1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024},
		{1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024},
		{1624, 1424, 1024, 1024, 1024, 1024, 1324, 1624},
		{1824, 1524, 1024, 1024, 1024, 1024, 1524, 1724}
	};
	unsigned int gain2[GAIN_LUT_Y_NUM][GAIN_LUT_X_NUM] = {
		{1624, 1524, 1024, 1024, 1024, 1024, 1624, 1784},
		{1624, 1424, 1024, 1024, 1024, 1024, 1584, 1664},
		{1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024},
		{1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024},
		{1524, 1324, 1024, 1024, 1024, 1024, 1424, 1664},
		{1724, 1424, 1024, 1024, 1024, 1024, 1554, 1784}
	};
	unsigned int gain3[GAIN_LUT_Y_NUM][GAIN_LUT_X_NUM] = {
		{1224, 1154, 1024, 1024, 1024, 1024, 1184, 1324},
		{1164, 1124, 1024, 1024, 1024, 1024, 1124, 1164},
		{1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024},
		{1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024},
		{1324, 1224, 1024, 1024, 1024, 1024, 1264, 1324},
		{1424, 1264, 1024, 1024, 1024, 1024, 1314, 1484}
	};

	//这部分代码的功能是计算增益查找表在输入图像中的位置，确保这些位置均匀分布在图像的宽度和高度上。
	//赋0初值
	unsigned int gain_pos_x[GAIN_LUT_X_NUM] = {0};
	unsigned int gain_pos_y[GAIN_LUT_Y_NUM] = {0};

	//循环赋值 pos gain数组【0】-【7】的每个元素  所以只能对8个位置进行增益，位置存在pos x中。
	//把图像宽度width平分了8组，gain pos 元素为0 (width-1)/7 (width-1)2/7...(width-1)7/7
	for (unsigned int i = 0; i < GAIN_LUT_X_NUM; i++) // ii = 1
	{
		gain_pos_x[i] = i * (width - 1) / (GAIN_LUT_X_NUM - 1);
	}
	gain_pos_x[GAIN_LUT_X_NUM - 1] = (width - 1);

	//把height平分了6组，gain pos 元素为0 (height-1)/5 (height-1)2/5...(height-1)5/5
	for (unsigned int i = 0; i < GAIN_LUT_Y_NUM; i++) // ii = 1
	{
		gain_pos_y[i] = i * (height - 1) / (GAIN_LUT_Y_NUM - 1);
	}
	gain_pos_y[GAIN_LUT_Y_NUM - 1] = (height - 1);
	
	//============================正式循环=========================================
	
	unsigned int x = 0,y = 0;
	unsigned int *x_idx_map = new unsigned int[width];
 	unsigned int *y_idx_map = new unsigned int[height];
	
	unsigned int pos = 0;
    for (unsigned int x = 0; x < width; x++) {
        if (x > gain_pos_x[pos + 1] && pos < GAIN_LUT_X_NUM - 1) pos++;
        x_idx_map[x] = pos;
    }
	pos = 0;
	for (unsigned int y = 0; y < height; y++) 
	{
		if (y > gain_pos_y[pos + 1] && pos < GAIN_LUT_Y_NUM - 1) pos++;
		y_idx_map[y] = pos;
	}

	for (unsigned int k = 0; k < height*width; k++) // ii = 10
	{
		if(k % width == 0 && k != 0)
			y++;
		// y = k / width;
		x = k % width;
		unsigned int x_idx = x_idx_map[x];
		unsigned int y_idx = y_idx_map[y];
		
		unsigned int x1 = x - gain_pos_x[x_idx];
		unsigned int x2 = gain_pos_x[x_idx + 1] - x;
		unsigned int y1 = y - gain_pos_y[y_idx];
		unsigned int y2 = gain_pos_y[y_idx + 1] - y;
		
		//计算当前像素所在网格的宽度 grid_w 和高度 grid_h。
		//上述中间量传给加法PE得到grid
		unsigned int grid_w = x1 + x2;
		unsigned int grid_h = y1 + y2;
		//存储当前像素位置的四个角的增益值。没用上
		unsigned int corner_gain[4] = {0};
		//gain 1 2 3是存在mem里的，肯定要访存，让i传给减法pe做i-1，也传给corner gain的load PE，这里并行4套，提高吞吐
		//width*height次循环，每次都要做一次下面访存
		//4套if判断
		if (y % 2 == 0 && x % 2 == 0) 	// x y均偶，取gain 1。！！！gain在mem按正方形排布还是15，16，25，26排布。
		{	
			//双线性插值需要使用目标点周围的四个顶点值进行加权平均。
			corner_gain[0] = gain1[y_idx][x_idx];
			corner_gain[1] = gain1[y_idx][x_idx + 1];
			corner_gain[2] = gain1[y_idx + 1][x_idx];
			corner_gain[3] = gain1[y_idx + 1][x_idx + 1];
		}
		//算法一一映射有冗余，暂且不管。
		else if (y % 2 == 0 && x % 2 == 1) 	//x奇y偶，取gain2。
		{
			corner_gain[0] = gain2[y_idx][x_idx];
			corner_gain[1] = gain2[y_idx][x_idx + 1];
			corner_gain[2] = gain2[y_idx + 1][x_idx];
			corner_gain[3] = gain2[y_idx + 1][x_idx + 1];
		}
		else if (y % 2 == 1 && x % 2 == 0) 	//x偶y奇，取gain2
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
		//TODO:
		int gain = (x2 * y2 * corner_gain[0] + x1 * y2 * corner_gain[1] + x2 * y1 * corner_gain[2] + x1 * y1 * corner_gain[3]) / (grid_h * grid_w);//双线性插值算法的具体实现
		d1_out[y*width+x] = clip_bits((d1_in[y*width + x] * gain) >> GAIN_FRAC_FRACTION_BITS,0,4096);
		delete[] x_idx_map;
		delete[] y_idx_map;
	}
}

//============================正式循环=========================================
	// int x = 0,y = 0;
	// int *x_idx_map = new int[width];
	// int *y_idx_map = new int[height];

	// // Precompute x and y indices for each position
    // int pos = 0;
    // for (int x = 0; x < width; x++) {
    //     if (x > gain_pos_x[pos + 1] && pos < GAIN_LUT_X_NUM - 1) pos++;
    //     x_idx_map[x] = pos;
    // }
    // pos = 0;
    // for (int y = 0; y < height; y++) {
    //     if (y > gain_pos_y[pos + 1] && pos < GAIN_LUT_Y_NUM - 1) pos++;
    //     y_idx_map[y] = pos;
    // }

	// int dis = GAIN_LUT_X_NUM - GAIN_LUT_Y_NUM;
	// for(int k = 0; k < height*width; k++)
	// {
	// 	y = k / width;
	// 	x = k % width;
	// 	int x_idx = x_idx_map[x];
    //  int y_idx = y_idx_map[y];
	// 	int (*selected_gain)[GAIN_LUT_X_NUM] = (y % 2 == 0) ? ((x % 2 == 0) ? gain1 : gain2) : gain3;

	// 	int x1 = x - gain_pos_x[x_idx];
    //     int x2 = gain_pos_x[x_idx + 1] - x;
    //     int y1 = y - gain_pos_y[y_idx];
    //     int y2 = gain_pos_y[y_idx + 1] - y;
	// 	int grid_w = x1 + x2;
	// 	int grid_h = y1 + y2;

	// 	int corner_gain[4] = {
    //         selected_gain[y_idx][x_idx],
    //         selected_gain[y_idx][x_idx + 1],
    //         selected_gain[y_idx + 1][x_idx],
    //         selected_gain[y_idx + 1][x_idx + 1]
    //     };

	// 	int gain = (x2 * y2 * corner_gain[0] + x1 * y2 * corner_gain[1] + x2 * y1 * corner_gain[2] + x1 * y1 * corner_gain[3]) / (grid_h * grid_w);//双线性插值算法的具体实现
	// 	d1_out[y*width+x] = clip_bits((d1_in[y*width + x] * gain) >> GAIN_FRAC_FRACTION_BITS,0,4096);
	// 	delete[] x_idx_map;
	// 	delete[] y_idx_map;
	// }