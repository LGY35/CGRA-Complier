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

	//这部分代码的功能是计算增益查找表在输入图像中的位置，确保这些位置均匀分布在图像的宽度和高度上。
	//赋0初值
	int gain_pos_x[GAIN_LUT_X_NUM] = {0};
	int gain_pos_y[GAIN_LUT_Y_NUM] = {0};
	//循环赋值 pos gain数组【0】-【7】的每个元素  所以只能对8个位置进行增益，位置存在pos x中。
	//把图像宽度width平分了8组，gain pos 元素为0 (width-1)/7 (width-1)2/7...(width-1)7/7
	for (int i = 0; i < GAIN_LUT_X_NUM; i++) // ii = 1
	{
		gain_pos_x[i] = i * (width - 1) / (GAIN_LUT_X_NUM - 1);
	}
	//循环次数是个固定值，①在配置的时候，就配置到该PE，自己count down数八次结束运算；or②靠另一个产生i的PE使能
	//这个计算掰开，三个PE分别做 减法、 乘法、 除法，三个都得配置count 8次。
	//不光 循环因子PE、计算PE也就循环8次，这个for就计算量不大。

	//算法冗余，不映射——由于在前面的循环中，gain_pos_x[GAIN_LUT_X_NUM - 1] 已经被设置为 (width - 1)，所以这一步是冗余的，不会改变数组的值
	gain_pos_x[GAIN_LUT_X_NUM - 1] = (width - 1);

	//把height平分了6组，gain pos 元素为0 (height-1)/5 (height-1)2/5...(height-1)5/5
	for (int i = 0; i < GAIN_LUT_Y_NUM; i++) // ii = 1
	{
		gain_pos_y[i] = i * (height - 1) / (GAIN_LUT_Y_NUM - 1);
	}

	//算法冗余，不映射
	gain_pos_y[GAIN_LUT_Y_NUM - 1] = (height - 1);

	for (int y = 0; y < height; y++) // ii = 10
	{
		for (int x = 0; x < width; x++)
		{		
			//中间变量 xidx x1 x2	
			int x_idx = 0;
			int x1 = 0, x2 = 0;
			// 确定当前像素 x 在 gain_pos_x 数组中的相邻位置。
			// 确定当前像素在 x 方向上最近的两个增益位置 gain_pos_x[i-1] 和 gain_pos_x[i]，并计算它们之间的距离 x1 和 x2。
			for (int i = 1; i < GAIN_LUT_X_NUM; i++)
			{
				if (x <= gain_pos_x[i])		// 当找到第一个 x 小于或等于 gain_pos_x[i] 的位置时，确定它的左侧增益位置为 gain_pos_x[i - 1] 和右侧增益位置为 gain_pos_x[i]。
				{							//这个结构旨在找到当前像素 x 所在的区间，以便进行双线性插值。使用 <= 确保任何 x 值都能找到一个区间，而不是仅仅匹配具体的 gain_pos_x[i] 值。
					x_idx = i - 1;	// 如果 x 小于等于 gain_pos_x[i]，则找到对应的 x_idx。
					x1 = x - gain_pos_x[x_idx];		// x1 是当前像素到左侧增益位置的距离。
					x2 = gain_pos_x[x_idx + 1] - x; // x2 是当前像素到右侧增益位置的距离。
					break;	//只要找到第一个满足<=的，就推出循环
				}
			}
			int y_idx = 0;
			int y1 = 0, y2 = 0;
			for (int i = 1; i < GAIN_LUT_Y_NUM; i++)
			{
				if (y <= gain_pos_y[i])
				{
					y_idx = i - 1;
					y1 = y - gain_pos_y[y_idx];
					y2 = gain_pos_y[y_idx + 1] - y;
					break;
				}
			}

			//计算当前像素所在网格的宽度 grid_w 和高度 grid_h。
			//上述中间量传给加法PE得到grid
			int grid_w = x1 + x2;
			int grid_h = y1 + y2;
			//存储当前像素位置的四个角的增益值。没用上
			int corner_gain[4] = {0};
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
			//一次加法产生grid，传给一套（或4套）乘法PE做乘法，2次运算，正好和下面4个部分积2次乘法对齐。并行4套除法。再做三次加法，这样等待时间最短。
			//中间量x1 x2 y1 y2传给4套乘法，让乘法时间正好和load corner gain的时间对齐，cornergain传进来做第二次乘法。然后做三次加法。

			//计算加权增益————双线性插值算法（Bilinear Interpolation）的具体实现。一种在二维空间中进行插值的方法，它通过对相邻四个点的加权平均值进行计算，从而得到目标点的值。
			//load corner_gain[]可以共用一个内存接口，
			int gain = (x2 * y2 * corner_gain[0] + x1 * y2 * corner_gain[1] + x2 * y1 * corner_gain[2] + x1 * y1 * corner_gain[3]) / (grid_h * grid_w);//双线性插值算法的具体实现
			
			//应用增益并剪裁
			//循环因子y x、外部输入width, 一乘一加，计算地址y*width+x
			//地址传LSU访存取d1 in，传到乘法PE，*gain
			//结果传到专用clip bits
			//结果通过LSU写到mem，传递数据、地址
			d1_out[y*width+x] = clip_bits((d1_in[y*width + x] * gain) >> GAIN_FRAC_FRACTION_BITS,0,4096);
			//当前像素值d1_in[y * width + x] * 增益 gain ，然后除以1024，最后再限制到一定的范围内
			//上述运算要循环width*height次
		}
	}
}

/* 也就是说，
	每次计算，每个像素点都会计算，分别找到水平和垂直方向相邻的两个参考点pos-x和pos-y的坐标x-idx和y-idx，然后依据这两个idx坐标，和原始的xy坐标的奇偶性，去查找对应的gain里面的4个增益值，填入corner
	再利用左边/右边与x坐标之间的差值、上边/下边与y坐标之间的差值，一起填入差值公式，得到最终的增益。然后通过增益的计算公式，得到最终的坐标

*/ 