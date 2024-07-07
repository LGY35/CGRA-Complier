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
unsigned char alg3_func_1(unsigned int bArray[MF_KERNEL_TS*MF_KERNEL_TS], unsigned int iFilterLen)
{
	unsigned int i = 0, j = 1;  // Initialize i and j          
	unsigned char bTemp; 

	for (unsigned int k = 0; k < ((iFilterLen - 1) * (iFilterLen) / 2); k++) 
	{
		if (bArray[i] > bArray[i + 1]) {
			bTemp = bArray[i];
			bArray[i] = bArray[i + 1];
			bArray[i + 1] = bTemp;
		}
		i = (i + 1) % (iFilterLen - 1);  // Cycle i through 0 to iFilterLen-2
        j = (i + 1) % iFilterLen;        // Ensure j is always one ahead of i, wrapped around at iFilterLen
		// if (i < iFilterLen - j - 2) {
		// 	i++;
		// } else {
		// 	j++;
		// 	i = 0;
		// }
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
	unsigned int * d1_c = (unsigned int *)malloc((width / 2) * (height / 2) * 4 * sizeof(unsigned int));
	unsigned int * d1_ce = (unsigned int*)malloc((width / 2 + 8) * (height / 2 + 8) * 4 * sizeof(unsigned int));
	unsigned int i, j;
	for (unsigned int k = 0; k < (height*width/4); k++)// ii = 1
	{
		// i = k / (width/2);
		if(k % (width/2) == 0 && k != 0)
			i ++;
		j = k % (width/2);
		d1_c[i * width / 2 + j] = d1in[i * 2 * width + j * 2];
		d1_c[i * width / 2 + j + (width / 2) * (height / 2)] = d1in[i * 2 * width + j * 2 + 1];
		d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2] = d1in[(i * 2 + 1) * width + j * 2];
		d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3] = d1in[(i * 2 + 1) * width + j * 2 + 1];
	}

	i = 0, j = 0;
	unsigned int  c = 0;
	unsigned int line_start = 0, block_start = 0;
	unsigned int block_size = (height / 2) * (width / 2);

	// subloop1 中心数据块
	for (unsigned int k = 0; k < 4 * block_size; k++) {
		if (k != 0 && k % block_size == 0) {
			c++;
			line_start = k;
		}
		if (k != 0 && (k - line_start) % (width / 2) == 0 && k > line_start) {
			i++;
		}
		j = (k - line_start) % (width / 2);
		d1_ce[(4 + i) * (width / 2 + 8) + 4 + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[i * width / 2 + j + c * (width / 2) * (height / 2)];
		if (j == (width / 2) - 1) {
			line_start = k + 1;
			i = 0;
		}
	}
	c = 0;
	i = 0;
	j = 0;

	// subloop2 左侧边界填充
	for (unsigned int k = 0; k < 4 * (height / 2) * 4; k++) {
		if (k != 0 && k % (height / 2) == 0) {
			c++;
			line_start = k;
		}
		i = 4 + (k - line_start) / 4;
		j = k % 4;
		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) * width / 2 + c * (width / 2) * (height / 2)];
	}
	c = 0;
	i = 0;
	j = 0;

	// subloop3 右侧边界填充
	for (unsigned int k = 0; k < 4 * (height / 2) * 4; k++) {
		if (k != 0 && k % (height / 2) == 0) {
			c++;
			line_start = k;
		}
		i = 4 + (k - line_start) / 4;
		j = width / 2 + 4 + k % 4;
		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) * width / 2 + width / 2 - 1 + c * (width / 2) * (height / 2)];
	}
	c = 0;
	i = 0;
	j = 0;

	// subloop4 顶部边界填充
	for (unsigned int k = 0; k < 4 * 4 * (width / 2 + 8); k++) {
		if (k != 0 && k % (4 * (width / 2 + 8)) == 0) {
			c++;
			line_start = k;
		}
		i = (k - line_start) / (width / 2 + 8);
		j = k % (width / 2 + 8);
		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_ce[4 * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];
	}
	c = 0;
	i = 0;
	j = 0;

	// subloop5 底部边界填充
	for (unsigned int k = 0; k < 4 * 4 * (width / 2 + 8); k++) {
		if (k != 0 && k % (4 * (width / 2 + 8)) == 0) {
			c++;
			line_start = k;
		}
		i = height / 2 + 4 + (k - line_start) / (width / 2 + 8);
		j = k % (width / 2 + 8);
		d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_ce[(height / 2 + 3) * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];
	}

	unsigned int MF_pixel_block[9 * 9] = { 0 };
	c = 0;
	unsigned int m, n;
	line_start = 0, block_start = 0;
	unsigned int kernel_size = 81; // Kernel size (9x9)
	block_size = (height / 2) * (width / 2);
	unsigned int sub_block_size = block_size * kernel_size;
	unsigned int total_iterations = 4 * sub_block_size;
	unsigned int sub_block_start = 0;
	i = 0, j = 0;

	for (unsigned int k = 0; k < total_iterations; k++) {
		// Update 'c' for every new sub-block of the entire data set
		if (k != 0 && k % sub_block_size == 0) {
			c++;
			sub_block_start = k;
		}

		// Update 'i' for every new line of sub-block
		if (k != sub_block_start && (k - sub_block_start) % ((width / 2) * kernel_size) == 0) {
			line_start = k;
		}

		if (k != line_start && (k - line_start) % kernel_size == 0) {
			i++;
		}

		j = 4 + (k - line_start) / kernel_size % (width / 2); // Calculate 'j' based on position in the sub-block

		m = (k % 81) / 9 - 4; // Kernel row
		n = (k % 9) - 4; // Kernel column

		MF_pixel_block[(m + 4) * 9 + n + 4] = d1_ce[(4 + i + m) * (width / 2 + 8) + (4 + j + n) + c * (width / 2 + 8) * (height / 2 + 8)];
		
		// Finalize result for the current kernel application
		if (k % kernel_size == kernel_size - 1) {
			d1_c[(i - 4) * width / 2 + (j - 4) + c * (width / 2) * (height / 2)] = alg3_func_1(MF_pixel_block, 9 * 9);
		}

		// Reset i and line_start when finishing a line
		if (j == (width / 2) - 1 + 4) {
			line_start = k + 1;
			i = 0;
		}
	}

	for (unsigned int k = 0; k < (height*width/4); k++)// ii = 1
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