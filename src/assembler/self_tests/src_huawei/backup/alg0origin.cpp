#include <stdio.h>
#include "alg0.h"
//gain lut、frac bits算法定了就定了。PEA切换配置（算法）时，作为立即数配置到PE内。
//静态配置。

#define GAIN_LUT_X_NUM (8)
#define GAIN_LUT_Y_NUM (6)
#define GAIN_FRAC_FRACTION_BITS (10)
//clip bits不拆开映射，专门由一个PE单独做2拍，发出选择信号
#define clip_bits(X, MIN, MAX)  (((X) < (MIN)) ? (MIN) : (((X) > (MAX-1)) ? (MAX-1) : (X)))
void alg0_func(unsigned short* d1_in, unsigned short* d1_out, unsigned int width, unsigned int height)
{
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
	//0初值赋给 pos gain[8]
	int gain_pos_x[GAIN_LUT_X_NUM] = {0};
	int gain_pos_y[GAIN_LUT_Y_NUM] = {0};

	//循环赋值 pos gain数组【0】-【7】的每个元素
	//把width平分了8组，gain pos 元素为0 (width-1)/7 (width-1)2/7...(width-1)7/7
	for (int i = 0; i < GAIN_LUT_X_NUM; i++)					//i可以不放阵列上
	{	
		gain_pos_x[i] = i * (width - 1) / (GAIN_LUT_X_NUM - 1);	//循环因子i自增
	}
	//循环次数是个固定值，①在配置的时候，就配置到该PE，自己count down数八次结束运算；or②靠另一个产生i的PE使能
	//这个计算掰开，三个PE分别做 减法、 乘法、 除法，三个都得配置count 8次。
	//不光 循环因子PE、计算PE也就循环8次，这个for就计算量不大。

	//算法冗余，不映射
	gain_pos_x[GAIN_LUT_X_NUM - 1] = (width - 1);

	//把height平分了6组，gain pos 元素为0 (height-1)/5 (height-1)2/5...(height-1)5/5
	for (int i = 0; i < GAIN_LUT_Y_NUM; i++)
	{
		gain_pos_y[i] = i * (height - 1) / (GAIN_LUT_Y_NUM - 1);
	}
	//算法冗余，不映射
	gain_pos_y[GAIN_LUT_Y_NUM - 1] = (height - 1);

	//像这种，循环次数是外部输入变量，由阵列上一个PE来生成循环因子x：阵列如今控制流、数据流是解耦的。这种操作是，这个generate循环因子的pe，它的数据流给i，它的控制流给出循环配置的tag。
	//这种for循环，在PEA上静态映射就行。分支选择，再动态映射。
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)							
		{	
			//中间变量 xidx x1 x2	
			int x_idx = 0;
			int x1 = 0, x2 = 0;
			//感觉可以共用一个i因子，不过这个从1开始分发。
			for (int i = 1; i < GAIN_LUT_X_NUM; i++)			//i到达边界 要反馈给x++，为避免这个信号在阵列内外传输，i也放阵列上
			{
				//感觉可以上面gain pos x直接传过来。不过if块需要x因子使能
				if (x <= gain_pos_x[i])
				{	
					//不过没有硬件每次刷新中间变量，不按算法一一映射，不知道会不会出错
					x_idx = i - 1;
					//然后i-1位的gain pos x存在减法PE的LR，如果if 使能信号进来，就做x - gain_pos_x[i-1]这个减法
					x1 = x - gain_pos_x[x_idx];					//x1 = x - gain_pos_x[i-1]
					//第i个gain pos x正好传过来，同理如果if使能，就做gain_pos_x[i] - x这个减法
					x2 = gain_pos_x[x_idx + 1] - x;    			//x2 = gain_pos_x[i] - x
					break;
					//这样不需要访存gain pos
				}
			}
			//同上，复制一套并行。
			int y_idx = 0;
			int y1 = 0, y2 = 0;
			for (int i = 1; i < GAIN_LUT_Y_NUM; i++)			//这里y先循环完，可以令x收到两个i都到达边界的信号再x++
			{
				if (y <= gain_pos_y[i])
				{
					y_idx = i - 1;
					y1 = y - gain_pos_y[y_idx];
					y2 = gain_pos_y[y_idx + 1] - y;    
					break;//跳出for
				}
			}
			//上述中间量传给加法PE得到grid
			int grid_w = x1 + x2;
			int grid_h = y1 + y2;
			//没用上
			int corner_gain[4] = {0};
			//gain 1 2 3是存在mem里的，肯定要访存，让i传给减法pe做i-1，也传给corner gain的load PE，这里并行4套，提高吞吐
			//width*height次循环，每次都要做一次下面访存
			//4套if判断
			if (y % 2 == 0 && x % 2 == 0) // x y均偶，取gain 1。！！！gain在mem按正方形排布还是15，16，25，26排布。
			{
				corner_gain[0] = gain1[y_idx][x_idx];
				corner_gain[1] = gain1[y_idx][x_idx + 1];
				corner_gain[2] = gain1[y_idx + 1][x_idx];
				corner_gain[3] = gain1[y_idx + 1][x_idx + 1];
			}
			//算法一一映射有冗余，暂且不管。
			else if (y % 2 == 0 && x % 2 == 1) //x奇y偶，取gain2。
			{
				corner_gain[0] = gain2[y_idx][x_idx];
				corner_gain[1] = gain2[y_idx][x_idx + 1];
				corner_gain[2] = gain2[y_idx + 1][x_idx];
				corner_gain[3] = gain2[y_idx + 1][x_idx + 1];
			}
			else if (y % 2 == 1 && x % 2 == 0)  //x偶y奇，取gain2
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

			//load corner_gain[]可以共用一个内存接口，
			int gain = (x2 * y2 * corner_gain[0] + x1 * y2 * corner_gain[1] + x2 * y1 * corner_gain[2] + x1 * y1 * corner_gain[3]) / (grid_h * grid_w);
			//循环因子y x、外部输入width, 一乘一加，计算地址y*width+x
			//地址传LSU访存取d1 in，传到乘法PE，*gain
			//结果传到专用clip bits
			//结果通过LSU写到mem，传递数据、地址
			d1_out[y*width+x] = clip_bits((d1_in[y*width + x] * gain) >> GAIN_FRAC_FRACTION_BITS,0,4096);
			
			//上述运算要循环width*height次
		}
	}
}