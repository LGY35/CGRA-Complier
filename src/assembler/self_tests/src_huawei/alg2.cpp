#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

typedef struct {
	unsigned int pLutS[15];
} alg2_register;

static void alg2_func_1(alg2_register *pLuts, unsigned int si)
{
	unsigned int sum = 0;
	unsigned int pLutArray[] = {
		(unsigned int)exp(-0 / (2 * si * si)), //change due to compilation error
		(unsigned int)exp(-1 / (2 * si * si)),
		(unsigned int)exp(-2 / (2 * si * si)),
		(unsigned int)exp(-4 / (2 * si * si)),
		(unsigned int)exp(-5 / (2 * si * si)),
		(unsigned int)exp(-8 / (2 * si * si)),
		(unsigned int)exp(-9 / (2 * si * si)),
		(unsigned int)exp(-10 / (2 * si * si)),
		(unsigned int)exp(-13 / (2 * si * si)),
		(unsigned int)exp(-18 / (2 * si * si)),
		(unsigned int)exp(-16 / (2 * si * si)),
		(unsigned int)exp(-17 / (2 * si * si)),
		(unsigned int)exp(-20 / (2 * si * si)),
		(unsigned int)exp(-25 / (2 * si * si)),
		(unsigned int)exp(-32 / (2 * si * si))
	};
	sum = sum + pLutArray[0] + pLutArray[1] * 4 + pLutArray[2] * 4 + pLutArray[3] * 4 + pLutArray[4] * 8 + pLutArray[5] * 4 + pLutArray[6] * 4 + pLutArray[7] * 8
		+ pLutArray[8] * 8 + pLutArray[9] * 4 + pLutArray[10] * 4 + pLutArray[11] * 8 + pLutArray[12] * 8 + pLutArray[13] * 8 + pLutArray[14] * 4;
	for (unsigned int i = 0; i < 15; i++)// ii = 1
	{
		pLutArray[i] = pLutArray[i] / sum;
	}
	for (unsigned int i = 0; i < 15; i++)// ii = 1
	{
		pLuts->pLutS[i] = round(pLutArray[i] * 1024);
	}
	return;
}


// void alg2_func(unsigned short* d1in, unsigned short* d1out, unsigned int width, unsigned int height,unsigned int si)
void alg2_func(unsigned int* d1in, unsigned int* d1out, unsigned int width, unsigned int height,unsigned int si)
{
	unsigned int * d1_c = (unsigned int *)malloc((width / 2) * (height / 2) * 4 * sizeof(unsigned int));
	unsigned int * d1_ce = (unsigned int*)malloc((width / 2 + 8) * (height / 2 + 8) * 4 * sizeof(unsigned int));
	// 优化1：双层
	unsigned int i = 0,j = 0;
	for (unsigned int k = 0; k < height * width / 4; k++)// ii = 2
	{
		if(k % (width/2) == 0 && k != 0)
			i ++;
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
	//subloop2左侧边界填充
	for (int k = 0; k < 4 * (height/2) * 4; k++)
	{	
		c = k / (height/2);
		i = 4 + (k / 4) % (height/2);
		j = k % 4;
		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) *  width / 2 + c * (width / 2) * (height / 2)];
	}
	//subloop3右侧边界填充
	for (int k = 0; k < 4 * (height/2) * 4; k++)
	{	
		c = k / (height/2);
		i = 4 + (k / 4) % (height/2);
		j = width / 2 + 4 + k % 4;
		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) *  width / 2 + width / 2 - 1 + c * (width / 2) * (height / 2)];
	}
	//subloop4顶部边界填充
	for (int k = 0; k < 4 * 4 * (width/2+8); k++)
	{	
		c = k / (4 * (width/2+8));
		i = (k / (width/2+8)) % 4;
		j = k % (width/2+8);
		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[4 * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];
	}
	//subloop5底部边界填充
	for (int k = 0; k < 4 * 4 * (width/2+8); k++)
	{	
		c = k / (4 * (width/2+8));
		i = height / 2 + 4 + (k / (width/2+8)) % 4;
		j = k % (width/2+8);
		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(height / 2 + 3) * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];
	}

	//============================================================================================================
	alg2_register alg2_kernel;//TODO: check
	// alg2_func_1(&alg2_kernel, si);
	unsigned int pLutArray[15];
	for (unsigned int i = 0; i < 15; i++) // ii = 1
	{
		pLutArray[i] = alg2_kernel.pLutS[i];
	}
	unsigned int kernel[9][9] = {
		{pLutArray[14], pLutArray[13], pLutArray[12], pLutArray[11], pLutArray[10], pLutArray[11], pLutArray[12], pLutArray[13], pLutArray[14]},
		{pLutArray[13], pLutArray[9],  pLutArray[8],  pLutArray[7],  pLutArray[6],  pLutArray[7],  pLutArray[8],  pLutArray[9],  pLutArray[13]},
		{pLutArray[12], pLutArray[8],  pLutArray[5],  pLutArray[4],  pLutArray[3],  pLutArray[4],  pLutArray[5],  pLutArray[8],  pLutArray[12]},
		{pLutArray[11], pLutArray[7],  pLutArray[4],  pLutArray[2],  pLutArray[1],  pLutArray[2],  pLutArray[4],  pLutArray[7],  pLutArray[11]},
		{pLutArray[10], pLutArray[6],  pLutArray[3],  pLutArray[1],  pLutArray[0],  pLutArray[1],  pLutArray[3],  pLutArray[6],  pLutArray[10]},
		{pLutArray[11], pLutArray[7],  pLutArray[4],  pLutArray[2],  pLutArray[1],  pLutArray[2],  pLutArray[4],  pLutArray[7],  pLutArray[11]},
		{pLutArray[12], pLutArray[8],  pLutArray[5],  pLutArray[4],  pLutArray[3],  pLutArray[4],  pLutArray[5],  pLutArray[8],  pLutArray[12]},
		{pLutArray[13], pLutArray[9],  pLutArray[8],  pLutArray[7],  pLutArray[6],  pLutArray[7],  pLutArray[8],  pLutArray[9],  pLutArray[13]},
		{pLutArray[14], pLutArray[13], pLutArray[12], pLutArray[11], pLutArray[10], pLutArray[11], pLutArray[12], pLutArray[13], pLutArray[14]}
	};

	c = 0;
	unsigned int result = 0;
	unsigned int m,n;
	for (unsigned int k = 0; k < 4 * (height*width/4) * 81; k++)// ii = 3
	{
		c = k / ((height / 2) * (width / 2) * 81);
		i = 4 + (k / ((width/2)* 81)) % (height/2);
		j = 4 + (k / 81) % (width/2);
		m = (k%81) / 9 - 4;
		n = (k%81) % 9 - 4;
		if(k%81 == 0) result = 0;	// 重置结果，每当开始处理新的像素时
		result += d1_ce[(i + m) * (width / 2 + 8) + j + n + c * (width / 2 + 8) * (height / 2 + 8)] * kernel[m + 4][n + 4];
		// //TODO: check
		// if(k%81 == 80)	// 最后一次迭代更新目标数组
		// 	d1_c[(i - 4) * width / 2 + (j - 4) + c * (width / 2) * (height / 2)] = result >> 10;
	}
	//================================================================		================================================================

	// 优化4：2层
	i = 0;j = 0;
	for (unsigned int k = 0; k < height*width / 4; k++)// ii = 1
	{
		if(k % (width/2) == 0 && k != 0)
			i ++;
		j = k % (width/2);
		d1out[i * 2 * width + j * 2] = d1_c[i * width / 2 + j];
		d1out[i * 2 * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2)];
		d1out[(i * 2 + 1) * width + j * 2] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2];
		d1out[(i * 2 + 1) * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3];
	}

	free(d1_c);
	free(d1_ce);
}

//  优化3：5层——未完全拆分完
	// for (int k = 0; k < 4 * (height*width/4); k++)// ii = 3
	// {
	// 	c = k / (height*width/4);
	// 	i = 4 + (k / (width/2)) % (height/2);
	// 	j = 4 + k % (width/2);
		
	// 	result = 0;
	// 	for(int kk1 = 0; kk1 < 81; kk1++)		//原始代码中 m 和 n 循环从 -4 到 4，覆盖了 9×9 的范围。
	// 	{
	// 		m = kk1 / 9 - 4;
    //     	n = kk1 % 9 - 4;
	// 		result += d1_ce[(i + m) * (width / 2 + 8) + j + n + c * (width / 2 + 8) * (height / 2 + 8)] * kernel[m + 4][n + 4];
	// 	}
	// 	d1_c[(i - 4) * width / 2 + (j - 4) + c * (width / 2) * (height / 2)] = result >> 10;
	// }


//================================== original code

// static void alg2_func_1(alg2_register *pLuts, float si)
// {
// 	float sum = 0;
// 	float pLutArray[] = {
// 		(float)exp(-0 / (2 * si * si)), //change due to compilation error
// 		(float)exp(-1 / (2 * si * si)),
// 		(float)exp(-2 / (2 * si * si)),
// 		(float)exp(-4 / (2 * si * si)),
// 		(float)exp(-5 / (2 * si * si)),
// 		(float)exp(-8 / (2 * si * si)),
// 		(float)exp(-9 / (2 * si * si)),
// 		(float)exp(-10 / (2 * si * si)),
// 		(float)exp(-13 / (2 * si * si)),
// 		(float)exp(-18 / (2 * si * si)),
// 		(float)exp(-16 / (2 * si * si)),
// 		(float)exp(-17 / (2 * si * si)),
// 		(float)exp(-20 / (2 * si * si)),
// 		(float)exp(-25 / (2 * si * si)),
// 		(float)exp(-32 / (2 * si * si))
// 	};
// 	sum = sum + pLutArray[0] + pLutArray[1] * 4 + pLutArray[2] * 4 + pLutArray[3] * 4 + pLutArray[4] * 8 + pLutArray[5] * 4 + pLutArray[6] * 4 + pLutArray[7] * 8
// 		+ pLutArray[8] * 8 + pLutArray[9] * 4 + pLutArray[10] * 4 + pLutArray[11] * 8 + pLutArray[12] * 8 + pLutArray[13] * 8 + pLutArray[14] * 4;
// 	for (int i = 0; i < 15; i++)// ii = 1
// 	{
// 		pLutArray[i] = pLutArray[i] / sum;
// 	}
// 	for (int i = 0; i < 15; i++)// ii = 1
// 	{
// 		pLuts->pLutS[i] = round(pLutArray[i] * 1024);
// 	}
// 	return;
// }


// void alg2_func(unsigned short* d1in, unsigned short* d1out, unsigned int width, unsigned int height,float si)
// {
// 	int * d1_c = (int *)malloc((width / 2) * (height / 2) * 4 * sizeof(int));
// 	int * d1_ce = (int*)malloc((width / 2 + 8) * (height / 2 + 8) * 4 * sizeof(int));
// 	for (int i = 0; i < height / 2; i++)// ii = 2
// 	{
// 		for (int j = 0; j < width / 2; j++)
// 		{
// 			d1_c[i * width / 2 + j] = d1in[i * 2 * width + j * 2];
// 			d1_c[i * width / 2 + j + (width / 2) * (height / 2)] = d1in[i * 2 * width + j * 2 + 1];
// 			d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2] = d1in[(i * 2 + 1) * width + j * 2];
// 			d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3] = d1in[(i * 2 + 1) * width + j * 2 + 1];
// 		}
// 	}

// 	for (int c = 0; c < 4; c++) // ii = 3
// 	{
		
// 		for (int i = 0; i < height / 2; i++)
// 			for (int j = 0; j < width / 2; j++)
// 				d1_ce[(4 + i) * (width / 2 + 8) + 4 + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[i *  width / 2 + j + c * (width / 2) * (height / 2)];

		
// 		for (int i = 4; i < height / 2 + 4; i++)
// 			for (int j = 0; j < 4; j++)
// 				d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) *  width / 2 + c * (width / 2) * (height / 2)];

		
// 		for (int i = 4; i < height / 2 + 4; i++)
// 			for (int j = width / 2 + 4; j < width / 2 + 8; j++)
// 				d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) *  width / 2 + width / 2 - 1 + c * (width / 2) * (height / 2)];

		
// 		for (int i = 0; i < 4; i++)
// 			for (int j = 0; j < width / 2 + 8; j++)
// 				d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_ce[4 * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];

		
// 		for (int i = height / 2 + 4; i < height / 2 + 8; i++)
// 			for (int j = 0; j < width / 2 + 8; j++)
// 				d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_ce[(height / 2 + 3) * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];
// 	}

// 	alg2_register alg2_kernel;
// 	alg2_func_1(&alg2_kernel, si);
// 	int pLutArray[15];
// 	for (int i = 0; i < 15; i++) // ii = 1
// 	{
// 		pLutArray[i] = alg2_kernel.pLutS[i];
// 	}
// 	int kernel[9][9] = {
// 		{pLutArray[14], pLutArray[13], pLutArray[12], pLutArray[11], pLutArray[10], pLutArray[11], pLutArray[12], pLutArray[13], pLutArray[14]},
// 		{pLutArray[13], pLutArray[9],  pLutArray[8],  pLutArray[7],  pLutArray[6],  pLutArray[7],  pLutArray[8],  pLutArray[9],  pLutArray[13]},
// 		{pLutArray[12], pLutArray[8],  pLutArray[5],  pLutArray[4],  pLutArray[3],  pLutArray[4],  pLutArray[5],  pLutArray[8],  pLutArray[12]},
// 		{pLutArray[11], pLutArray[7],  pLutArray[4],  pLutArray[2],  pLutArray[1],  pLutArray[2],  pLutArray[4],  pLutArray[7],  pLutArray[11]},
// 		{pLutArray[10], pLutArray[6],  pLutArray[3],  pLutArray[1],  pLutArray[0],  pLutArray[1],  pLutArray[3],  pLutArray[6],  pLutArray[10]},
// 		{pLutArray[11], pLutArray[7],  pLutArray[4],  pLutArray[2],  pLutArray[1],  pLutArray[2],  pLutArray[4],  pLutArray[7],  pLutArray[11]},
// 		{pLutArray[12], pLutArray[8],  pLutArray[5],  pLutArray[4],  pLutArray[3],  pLutArray[4],  pLutArray[5],  pLutArray[8],  pLutArray[12]},
// 		{pLutArray[13], pLutArray[9],  pLutArray[8],  pLutArray[7],  pLutArray[6],  pLutArray[7],  pLutArray[8],  pLutArray[9],  pLutArray[13]},
// 		{pLutArray[14], pLutArray[13], pLutArray[12], pLutArray[11], pLutArray[10], pLutArray[11], pLutArray[12], pLutArray[13], pLutArray[14]}
// 	};

// 	int result = 0;
// 	for (int c = 0; c < 4; c++)// ii = 3
// 	{
// 		for (int i = 4; i < height / 2 + 4; i++)
// 		{
// 			for (int j = 4; j < width / 2 + 4; j++)
// 			{
// 				result = 0;
// 				for (int m = -4; m <= 4; m++)
// 					for (int n = -4; n <= 4; n++)
// 						result += d1_ce[(i + m) * (width / 2 + 8) + j + n + c * (width / 2 + 8) * (height / 2 + 8)] * kernel[m + 4][n + 4];

// 				d1_c[(i - 4) * width / 2 + (j - 4) + c * (width / 2) * (height / 2)] = result >> 10;
// 			}
// 		}
// 	}


// 	for (int i = 0; i < height / 2; i++)// ii = 1
// 	{
// 		for (int j = 0; j < width / 2; j++)
// 		{
// 			d1out[i * 2 * width + j * 2] = d1_c[i * width / 2 + j];
// 			d1out[i * 2 * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2)];
// 			d1out[(i * 2 + 1) * width + j * 2] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2];
// 			d1out[(i * 2 + 1) * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3];
// 		}
// 	}

// 	free(d1_c);
// 	free(d1_ce);
// }








//============================================ float 
// #include <assert.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <cmath>

// typedef struct {
// 	int pLutS[15];
// } alg2_register;

// static void alg2_func_1(alg2_register *pLuts, float si)
// {
// 	float sum = 0;
// 	float pLutArray[] = {
// 		(float)exp(-0 / (2 * si * si)), //change due to compilation error
// 		(float)exp(-1 / (2 * si * si)),
// 		(float)exp(-2 / (2 * si * si)),
// 		(float)exp(-4 / (2 * si * si)),
// 		(float)exp(-5 / (2 * si * si)),
// 		(float)exp(-8 / (2 * si * si)),
// 		(float)exp(-9 / (2 * si * si)),
// 		(float)exp(-10 / (2 * si * si)),
// 		(float)exp(-13 / (2 * si * si)),
// 		(float)exp(-18 / (2 * si * si)),
// 		(float)exp(-16 / (2 * si * si)),
// 		(float)exp(-17 / (2 * si * si)),
// 		(float)exp(-20 / (2 * si * si)),
// 		(float)exp(-25 / (2 * si * si)),
// 		(float)exp(-32 / (2 * si * si))
// 	};
// 	sum = sum + pLutArray[0] + pLutArray[1] * 4 + pLutArray[2] * 4 + pLutArray[3] * 4 + pLutArray[4] * 8 + pLutArray[5] * 4 + pLutArray[6] * 4 + pLutArray[7] * 8
// 		+ pLutArray[8] * 8 + pLutArray[9] * 4 + pLutArray[10] * 4 + pLutArray[11] * 8 + pLutArray[12] * 8 + pLutArray[13] * 8 + pLutArray[14] * 4;
// 	for (int i = 0; i < 15; i++)// ii = 1
// 	{
// 		pLutArray[i] = pLutArray[i] / sum;
// 	}
// 	for (int i = 0; i < 15; i++)// ii = 1
// 	{
// 		pLuts->pLutS[i] = round(pLutArray[i] * 1024);
// 	}
// 	return;
// }


// void alg2_func(unsigned short* d1in, unsigned short* d1out, unsigned int width, unsigned int height,float si)
// {
// 	int * d1_c = (int *)malloc((width / 2) * (height / 2) * 4 * sizeof(int));
// 	int * d1_ce = (int*)malloc((width / 2 + 8) * (height / 2 + 8) * 4 * sizeof(int));
// 	// 优化1：双层
// 	int i = 0,j = 0;
// 	for (int k = 0; k < height * width / 4; k++)// ii = 2
// 	{
// 		i = k / (width/2);
// 		j = k % (width/2);
// 		d1_c[i * width / 2 + j] = d1in[i * 2 * width + j * 2];
// 		d1_c[i * width / 2 + j + (width / 2) * (height / 2)] = d1in[i * 2 * width + j * 2 + 1];
// 		d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2] = d1in[(i * 2 + 1) * width + j * 2];
// 		d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3] = d1in[(i * 2 + 1) * width + j * 2 + 1];
// 	}

// 	// 优化2：3层
// 	int c = 0;i = 0;j = 0;
// 	//subloop1中心数据块
// 	for (int k = 0; k < 4 * (height/2) * (width/2); k++)
// 	{	
// 		c = k / ((height/2) * (width/2));
// 		i = (k / (width/2)) % (height/2);
// 		j = k % (width / 2);
// 		d1_ce[(4 + i) * (width / 2 + 8) + 4 + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[i *  width / 2 + j + c * (width / 2) * (height / 2)];
// 	}
// 	//subloop2左侧边界填充
// 	for (int k = 0; k < 4 * (height/2) * 4; k++)
// 	{	
// 		c = k / (height/2);
// 		i = 4 + (k / 4) % (height/2);
// 		j = k % 4;
// 		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) *  width / 2 + c * (width / 2) * (height / 2)];
// 	}
// 	//subloop3右侧边界填充
// 	for (int k = 0; k < 4 * (height/2) * 4; k++)
// 	{	
// 		c = k / (height/2);
// 		i = 4 + (k / 4) % (height/2);
// 		j = width / 2 + 4 + k % 4;
// 		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) *  width / 2 + width / 2 - 1 + c * (width / 2) * (height / 2)];
// 	}
// 	//subloop4顶部边界填充
// 	for (int k = 0; k < 4 * 4 * (width/2+8); k++)
// 	{	
// 		c = k / (4 * (width/2+8));
// 		i = (k / (width/2+8)) % 4;
// 		j = k % (width/2+8);
// 		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_ce[4 * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];
// 	}
// 	//subloop5底部边界填充
// 	for (int k = 0; k < 4 * 4 * (width/2+8); k++)
// 	{	
// 		c = k / (4 * (width/2+8));
// 		i = height / 2 + 4 + (k / (width/2+8)) % 4;
// 		j = k % (width/2+8);
// 		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_ce[(height / 2 + 3) * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];
// 	}

// 	alg2_register alg2_kernel;
// 	alg2_func_1(&alg2_kernel, si);
// 	int pLutArray[15];
// 	for (int i = 0; i < 15; i++) // ii = 1
// 	{
// 		pLutArray[i] = alg2_kernel.pLutS[i];
// 	}
// 	int kernel[9][9] = {
// 		{pLutArray[14], pLutArray[13], pLutArray[12], pLutArray[11], pLutArray[10], pLutArray[11], pLutArray[12], pLutArray[13], pLutArray[14]},
// 		{pLutArray[13], pLutArray[9],  pLutArray[8],  pLutArray[7],  pLutArray[6],  pLutArray[7],  pLutArray[8],  pLutArray[9],  pLutArray[13]},
// 		{pLutArray[12], pLutArray[8],  pLutArray[5],  pLutArray[4],  pLutArray[3],  pLutArray[4],  pLutArray[5],  pLutArray[8],  pLutArray[12]},
// 		{pLutArray[11], pLutArray[7],  pLutArray[4],  pLutArray[2],  pLutArray[1],  pLutArray[2],  pLutArray[4],  pLutArray[7],  pLutArray[11]},
// 		{pLutArray[10], pLutArray[6],  pLutArray[3],  pLutArray[1],  pLutArray[0],  pLutArray[1],  pLutArray[3],  pLutArray[6],  pLutArray[10]},
// 		{pLutArray[11], pLutArray[7],  pLutArray[4],  pLutArray[2],  pLutArray[1],  pLutArray[2],  pLutArray[4],  pLutArray[7],  pLutArray[11]},
// 		{pLutArray[12], pLutArray[8],  pLutArray[5],  pLutArray[4],  pLutArray[3],  pLutArray[4],  pLutArray[5],  pLutArray[8],  pLutArray[12]},
// 		{pLutArray[13], pLutArray[9],  pLutArray[8],  pLutArray[7],  pLutArray[6],  pLutArray[7],  pLutArray[8],  pLutArray[9],  pLutArray[13]},
// 		{pLutArray[14], pLutArray[13], pLutArray[12], pLutArray[11], pLutArray[10], pLutArray[11], pLutArray[12], pLutArray[13], pLutArray[14]}
// 	};

// 	c = 0;
// 	int result = 0;
// 	int m,n;
// 	for (int k = 0; k < 4 * (height*width/4) * 81; k++)// ii = 3
// 	{
// 		c = k / ((height / 2) * (width / 2) * 81);
// 		i = 4 + (k / ((width/2)* 81)) % (height/2);
// 		j = 4 + (k / 81) % (width/2);
// 		m = (k%81) / 9 - 4;
// 		n = (k%81) % 9 - 4;

// 		if(k%81 == 0) result = 0;	// 重置结果，每当开始处理新的像素时
// 		result += d1_ce[(i + m) * (width / 2 + 8) + j + n + c * (width / 2 + 8) * (height / 2 + 8)] * kernel[m + 4][n + 4];
// 		if(k%81 == 80)	// 最后一次迭代更新目标数组
// 		d1_c[(i - 4) * width / 2 + (j - 4) + c * (width / 2) * (height / 2)] = result >> 10;
// 	}
	
// 	// 优化4：2层
// 	i = 0;j = 0;
// 	for (int k = 0; k < height*width / 4; k++)// ii = 1
// 	{
// 		i = k / (width/2);
// 		j = k % (width/2);
// 		d1out[i * 2 * width + j * 2] = d1_c[i * width / 2 + j];
// 		d1out[i * 2 * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2)];
// 		d1out[(i * 2 + 1) * width + j * 2] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2];
// 		d1out[(i * 2 + 1) * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3];
// 	}

// 	free(d1_c);
// 	free(d1_ce);
// }

