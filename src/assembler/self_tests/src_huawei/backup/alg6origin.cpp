#include <iostream>
#include"alg6.h"
#define clip_bits(X, MIN, MAX)  (((X) < (MIN)) ? (MIN) : (((X) > (MAX)) ? (MAX) : (X))) 		//只取位于min<x<max之间的x，否则取上下限
void alg6_func_1(unsigned short d3_1_dst[ALG6_WIDTH*ALG6_HEIGHT], unsigned short d3_2_dst[ALG6_WIDTH / 2 * ALG6_HEIGHT], unsigned short d3_3_dst[ALG6_WIDTH / 2 * ALG6_HEIGHT], unsigned short d3_1_src[ALG6_WIDTH*ALG6_HEIGHT], unsigned short d3_2_src[ALG6_WIDTH*ALG6_HEIGHT], unsigned short d3_3_src[ALG6_WIDTH*ALG6_HEIGHT])
{
	int iHeight = ALG6_HEIGHT;			//1296
	int iWidth = ALG6_WIDTH;			//2304
	for (int i = 0; i < iWidth * iHeight; i++)		//不在阵列上做
	{
		d3_1_dst[i] = d3_1_src[i];
	}
	int ped3_2 = 0, ped3_3 = 0;
	for (int y = 0; y < iHeight; y++)
	{
		for (int x = 0; x < iWidth; x++)
		{
			if (x % 2 == 0)							//if块为真
			{
				ped3_2 = d3_2_src[iWidth*y + x];
				ped3_2 = clip_bits(ped3_2, 0, 1023);	//则load d3_2_src[iWidth*y + x]到clip bits块（if..else if）
				d3_2_dst[y * iWidth / 2 + x / 2] = ped3_2;		//clip bits块的结果直接store到d3_2_dst[]
			}
			else
			{
				ped3_3 = d3_3_src[iWidth*y + x]; 		//同上
				ped3_3 = clip_bits(ped3_3, 0, 1023);
				d3_3_dst[y * iWidth / 2 + x / 2] = ped3_3;
			}
		}
	}
}
//初始化func1的3输入
unsigned short d3_1[ALG6_HEIGHT * ALG6_WIDTH] = { 0 };
unsigned short d3_2[ALG6_HEIGHT * ALG6_WIDTH] = { 0 };
unsigned short d3_3[ALG6_HEIGHT * ALG6_WIDTH] = { 0 };
//初始化func1的3结果变量
unsigned short d3_1_dst[ALG6_HEIGHT * ALG6_WIDTH] = { 0 };
unsigned short d3_2_dst[ALG6_HEIGHT * ALG6_WIDTH / 2] = { 0 };
unsigned short d3_3_dst[ALG6_HEIGHT * ALG6_WIDTH / 2] = { 0 };

void alg6_func(unsigned short src_d3_data[ALG6_HEIGHT * ALG6_WIDTH * 2], unsigned short d4_dst[ALG6_HEIGHT * ALG6_WIDTH], unsigned short d2_in[ALG6_HEIGHT][ALG6_WIDTH][3])
{
	int iHeight = ALG6_HEIGHT;
	int iWidth = ALG6_WIDTH;
	//配置存到bank
	int tran_mat[9] = { 38,75,15,-22,-42,64,64,-54,-10 };
	for (int y = 0; y < iHeight; y++)
	{
		for (int x = 0; x < iWidth; x++)
		{	
			//中间量，分别对应d2_in的三通道
			int in_d2[3];         
			int ext_d3[3]; 
			//每次循环，把d2_in通道里的一个数，赋给中间变量    
			//d2_in存在bank，每次循环load一拍，通过LSU直接load到乘法PE
			in_d2[0] = d2_in[y][x][0];
			in_d2[1] = d2_in[y][x][1];
			in_d2[2] = d2_in[y][x][2];
			//每次循环cal七拍
			//3乘3加，可以分配3套乘法PE并行做，2套加法PE，3套移位，4拍做完。
 			ext_d3[0] = (in_d2[0] * tran_mat[0] + in_d2[1] * tran_mat[1] + in_d2[2] * tran_mat[2]+64) >> 7;		//也可以视作MAC计算，由一个PE用3拍执行完。第一拍in_d2[2]到，做完第一个乘加MAC，结果放进寄存器；接着第二拍in_d2[1]到，第三拍in_d2[0]到。分配3个PE。
			ext_d3[1] = (in_d2[0] * tran_mat[3] + in_d2[1] * tran_mat[4] + in_d2[2] * tran_mat[5]+64) >> 7;
			ext_d3[2] = (in_d2[0] * tran_mat[6] + in_d2[1] * tran_mat[7] + in_d2[2] * tran_mat[8]+64) >> 7;
			//并行,用1拍做加法
			ext_d3[0] = ext_d3[0];   
			ext_d3[1] = ext_d3[1] + (128 << 2);     
			ext_d3[2] = ext_d3[2] + (128 << 2);      
			//[iWidth*y + x]就是循环0~iwidth*iheight每一位
			//d2_in三通道的处理结果，一一对应d3_1、d3_2、d3_3的每一位，d3_1、d3_2、d3_3不store到bank，直接供func1对应的PE使用
			d3_1[iWidth*y + x] = clip_bits(ext_d3[0], 0, 1023);		//做2次if然后store
			//d2_in[0]的处理结果，一一对应store到d4_dst，d2_in[0]是二维数组，处理完转存为d4_dst一维数组。
			d4_dst[iWidth*y + x] = d3_1[iWidth*y + x];
			d3_2[iWidth*y + x] = clip_bits(ext_d3[1], 0, 1023);		//	
			d3_3[iWidth*y + x] = clip_bits(ext_d3[2], 0, 1023);		//clip_bits块做成一个算子
		}
	}

	//d3_1、d3_2、d3_3不store到bank，直接传到func1对应的PE使用
	alg6_func_1(d3_1_dst, d3_2_dst, d3_3_dst, d3_1, d3_2, d3_3);
	//func1处理结果d3_1_dst, d3_2_dst, d3_3_dst不store，直接传给4套if判断PE，d3_1_dst, d3_3_dst，d3_1_dst，d3_2_dst处理结果依次对应src_d3_data的每个第1、2、3、0位。最终结果src_d3_data再经过LSU store
	for (int j = 0; j < iHeight * iWidth * 2; j++) {
		if (j % 4 == 0) {
			src_d3_data[j] = d3_2_dst[j/4];
		} else if (j % 4 == 1) {
			src_d3_data[j] = d3_1_dst[(j-1) / 2];
		} else if (j % 4 == 2) {
			src_d3_data[j] = d3_3_dst[j / 4];
		} else if (j % 4 == 3) {
			src_d3_data[j] = d3_1_dst[(j-1) / 2];		//4个if块，2、4执行语句相同，可优化成2个if块。第1个if块判断模二：若余1，则直接load d3_1_dst[(j-1)/2]到src_d3_data[j]块，然后store。若余0，则使能第2个if块：余1则load d3_3_dst[j/4]，余0则load d3_2_dst[j/4]
		}
	}
}