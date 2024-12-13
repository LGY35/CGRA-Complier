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
	int i = 0, j = 0;            
	unsigned char bTemp; 

	// for (int k = 0; k < ((iFilterLen - 1) * (iFilterLen) / 2); k++) 
	// {
	// 	i = k % (iFilterLen-1);
	// 	j = k / (iFilterLen-1);  
		
	// 	//TODO: check 
	// 	if(i < (iFilterLen-1-j))
	// 	{
	// 		if (bArray[i] > bArray[i + 1]) {
	// 			bTemp = bArray[i];
	// 			bArray[i] = bArray[i + 1];
	// 			bArray[i + 1] = bTemp;
	// 		}
	// 	}
	// }
	if ((iFilterLen & 1) > 0)	{
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else{
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}
	return bTemp;
}
	unsigned int width_, height_;
	unsigned int * d1_c = (unsigned int *)malloc((width_ / 2) * (height_ / 2) * 4 * sizeof(unsigned int));
	unsigned int * d1_ce = (unsigned int*)malloc((width_ / 2 + 8) * (height_ / 2 + 8) * 4 * sizeof(unsigned int));
// void alg3_func(unsigned short * d1in, unsigned short  * d1out, unsigned int width, unsigned int height)
void alg3_func(unsigned int * d1in, unsigned int  * d1out, unsigned int width, unsigned int height)
{
	unsigned int i, j;
	width_ = width;
	height_ = height;
	// for (unsigned int k = 0; k < (height*width/4); k++)// ii = 1
	// {
	// 	if(k % (width/2) == 0 && k != 0)
	// 		i++;
	// 	j = k % (width/2);
	// 	d1_c[i * width / 2 + j] = d1in[i * 2 * width + j * 2];
	// 	d1_c[i * width / 2 + j + (width / 2) * (height / 2)] = d1in[i * 2 * width + j * 2 + 1];
	// 	d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2] = d1in[(i * 2 + 1) * width + j * 2];
	// 	d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3] = d1in[(i * 2 + 1) * width + j * 2 + 1];
	// }

	unsigned int c = 0;i = 0;j = 0;
	// //subloop1中心数据块
	// for (int k = 0; k < 4 * (height/2) * (width/2); k++)
	// {	
	// 	c = k / ((height/2) * (width/2));
	// 	i = (k / (width/2)) % (height/2);
	// 	j = k % (width / 2);
	// 	d1_ce[(4 + i) * (width / 2 + 8) + 4 + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[i *  width / 2 + j + c * (width / 2) * (height / 2)];
	// }
	// c = 0;i = 0;j = 0;
	// //subloop2左侧边界填充
	// for (int k = 0; k < 4 * (height/2) * 4; k++)
	// {	
	// 	c = k / (height/2);
	// 	i = 4 + (k / 4) % (height/2);
	// 	j = k % 4;
	// 	d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) *  width / 2 + c * (width / 2) * (height / 2)];
	// }
	// c = 0;i = 0;j = 0;
	// //subloop3右侧边界填充
	// for (int k = 0; k < 4 * (height/2) * 4; k++)
	// {	
	// 	c = k / (height/2);
	// 	i = 4 + (k / 4) % (height/2);
	// 	j = width / 2 + 4 + k % 4;
	// 	d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(i - 4) *  width / 2 + width / 2 - 1 + c * (width / 2) * (height / 2)];
	// }
	// c = 0;i = 0;j = 0;
	// //subloop4顶部边界填充
	// for (int k = 0; k < 4 * 4 * (width/2+8); k++)
	// {	
	// 	// c = k / (4 * (width/2+8));
	// 	if(k % (4 * (width/2+8)) == 0 && k != 0)
	// 		c++; 
	// 	// i = (k / (width/2+8)) % 4;
	// 	if(k % (width/2+8) == 0 && k != 0)
	// 		i++;
	// 	j = k % (width/2+8);
	// 	d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[4 * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];
	// }
	// c = 0;i = 0;j = 0;
	// //subloop5底部边界填充
	// for (int k = 0; k < 4 * 4 * (width/2+8); k++)
	// {	
	// 	c = k / (4 * (width/2+8));
	// 	i = height / 2 + 4 + (k / (width/2+8)) % 4;
	// 	j = k % (width/2+8);
	// 	d1_ce[i * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)] = d1_c[(height / 2 + 3) * (width / 2 + 8) + j + c * (width / 2 + 8) * (height / 2 + 8)];
	// }

	int MF_pixel_block[9 * 9] = { 0 };
	for (int k = 0; k < 4 * (height/2) * (width/2); k++)
	{	
		// c = k / ((height/2) * (width/2));
		if(k % ((height/2) * (width/2)) == 0 && k != 0)
			c++;
		i = 4 + (k / (width/2)) % 4;
		j = 4 + k % (width/2);		
		int m = -4,n = -4;
		for(int inner_k = 0; inner_k < 81;inner_k++)
		{
			m = inner_k / 9 - 4;
            n = inner_k % 9 - 4;
            MF_pixel_block[(m + 4) * 9 + n + 4] = d1_ce[(i + m) * (width / 2 + 8) + j + n + c * (width / 2 + 8) * (height / 2 + 8)];  
		}
		//TODO: check
		d1_c[(i - 4) * width / 2 + (j - 4) + c * (width / 2) * (height / 2)] = alg3_func_1(MF_pixel_block, 9 * 9);
	}

	// i = 0;j = 0;
	// for (unsigned int k = 0; k < (height*width/4); k++)// ii = 1
	// {
	// 	if(k % (width/2) == 0 && k != 0)
	// 		i++;
	// 	j = k % (width/2);//TODO: check
	// 	d1out[i * 2 * width + j * 2] = d1_c[i * width / 2 + j];
	// 	d1out[i * 2 * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2)];
	// 	d1out[(i * 2 + 1) * width + j * 2] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2];
	// 	d1out[(i * 2 + 1) * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3];
	// }
	// free(d1_c);
	// free(d1_ce);
}