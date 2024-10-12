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


#define SWAP(a, b, temp) { temp = (a); (a) = (b); (b) = temp; }

#define COMPARE_AND_SWAP(arr, i, temp) \
    if ((arr)[i] > (arr)[(i) + 1]) { SWAP((arr)[i], (arr)[(i) + 1], temp); }

// 宏定义用于展开特定的 j 值时的所有比较和交换操作
#define BUBBLE_SORT_ITERATION(arr, j, temp) \
    COMPARE_AND_SWAP(arr, 0, temp) \
    COMPARE_AND_SWAP(arr, 1, temp) \
    COMPARE_AND_SWAP(arr, 2, temp) \
    COMPARE_AND_SWAP(arr, 3, temp) \
    COMPARE_AND_SWAP(arr, 4, temp) \
    COMPARE_AND_SWAP(arr, 5, temp) \
    COMPARE_AND_SWAP(arr, 6, temp) \
    COMPARE_AND_SWAP(arr, 7, temp) \
    COMPARE_AND_SWAP(arr, 8, temp) \
    COMPARE_AND_SWAP(arr, 9, temp) \
    COMPARE_AND_SWAP(arr, 10, temp) \
    COMPARE_AND_SWAP(arr, 11, temp) \
    COMPARE_AND_SWAP(arr, 12, temp) \
    COMPARE_AND_SWAP(arr, 13, temp) \
    COMPARE_AND_SWAP(arr, 14, temp) \
    COMPARE_AND_SWAP(arr, 15, temp) \
    COMPARE_AND_SWAP(arr, 16, temp) \
    COMPARE_AND_SWAP(arr, 17, temp) \
    COMPARE_AND_SWAP(arr, 18, temp) \
    COMPARE_AND_SWAP(arr, 19, temp) \
    COMPARE_AND_SWAP(arr, 20, temp) \
    COMPARE_AND_SWAP(arr, 21, temp) \
    COMPARE_AND_SWAP(arr, 22, temp) \
    COMPARE_AND_SWAP(arr, 23, temp) \
    COMPARE_AND_SWAP(arr, 24, temp) \
    COMPARE_AND_SWAP(arr, 25, temp) \
    COMPARE_AND_SWAP(arr, 26, temp) \
    COMPARE_AND_SWAP(arr, 27, temp) \
    COMPARE_AND_SWAP(arr, 28, temp) \
    COMPARE_AND_SWAP(arr, 29, temp) \
    COMPARE_AND_SWAP(arr, 30, temp) \
    COMPARE_AND_SWAP(arr, 31, temp) \
    COMPARE_AND_SWAP(arr, 32, temp) \
    COMPARE_AND_SWAP(arr, 33, temp) \
    COMPARE_AND_SWAP(arr, 34, temp) \
    COMPARE_AND_SWAP(arr, 35, temp) \
    COMPARE_AND_SWAP(arr, 36, temp) \
    COMPARE_AND_SWAP(arr, 37, temp) \
    COMPARE_AND_SWAP(arr, 38, temp) \
    COMPARE_AND_SWAP(arr, 39, temp) \
    COMPARE_AND_SWAP(arr, 40, temp) \
    COMPARE_AND_SWAP(arr, 41, temp) \
    COMPARE_AND_SWAP(arr, 42, temp) \
    COMPARE_AND_SWAP(arr, 43, temp) \
    COMPARE_AND_SWAP(arr, 44, temp) \
    COMPARE_AND_SWAP(arr, 45, temp) \
    COMPARE_AND_SWAP(arr, 46, temp) \
    COMPARE_AND_SWAP(arr, 47, temp) \
    COMPARE_AND_SWAP(arr, 48, temp) \
    COMPARE_AND_SWAP(arr, 49, temp) \
    COMPARE_AND_SWAP(arr, 50, temp) \
    COMPARE_AND_SWAP(arr, 51, temp) \
    COMPARE_AND_SWAP(arr, 52, temp) \
    COMPARE_AND_SWAP(arr, 53, temp) \
    COMPARE_AND_SWAP(arr, 54, temp) \
    COMPARE_AND_SWAP(arr, 55, temp) \
    COMPARE_AND_SWAP(arr, 56, temp) \
    COMPARE_AND_SWAP(arr, 57, temp) \
    COMPARE_AND_SWAP(arr, 58, temp) \
    COMPARE_AND_SWAP(arr, 59, temp) \
    COMPARE_AND_SWAP(arr, 60, temp) \
    COMPARE_AND_SWAP(arr, 61, temp) \
    COMPARE_AND_SWAP(arr, 62, temp) \
    COMPARE_AND_SWAP(arr, 63, temp) \
    COMPARE_AND_SWAP(arr, 64, temp) \
    COMPARE_AND_SWAP(arr, 65, temp) \
    COMPARE_AND_SWAP(arr, 66, temp) \
    COMPARE_AND_SWAP(arr, 67, temp) \
    COMPARE_AND_SWAP(arr, 68, temp) \
    COMPARE_AND_SWAP(arr, 69, temp) \
    COMPARE_AND_SWAP(arr, 70, temp) \
    COMPARE_AND_SWAP(arr, 71, temp) \
    COMPARE_AND_SWAP(arr, 72, temp) \
    COMPARE_AND_SWAP(arr, 73, temp) \
    COMPARE_AND_SWAP(arr, 74, temp) \
    COMPARE_AND_SWAP(arr, 75, temp) \
    COMPARE_AND_SWAP(arr, 76, temp) \
    COMPARE_AND_SWAP(arr, 77, temp) \
    COMPARE_AND_SWAP(arr, 78, temp) \
    COMPARE_AND_SWAP(arr, 79, temp) \

// 顶层宏定义用于调用每个 j 值的循环展开
#define FULL_BUBBLE_SORT(arr, temp) \
    BUBBLE_SORT_ITERATION(arr, 0, temp) \
    BUBBLE_SORT_ITERATION(arr, 1, temp) \
    BUBBLE_SORT_ITERATION(arr, 2, temp) \
    BUBBLE_SORT_ITERATION(arr, 3, temp) \
    BUBBLE_SORT_ITERATION(arr, 4, temp) \
    BUBBLE_SORT_ITERATION(arr, 5, temp) \
    BUBBLE_SORT_ITERATION(arr, 6, temp) \
    BUBBLE_SORT_ITERATION(arr, 7, temp) \
    BUBBLE_SORT_ITERATION(arr, 8, temp) \
    BUBBLE_SORT_ITERATION(arr, 9, temp) \
    BUBBLE_SORT_ITERATION(arr, 10, temp) \
    BUBBLE_SORT_ITERATION(arr, 11, temp) \
    BUBBLE_SORT_ITERATION(arr, 12, temp) \
    BUBBLE_SORT_ITERATION(arr, 13, temp) \
    BUBBLE_SORT_ITERATION(arr, 14, temp) \
    BUBBLE_SORT_ITERATION(arr, 15, temp) \
    BUBBLE_SORT_ITERATION(arr, 16, temp) \
    BUBBLE_SORT_ITERATION(arr, 17, temp) \
    BUBBLE_SORT_ITERATION(arr, 18, temp) \
    BUBBLE_SORT_ITERATION(arr, 19, temp) \
    BUBBLE_SORT_ITERATION(arr, 20, temp) \
    BUBBLE_SORT_ITERATION(arr, 21, temp) \
    BUBBLE_SORT_ITERATION(arr, 22, temp) \
    BUBBLE_SORT_ITERATION(arr, 23, temp) \
    BUBBLE_SORT_ITERATION(arr, 24, temp) \
    BUBBLE_SORT_ITERATION(arr, 25, temp) \
    BUBBLE_SORT_ITERATION(arr, 26, temp) \
    BUBBLE_SORT_ITERATION(arr, 27, temp) \
    BUBBLE_SORT_ITERATION(arr, 28, temp) \
    BUBBLE_SORT_ITERATION(arr, 29, temp) \
    BUBBLE_SORT_ITERATION(arr, 30, temp) \
    BUBBLE_SORT_ITERATION(arr, 31, temp) \
    BUBBLE_SORT_ITERATION(arr, 32, temp) \
    BUBBLE_SORT_ITERATION(arr, 33, temp) \
    BUBBLE_SORT_ITERATION(arr, 34, temp) \
    BUBBLE_SORT_ITERATION(arr, 35, temp) \
    BUBBLE_SORT_ITERATION(arr, 36, temp) \
    BUBBLE_SORT_ITERATION(arr, 37, temp) \
    BUBBLE_SORT_ITERATION(arr, 38, temp) \
    BUBBLE_SORT_ITERATION(arr, 39, temp) \
    BUBBLE_SORT_ITERATION(arr, 40, temp) \
    BUBBLE_SORT_ITERATION(arr, 41, temp) \
    BUBBLE_SORT_ITERATION(arr, 42, temp) \
    BUBBLE_SORT_ITERATION(arr, 43, temp) \
    BUBBLE_SORT_ITERATION(arr, 44, temp) \
    BUBBLE_SORT_ITERATION(arr, 45, temp) \
    BUBBLE_SORT_ITERATION(arr, 46, temp) \
    BUBBLE_SORT_ITERATION(arr, 47, temp) \
    BUBBLE_SORT_ITERATION(arr, 48, temp) \
    BUBBLE_SORT_ITERATION(arr, 49, temp) \
    BUBBLE_SORT_ITERATION(arr, 50, temp) \
    BUBBLE_SORT_ITERATION(arr, 51, temp) \
    BUBBLE_SORT_ITERATION(arr, 52, temp) \
    BUBBLE_SORT_ITERATION(arr, 53, temp) \
    BUBBLE_SORT_ITERATION(arr, 54, temp) \
    BUBBLE_SORT_ITERATION(arr, 55, temp) \
    BUBBLE_SORT_ITERATION(arr, 56, temp) \
    BUBBLE_SORT_ITERATION(arr, 57, temp) \
    BUBBLE_SORT_ITERATION(arr, 58, temp) \
    BUBBLE_SORT_ITERATION(arr, 59, temp) \
    BUBBLE_SORT_ITERATION(arr, 60, temp) \
    BUBBLE_SORT_ITERATION(arr, 61, temp) \
    BUBBLE_SORT_ITERATION(arr, 62, temp) \
    BUBBLE_SORT_ITERATION(arr, 63, temp) \
    BUBBLE_SORT_ITERATION(arr, 64, temp) \
    BUBBLE_SORT_ITERATION(arr, 65, temp) \
    BUBBLE_SORT_ITERATION(arr, 66, temp) \
    BUBBLE_SORT_ITERATION(arr, 67, temp) \
    BUBBLE_SORT_ITERATION(arr, 68, temp) \
    BUBBLE_SORT_ITERATION(arr, 69, temp) \
    BUBBLE_SORT_ITERATION(arr, 70, temp) \
    BUBBLE_SORT_ITERATION(arr, 71, temp) \
    BUBBLE_SORT_ITERATION(arr, 72, temp) \
    BUBBLE_SORT_ITERATION(arr, 73, temp) \
    BUBBLE_SORT_ITERATION(arr, 74, temp) \
    BUBBLE_SORT_ITERATION(arr, 75, temp) \
    BUBBLE_SORT_ITERATION(arr, 76, temp) \
    BUBBLE_SORT_ITERATION(arr, 77, temp) \
    BUBBLE_SORT_ITERATION(arr, 78, temp) \
    BUBBLE_SORT_ITERATION(arr, 79, temp)


void alg3_func(unsigned short * d1in, unsigned short  * d1out, unsigned int width, unsigned int height)
{
	int bArray[81] = {5, 1, 9, 3, 7, 4, 2, 6, 8, 0}; // 初始化部分数据，长度为81
    int temp;
	int * d1_c = (int *)malloc((width / 2) * (height / 2) * 4 * sizeof(int));
	int * d1_ce = (int*)malloc((width / 2 + 8) * (height / 2 + 8) * 4 * sizeof(int));

	unsigned int i, j;
	for (unsigned int k = 0; k < (height*width/4); k++)// ii = 1
	{
		if(k % (width/2) == 0 && k != 0)
			i++;
		j = k % (width/2);
		d1_c[i * width / 2 + j] = d1in[i * 2 * width + j * 2];
		d1_c[i * width / 2 + j + (width / 2) * (height / 2)] = d1in[i * 2 * width + j * 2 + 1];
		d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2] = d1in[(i * 2 + 1) * width + j * 2];
		d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3] = d1in[(i * 2 + 1) * width + j * 2 + 1];
	}

	unsigned int c = 0;i = 0;j = 0;
	//subloop1中心数据块
	for (int k = 0; k < 4 * (height/2) * (width/2); k++)
	{	
		c = k / ((height/2) * (width/2));
		i = (k / (width/2)) % (height/2);
		j = k % (width / 2);
		d1_ce[(4 + i) * (width / 2 + 8) + 4 + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[i *  width / 2 + j + c * (width / 2) * (height / 2)];
	}
	c = 0;i = 0;j = 0;
	//subloop2左侧边界填充
	for (int k = 0; k < 4 * (height/2) * 4; k++)
	{	
		c = k / (height/2);
		i = 4 + (k / 4) % (height/2);
		j = k % 4;
		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) *  width / 2 + c * (width / 2) * (height / 2)];
	}
	c = 0;i = 0;j = 0;
	//subloop3右侧边界填充
	for (int k = 0; k < 4 * (height/2) * 4; k++)
	{	
		c = k / (height/2);
		i = 4 + (k / 4) % (height/2);
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
	for (int k = 0; k < 4 * 4 * (width/2+8); k++)
	{	
		c = k / (4 * (width/2+8));
		i = height / 2 + 4 + (k / (width/2+8)) % 4;
		j = k % (width/2+8);
		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(height / 2 + 3) * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];
	}

	int MF_pixel_block[9 * 9] = { 0 };
		for (int k = 0; k < 4 * (height/2) * (width/2); k++)
		{	
			// c = k / ((height/2) * (width/2));
			if(k % ((height/2) * (width/2)) == 0 && k != 0)
				c++;
			i = 4 + (k / (width/2)) % 4;
			j = 4 + k % (width/2);		
				// for (int m = -4; m <= 4; m++)
				// 	for (int n = -4; n <= 4; n++)
				// 		MF_pixel_block[(m + 4) * 9 + n + 4] = d1_ce[(i + m) * (width / 2 + 8) + j + n + c * (width / 2 + 8) * (height / 2 + 8)];  
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
				{
					int MF_pixel_block_copy[81]; // 用于手动排序的临时副本
					unsigned char bTemp;

					// 复制 MF_pixel_block 到 MF_pixel_block_copy
					for (int idx = 0; idx < 81; idx++) {
						MF_pixel_block_copy[idx] = MF_pixel_block[idx];
					}

					// 排序
					FULL_BUBBLE_SORT(bArray, temp); // 使用宏完成冒泡排序

					// 手动排序所有元素后，根据奇偶性决定返回值
					if (81 % 2 == 1) { // 奇数个元素，取中间值
						bTemp = MF_pixel_block_copy[81 / 2];
					} else { // 偶数个元素，取中间两个元素的平均值
						bTemp = (MF_pixel_block_copy[81 / 2] + MF_pixel_block_copy[81 / 2 + 1]) / 2;
					}

					// 将结果赋值给 d1_c
					d1_c[(i - 4) * width / 2 + (j - 4) + c * (width / 2) * (height / 2)] = bTemp;
				}
	}

	i = 0;j = 0;
	for (unsigned int k = 0; k < (height*width/4); k++)// ii = 1
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