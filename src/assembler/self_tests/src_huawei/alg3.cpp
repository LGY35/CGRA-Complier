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
unsigned char alg3_func_1(int bArray[MF_KERNEL_TS*MF_KERNEL_TS], int iFilterLen)
{
	int     i, j;            
	unsigned char bTemp; 
	for (j = 0; j < iFilterLen - 1; j++){
		for (i = 0; i < iFilterLen - j - 1; i++){
			if (bArray[i] > bArray[i + 1]){ 
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}
	if ((iFilterLen & 1) > 0)	{
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else{
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}
	return bTemp;
}
void alg3_func(unsigned short * d1in, unsigned short  * d1out, unsigned int width, unsigned int height)
{
	int * d1_c = (int *)malloc((width / 2) * (height / 2) * 4 * sizeof(int));
	int * d1_ce = (int*)malloc((width / 2 + 8) * (height / 2 + 8) * 4 * sizeof(int));
	for (int i = 0; i < height / 2; i++)
	{
		for (int j = 0; j < width / 2; j++)
		{
			d1_c[i * width / 2 + j] = d1in[i * 2 * width + j * 2];
			d1_c[i * width / 2 + j + (width / 2) * (height / 2)] = d1in[i * 2 * width + j * 2 + 1];
			d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2] = d1in[(i * 2 + 1) * width + j * 2];
			d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3] = d1in[(i * 2 + 1) * width + j * 2 + 1];
		}
	}
	for (int c = 0; c < 4; c++)       
	{

		for (int i = 0; i < height / 2; i++)
			for (int j = 0; j < width / 2; j++)
				d1_ce[(4 + i) * (width / 2 + 8) + 4 + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[i *  width / 2 + j + c * (width / 2) * (height / 2)];

		for (int i = 4; i < height / 2 + 4; i++)
			for (int j = 0; j < 4; j++)
				d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) *  width / 2 + c * (width / 2) * (height / 2)];

		for (int i = 4; i < height / 2 + 4; i++)
			for (int j = width / 2 + 4; j < width / 2 + 8; j++)
				d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) *  width / 2 + width / 2 - 1 + c * (width / 2) * (height / 2)];

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < width / 2 + 8; j++)
				d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_ce[4 * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];

		for (int i = height / 2 + 4; i < height / 2 + 8; i++)
			for (int j = 0; j < width / 2 + 8; j++)
				d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_ce[(height / 2 + 3) * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];
	}

	int MF_pixel_block[9 * 9] = { 0 };
	for (int c = 0; c < 4; c++)
	{
		for (int i = 4; i < height / 2 + 4; i++)
		{
			for (int j = 4; j < width / 2 + 4; j++)
			{
				for (int m = -4; m <= 4; m++)
					for (int n = -4; n <= 4; n++)
						MF_pixel_block[(m + 4) * 9 + n + 4] = d1_ce[(i + m) * (width / 2 + 8) + j + n + c * (width / 2 + 8) * (height / 2 + 8)];  
				d1_c[(i - 4) * width / 2 + (j - 4) + c * (width / 2) * (height / 2)] = alg3_func_1(MF_pixel_block, 9 * 9);
			}
		}
	}

	for (int i = 0; i < height / 2; i++)
	{
		for (int j = 0; j < width / 2; j++)
		{
			d1out[i * 2 * width + j * 2] = d1_c[i * width / 2 + j];
			d1out[i * 2 * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2)];
			d1out[(i * 2 + 1) * width + j * 2] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2];
			d1out[(i * 2 + 1) * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3];
		}
	}
	free(d1_c);
	free(d1_ce);
}