#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

typedef struct {
	int pLutS[15];
} alg2_register;

static void alg2_func_1(alg2_register *pLuts, float si)
{
	float sum = 0;
	float pLutArray[] = {
		float(exp(-0 / (2 * si * si))),
		float(exp(-1 / (2 * si * si))),
		float(exp(-2 / (2 * si * si))),
		float(exp(-4 / (2 * si * si))),
		float(exp(-5 / (2 * si * si))),
		float(exp(-8 / (2 * si * si))),
		float(exp(-9 / (2 * si * si))),
		float(exp(-10 / (2 * si * si))),
		float(exp(-13 / (2 * si * si))),
		float(exp(-18 / (2 * si * si))),
		float(exp(-16 / (2 * si * si))),
		float(exp(-17 / (2 * si * si))),
		float(exp(-20 / (2 * si * si))),
		float(exp(-25 / (2 * si * si))),
		float(exp(-32 / (2 * si * si)))
	};
	sum = sum + pLutArray[0] + pLutArray[1] * 4 + pLutArray[2] * 4 + pLutArray[3] * 4 + pLutArray[4] * 8 + pLutArray[5] * 4 + pLutArray[6] * 4 + pLutArray[7] * 8
		+ pLutArray[8] * 8 + pLutArray[9] * 4 + pLutArray[10] * 4 + pLutArray[11] * 8 + pLutArray[12] * 8 + pLutArray[13] * 8 + pLutArray[14] * 4;
	for (int i = 0; i < 15; i++)
	{
		pLutArray[i] = pLutArray[i] / sum;
	}
	for (int i = 0; i < 15; i++)
	{
		pLuts->pLutS[i] = round(pLutArray[i] * 1024);
	}
	return;
}


void alg2_func(unsigned short* d1in, unsigned short* d1out, unsigned int width, unsigned int height,float si)
{
	int * d1_c = (int *)malloc((width / 2) * (height / 2) * 4 * sizeof(int));
	int * d1_ce = (int*)malloc((width / 2 + 8) * (height / 2 + 8) * 4 * sizeof(int));
	for (int i = 0; i <  (int)height / 2; i++)
	{
		for (int j = 0; j <  (int)width / 2; j++)
		{
			d1_c[i * width / 2 + j] = d1in[i * 2 * width + j * 2];
			d1_c[i * width / 2 + j + (width / 2) * (height / 2)] = d1in[i * 2 * width + j * 2 + 1];
			d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2] = d1in[(i * 2 + 1) * width + j * 2];
			d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3] = d1in[(i * 2 + 1) * width + j * 2 + 1];
		}
	}

	for (int c = 0; c < 4; c++)           
	{
		
		for (int i = 0; i <  (int)height / 2; i++)
			for (int j = 0; j <  (int)width / 2; j++)
				d1_ce[(4 + i) * (width / 2 + 8) + 4 + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[i *  width / 2 + j + c * (width / 2) * (height / 2)];

		
		for (int i = 4; i <  (int)height / 2 + 4; i++)
			for (int j = 0; j < 4; j++)
				d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) *  width / 2 + c * (width / 2) * (height / 2)];

		
		for (int i = 4; i <  (int)height / 2 + 4; i++)
			for (int j = width / 2 + 4; j < (int) width / 2 + 8; j++)
				d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) *  width / 2 + width / 2 - 1 + c * (width / 2) * (height / 2)];

		
		for (int i = 0; i < 4; i++)
			for (int j = 0; j <  (int)width / 2 + 8; j++)
				d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_ce[4 * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];

		
		for (int i = height / 2 + 4; i <  (int)height / 2 + 8; i++)
			for (int j = 0; j <  (int)width / 2 + 8; j++)
				d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_ce[(height / 2 + 3) * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];
	}

	alg2_register alg2_kernel;
	alg2_func_1(&alg2_kernel, si);
	int pLutArray[15];
	for (int i = 0; i < 15; i++)
	{
		pLutArray[i] = alg2_kernel.pLutS[i];
	}
	int kernel[9][9] = {
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

	int result = 0;
	for (int c = 0; c < 4; c++)
	{
		for (int i = 4; i <  (int)height / 2 + 4; i++)
		{
			for (int j = 4; j <  (int)width / 2 + 4; j++)
			{
				result = 0;
				for (int m = -4; m <= 4; m++)
					for (int n = -4; n <= 4; n++)
						result += d1_ce[(i + m) * (width / 2 + 8) + j + n + c * (width / 2 + 8) * (height / 2 + 8)] * kernel[m + 4][n + 4];

				d1_c[(i - 4) * width / 2 + (j - 4) + c * (width / 2) * (height / 2)] = result >> 10;
			}
		}
	}


	for (int i = 0; i <  (int)height / 2; i++)
	{
		for (int j = 0; j <  (int)width / 2; j++)
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
