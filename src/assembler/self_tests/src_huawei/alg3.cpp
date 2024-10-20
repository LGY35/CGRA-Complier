#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GS_KERNEL	(4)
#define MF_KERNEL_TS2	(4)
#define MF_KERNEL_TS	(9)
#define BM_KERNEL_TS2	(4)
#define BM_KERNEL_TS	(9)
#define BM_WIN_RAD 3
#define PI			3.14159265358979323846


void alg3_func(unsigned short * d1in, unsigned short  * d1out, unsigned int width, unsigned int height)
{
	int arr[81] = {0};
	int temp;
	int * d1_c = (int *)malloc((width / 2) * (height / 2) * 4 * sizeof(int));
	int * d1_ce = (int*)malloc((width / 2 + 8) * (height / 2 + 8) * 4 * sizeof(int));
	int *bArray;
	int iFilterLen = 9 * 9;
	unsigned char bTemp;
	 int i, j;
	for ( int k = 0; k < (height*width/4); k++)// ii = 1
	{
		if(k % (width/2) == 0 && k != 0)
			i++;
		j = k % (width/2);
		d1_c[i * width / 2 + j] = d1in[i * 2 * width + j * 2];
		d1_c[i * width / 2 + j + (width / 2) * (height / 2)] = d1in[i * 2 * width + j * 2 + 1];
		d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2] = d1in[(i * 2 + 1) * width + j * 2];
		d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3] = d1in[(i * 2 + 1) * width + j * 2 + 1];
	}

	 int c = 0;i = 0;j = 0;
	//subloop1中心数据块
	for (int k = 0; k < 4 * (height/2) * (width/2); k++)
	{	
		// c = k / ((height/2) * (width/2));
		// i = (k / (width/2)) % (height/2);
		if(k % ((height/2) * (width/2)) == 0 && k != 0)
			c++;
		if(k % (width/2) == 0 && k != 0)
			i++;
		j = k % (width / 2);
		d1_ce[(4 + i) * (width / 2 + 8) + 4 + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[i *  width / 2 + j + c * (width / 2) * (height / 2)];
	}
	c = 0;i = 0;j = 0;
	//subloop2左侧边界填充
	i=4;
	for (int k = 0; k < 4 * (height/2) * 4; k++)
	{	
		// c = k / (height/2);
		// i = 4 + (k / 4) % (height/2);
		if(k % ((height/2) * 4) == 0 && k != 0)
			c++;
		if(k % 4 == 0 && k != 0)
			i++;
		j = k % 4;
		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) *  width / 2 + c * (width / 2) * (height / 2)];
	}
	c = 0;i = 0;j = 0;
	//subloop3右侧边界填充
	i=4;
	for (int k = 0; k < 4 * (height/2) * 4; k++)
	{	
		// c = k / (height/2);
		// i = 4 + (k / 4) % (height/2);
		if(k % ((height/2) * 4) == 0 && k != 0)
			c++;
		if(k % 4 == 0 && k != 0)
			i++;
		j = width / 2 + 4 + k % 4;
		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) *  width / 2 + width / 2 - 1 + c * (width / 2) * (height / 2)];
	}
	c = 0;i = 0;j = 0;
	//subloop4顶部边界填充
	for (int k = 0; k < 4 * 4 * (width/2+8); k++)
	{	
		// c = k / (4 * (width/2+8));
		if(k % (4 * (width/2+8)) == 0 && k != 0)
			c++; 
		// i = (k / (width/2+8)) % 4;
		if(k % (width/2+8) == 0 && k != 0)
			i++;
		j = k % (width/2+8);
		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[4 * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];
	}
	c = 0;i = 0;j = 0;
	//subloop5底部边界填充
	i = height / 2 + 4;
	for (int k = 0; k < 4 * 4 * (width/2+8); k++)
	{	
		// c = k / (4 * (width/2+8));
		// i = height / 2 + 4 + (k / (width/2+8)) % 4;
		if(k % (4 * (width/2+8)) == 0 && k != 0)
			c++;
		if(k % (width/2+8) == 0 && k != 0)
			i++;
		j = k % (width/2+8);
		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(height / 2 + 3) * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];
	}
	
	int MF_pixel_block[9 * 9] = { 0 };
	c = 0;
	i = 4;
	j = 4;
	for (int k = 0; k < 4 * (height / 2) * (width/2); k++)
	{	
		if(k % ((height / 2) * (width/2)) == 0 && k != 0)
		{
			c++;
			i = 4; // 重置 i 的初始值
		}
		if(k % (width/2) == 0 && k != 0)
		{
			i++;
			 j = 4; // 重置 j 的初始值
		}
		// 更新 j 的值
   		j = 4 + (k % (width / 2));

		MF_pixel_block[(0) * 9 + 0] = d1_ce[(i - 4) * (width / 2 + 8) + j - 4 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(0) * 9 + 1] = d1_ce[(i - 4) * (width / 2 + 8) + j - 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(0) * 9 + 2] = d1_ce[(i - 4) * (width / 2 + 8) + j - 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(0) * 9 + 3] = d1_ce[(i - 4) * (width / 2 + 8) + j - 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(0) * 9 + 4] = d1_ce[(i - 4) * (width / 2 + 8) + j + 0 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(0) * 9 + 5] = d1_ce[(i - 4) * (width / 2 + 8) + j + 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(0) * 9 + 6] = d1_ce[(i - 4) * (width / 2 + 8) + j + 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(0) * 9 + 7] = d1_ce[(i - 4) * (width / 2 + 8) + j + 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(0) * 9 + 8] = d1_ce[(i - 4) * (width / 2 + 8) + j + 4 + c * (width / 2 + 8) * (height / 2 + 8)];

		MF_pixel_block[(1) * 9 + 0] = d1_ce[(i - 3) * (width / 2 + 8) + j - 4 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(1) * 9 + 1] = d1_ce[(i - 3) * (width / 2 + 8) + j - 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(1) * 9 + 2] = d1_ce[(i - 3) * (width / 2 + 8) + j - 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(1) * 9 + 3] = d1_ce[(i - 3) * (width / 2 + 8) + j - 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(1) * 9 + 4] = d1_ce[(i - 3) * (width / 2 + 8) + j + 0 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(1) * 9 + 5] = d1_ce[(i - 3) * (width / 2 + 8) + j + 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(1) * 9 + 6] = d1_ce[(i - 3) * (width / 2 + 8) + j + 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(1) * 9 + 7] = d1_ce[(i - 3) * (width / 2 + 8) + j + 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(1) * 9 + 8] = d1_ce[(i - 3) * (width / 2 + 8) + j + 4 + c * (width / 2 + 8) * (height / 2 + 8)];

		MF_pixel_block[(2) * 9 + 0] = d1_ce[(i - 2) * (width / 2 + 8) + j - 4 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(2) * 9 + 1] = d1_ce[(i - 2) * (width / 2 + 8) + j - 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(2) * 9 + 2] = d1_ce[(i - 2) * (width / 2 + 8) + j - 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(2) * 9 + 3] = d1_ce[(i - 2) * (width / 2 + 8) + j - 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(2) * 9 + 4] = d1_ce[(i - 2) * (width / 2 + 8) + j + 0 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(2) * 9 + 5] = d1_ce[(i - 2) * (width / 2 + 8) + j + 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(2) * 9 + 6] = d1_ce[(i - 2) * (width / 2 + 8) + j + 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(2) * 9 + 7] = d1_ce[(i - 2) * (width / 2 + 8) + j + 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(2) * 9 + 8] = d1_ce[(i - 2) * (width / 2 + 8) + j + 4 + c * (width / 2 + 8) * (height / 2 + 8)];

		MF_pixel_block[(3) * 9 + 0] = d1_ce[(i - 1) * (width / 2 + 8) + j - 4 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(3) * 9 + 1] = d1_ce[(i - 1) * (width / 2 + 8) + j - 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(3) * 9 + 2] = d1_ce[(i - 1) * (width / 2 + 8) + j - 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(3) * 9 + 3] = d1_ce[(i - 1) * (width / 2 + 8) + j - 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(3) * 9 + 4] = d1_ce[(i - 1) * (width / 2 + 8) + j + 0 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(3) * 9 + 5] = d1_ce[(i - 1) * (width / 2 + 8) + j + 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(3) * 9 + 6] = d1_ce[(i - 1) * (width / 2 + 8) + j + 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(3) * 9 + 7] = d1_ce[(i - 1) * (width / 2 + 8) + j + 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(3) * 9 + 8] = d1_ce[(i - 1) * (width / 2 + 8) + j + 4 + c * (width / 2 + 8) * (height / 2 + 8)];

		MF_pixel_block[(4) * 9 + 0] = d1_ce[(i + 0) * (width / 2 + 8) + j - 4 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(4) * 9 + 1] = d1_ce[(i + 0) * (width / 2 + 8) + j - 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(4) * 9 + 2] = d1_ce[(i + 0) * (width / 2 + 8) + j - 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(4) * 9 + 3] = d1_ce[(i + 0) * (width / 2 + 8) + j - 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(4) * 9 + 4] = d1_ce[(i + 0) * (width / 2 + 8) + j + 0 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(4) * 9 + 5] = d1_ce[(i + 0) * (width / 2 + 8) + j + 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(4) * 9 + 6] = d1_ce[(i + 0) * (width / 2 + 8) + j + 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(4) * 9 + 7] = d1_ce[(i + 0) * (width / 2 + 8) + j + 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(4) * 9 + 8] = d1_ce[(i + 0) * (width / 2 + 8) + j + 4 + c * (width / 2 + 8) * (height / 2 + 8)];

		MF_pixel_block[(5) * 9 + 0] = d1_ce[(i + 1) * (width / 2 + 8) + j - 4 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(5) * 9 + 1] = d1_ce[(i + 1) * (width / 2 + 8) + j - 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(5) * 9 + 2] = d1_ce[(i + 1) * (width / 2 + 8) + j - 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(5) * 9 + 3] = d1_ce[(i + 1) * (width / 2 + 8) + j - 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(5) * 9 + 4] = d1_ce[(i + 1) * (width / 2 + 8) + j + 0 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(5) * 9 + 5] = d1_ce[(i + 1) * (width / 2 + 8) + j + 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(5) * 9 + 6] = d1_ce[(i + 1) * (width / 2 + 8) + j + 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(5) * 9 + 7] = d1_ce[(i + 1) * (width / 2 + 8) + j + 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(5) * 9 + 8] = d1_ce[(i + 1) * (width / 2 + 8) + j + 4 + c * (width / 2 + 8) * (height / 2 + 8)];

		MF_pixel_block[(6) * 9 + 0] = d1_ce[(i + 2) * (width / 2 + 8) + j - 4 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(6) * 9 + 1] = d1_ce[(i + 2) * (width / 2 + 8) + j - 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(6) * 9 + 2] = d1_ce[(i + 2) * (width / 2 + 8) + j - 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(6) * 9 + 3] = d1_ce[(i + 2) * (width / 2 + 8) + j - 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(6) * 9 + 4] = d1_ce[(i + 2) * (width / 2 + 8) + j + 0 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(6) * 9 + 5] = d1_ce[(i + 2) * (width / 2 + 8) + j + 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(6) * 9 + 6] = d1_ce[(i + 2) * (width / 2 + 8) + j + 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(6) * 9 + 7] = d1_ce[(i + 2) * (width / 2 + 8) + j + 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(6) * 9 + 8] = d1_ce[(i + 2) * (width / 2 + 8) + j + 4 + c * (width / 2 + 8) * (height / 2 + 8)];

		MF_pixel_block[(7) * 9 + 0] = d1_ce[(i + 3) * (width / 2 + 8) + j - 4 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(7) * 9 + 1] = d1_ce[(i + 3) * (width / 2 + 8) + j - 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(7) * 9 + 2] = d1_ce[(i + 3) * (width / 2 + 8) + j - 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(7) * 9 + 3] = d1_ce[(i + 3) * (width / 2 + 8) + j - 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(7) * 9 + 4] = d1_ce[(i + 3) * (width / 2 + 8) + j + 0 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(7) * 9 + 5] = d1_ce[(i + 3) * (width / 2 + 8) + j + 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(7) * 9 + 6] = d1_ce[(i + 3) * (width / 2 + 8) + j + 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(7) * 9 + 7] = d1_ce[(i + 3) * (width / 2 + 8) + j + 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(7) * 9 + 8] = d1_ce[(i + 3) * (width / 2 + 8) + j + 4 + c * (width / 2 + 8) * (height / 2 + 8)];

		MF_pixel_block[(8) * 9 + 0] = d1_ce[(i + 4) * (width / 2 + 8) + j - 4 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(8) * 9 + 1] = d1_ce[(i + 4) * (width / 2 + 8) + j - 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(8) * 9 + 2] = d1_ce[(i + 4) * (width / 2 + 8) + j - 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(8) * 9 + 3] = d1_ce[(i + 4) * (width / 2 + 8) + j - 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(8) * 9 + 4] = d1_ce[(i + 4) * (width / 2 + 8) + j + 0 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(8) * 9 + 5] = d1_ce[(i + 4) * (width / 2 + 8) + j + 1 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(8) * 9 + 6] = d1_ce[(i + 4) * (width / 2 + 8) + j + 2 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(8) * 9 + 7] = d1_ce[(i + 4) * (width / 2 + 8) + j + 3 + c * (width / 2 + 8) * (height / 2 + 8)];
		MF_pixel_block[(8) * 9 + 8] = d1_ce[(i + 4) * (width / 2 + 8) + j + 4 + c * (width / 2 + 8) * (height / 2 + 8)];
		
		// d1_c[(i - 4) * width / 2 + (j - 4) + c * (width / 2) * (height / 2)] = alg3_func_1(MF_pixel_block, 9 * 9);

		
		bArray = MF_pixel_block;
		// 冒泡排序部分
		// for (int j = 0; j < iFilterLen - 1; j++) {
		// 	for (int i = 0; i < iFilterLen - j - 1; i++) {
		// 		if (bArray[i] > bArray[i + 1]) {
		// 			bTemp = bArray[i];
		// 			bArray[i] = bArray[i + 1];
		// 			bArray[i + 1] = bTemp;
		// 		}
		// 	}
		// }
		// 展开j=0的迭代
		{
			// 展开i=0的迭代
			if (MF_pixel_block[0] > MF_pixel_block[1]) { temp = MF_pixel_block[0]; MF_pixel_block[0] = MF_pixel_block[1]; MF_pixel_block[1] = temp; }
			if (MF_pixel_block[1] > MF_pixel_block[2]) { temp = MF_pixel_block[1]; MF_pixel_block[1] = MF_pixel_block[2]; MF_pixel_block[2] = temp; }
			if (MF_pixel_block[2] > MF_pixel_block[3]) { temp = MF_pixel_block[2]; MF_pixel_block[2] = MF_pixel_block[3]; MF_pixel_block[3] = temp; }
			if (MF_pixel_block[3] > MF_pixel_block[4]) { temp = MF_pixel_block[3]; MF_pixel_block[3] = MF_pixel_block[4]; MF_pixel_block[4] = temp; }
			if (MF_pixel_block[4] > MF_pixel_block[5]) { temp = MF_pixel_block[4]; MF_pixel_block[4] = MF_pixel_block[5]; MF_pixel_block[5] = temp; }
			if (MF_pixel_block[5] > MF_pixel_block[6]) { temp = MF_pixel_block[5]; MF_pixel_block[5] = MF_pixel_block[6]; MF_pixel_block[6] = temp; }
			if (MF_pixel_block[6] > MF_pixel_block[7]) { temp = MF_pixel_block[6]; MF_pixel_block[6] = MF_pixel_block[7]; MF_pixel_block[7] = temp; }
			if (MF_pixel_block[7] > MF_pixel_block[8]) { temp = MF_pixel_block[7]; MF_pixel_block[7] = MF_pixel_block[8]; MF_pixel_block[8] = temp; }
		}
		// 展开j=1的迭代
		{
			if (MF_pixel_block[0] > MF_pixel_block[2]) { temp = MF_pixel_block[0]; MF_pixel_block[0] = MF_pixel_block[2]; MF_pixel_block[2] = temp; }
			if (MF_pixel_block[1] > MF_pixel_block[3]) { temp = MF_pixel_block[1]; MF_pixel_block[1] = MF_pixel_block[3]; MF_pixel_block[3] = temp; }
			if (MF_pixel_block[2] > MF_pixel_block[4]) { temp = MF_pixel_block[2]; MF_pixel_block[2] = MF_pixel_block[4]; MF_pixel_block[4] = temp; }
			if (MF_pixel_block[3] > MF_pixel_block[5]) { temp = MF_pixel_block[3]; MF_pixel_block[3] = MF_pixel_block[5]; MF_pixel_block[5] = temp; }
			if (MF_pixel_block[4] > MF_pixel_block[6]) { temp = MF_pixel_block[4]; MF_pixel_block[4] = MF_pixel_block[6]; MF_pixel_block[6] = temp; }
			if (MF_pixel_block[5] > MF_pixel_block[7]) { temp = MF_pixel_block[5]; MF_pixel_block[5] = MF_pixel_block[7]; MF_pixel_block[7] = temp; }
			if (MF_pixel_block[6] > MF_pixel_block[8]) { temp = MF_pixel_block[6]; MF_pixel_block[6] = MF_pixel_block[8]; MF_pixel_block[8] = temp; }
		}
		// 展开j=2的迭代
		{
			if (MF_pixel_block[0] > MF_pixel_block[3]) { temp = MF_pixel_block[0]; MF_pixel_block[0] = MF_pixel_block[3]; MF_pixel_block[3] = temp; }
			if (MF_pixel_block[1] > MF_pixel_block[4]) { temp = MF_pixel_block[1]; MF_pixel_block[1] = MF_pixel_block[4]; MF_pixel_block[4] = temp; }
			if (MF_pixel_block[2] > MF_pixel_block[5]) { temp = MF_pixel_block[2]; MF_pixel_block[2] = MF_pixel_block[5]; MF_pixel_block[5] = temp; }
			if (MF_pixel_block[3] > MF_pixel_block[6]) { temp = MF_pixel_block[3]; MF_pixel_block[3] = MF_pixel_block[6]; MF_pixel_block[6] = temp; }
			if (MF_pixel_block[4] > MF_pixel_block[7]) { temp = MF_pixel_block[4]; MF_pixel_block[4] = MF_pixel_block[7]; MF_pixel_block[7] = temp; }
			if (MF_pixel_block[5] > MF_pixel_block[8]) { temp = MF_pixel_block[5]; MF_pixel_block[5] = MF_pixel_block[8]; MF_pixel_block[8] = temp; }
		}

		// 展开j=3的迭代
		{
			if (MF_pixel_block[0] > MF_pixel_block[4]) { temp = MF_pixel_block[0]; MF_pixel_block[0] = MF_pixel_block[4]; MF_pixel_block[4] = temp; }
			if (MF_pixel_block[1] > MF_pixel_block[5]) { temp = MF_pixel_block[1]; MF_pixel_block[1] = MF_pixel_block[5]; MF_pixel_block[5] = temp; }
			if (MF_pixel_block[2] > MF_pixel_block[6]) { temp = MF_pixel_block[2]; MF_pixel_block[2] = MF_pixel_block[6]; MF_pixel_block[6] = temp; }
			if (MF_pixel_block[3] > MF_pixel_block[7]) { temp = MF_pixel_block[3]; MF_pixel_block[3] = MF_pixel_block[7]; MF_pixel_block[7] = temp; }
			if (MF_pixel_block[4] > MF_pixel_block[8]) { temp = MF_pixel_block[4]; MF_pixel_block[4] = MF_pixel_block[8]; MF_pixel_block[8] = temp; }
		}

		// 展开j=4的迭代
		{
			if (MF_pixel_block[0] > MF_pixel_block[5]) { temp = MF_pixel_block[0]; MF_pixel_block[0] = MF_pixel_block[5]; MF_pixel_block[5] = temp; }
			if (MF_pixel_block[1] > MF_pixel_block[6]) { temp = MF_pixel_block[1]; MF_pixel_block[1] = MF_pixel_block[6]; MF_pixel_block[6] = temp; }
			if (MF_pixel_block[2] > MF_pixel_block[7]) { temp = MF_pixel_block[2]; MF_pixel_block[2] = MF_pixel_block[7]; MF_pixel_block[7] = temp; }
			if (MF_pixel_block[3] > MF_pixel_block[8]) { temp = MF_pixel_block[3]; MF_pixel_block[3] = MF_pixel_block[8]; MF_pixel_block[8] = temp; }
		}

		// 展开j=5的迭代
		{
			if (MF_pixel_block[0] > MF_pixel_block[6]) { temp = MF_pixel_block[0]; MF_pixel_block[0] = MF_pixel_block[6]; MF_pixel_block[6] = temp; }
			if (MF_pixel_block[1] > MF_pixel_block[7]) { temp = MF_pixel_block[1]; MF_pixel_block[1] = MF_pixel_block[7]; MF_pixel_block[7] = temp; }
			if (MF_pixel_block[2] > MF_pixel_block[8]) { temp = MF_pixel_block[2]; MF_pixel_block[2] = MF_pixel_block[8]; MF_pixel_block[8] = temp; }
		}

		// 展开j=6的迭代
		{
			if (MF_pixel_block[0] > MF_pixel_block[7]) { temp = MF_pixel_block[0]; MF_pixel_block[0] = MF_pixel_block[7]; MF_pixel_block[7] = temp; }
			if (MF_pixel_block[1] > MF_pixel_block[8]) { temp = MF_pixel_block[1]; MF_pixel_block[1] = MF_pixel_block[8]; MF_pixel_block[8] = temp; }
		}

		// 展开j=7的迭代
		{
			if (MF_pixel_block[0] > MF_pixel_block[8]) { temp = MF_pixel_block[0]; MF_pixel_block[0] = MF_pixel_block[8]; MF_pixel_block[8] = temp; }
		}

		// 中值计算部分
		bTemp = bArray[(iFilterLen + 1) / 2];

		d1_c[(i - 4) * width / 2 + (j - 4) + c * (width / 2) * (height / 2)] = bTemp;

	}
	

	i = 0;j = 0;
	for ( int k = 0; k < (height*width/4); k++)// ii = 1
	{
		if(k % (width/2) == 0 && k != 0)
			i++;
		j = k % (width/2);//TODO: check
		d1out[i * 2 * width + j * 2] = d1_c[i * width / 2 + j];
		d1out[i * 2 * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2)];
		d1out[(i * 2 + 1) * width + j * 2] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2];
		d1out[(i * 2 + 1) * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3];
	}
	free(d1_c);
	free(d1_ce);
}