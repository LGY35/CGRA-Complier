#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// static unsigned int tnr_div64(unsigned int in, unsigned int *out, unsigned int *shft)
// {
// 	unsigned int nbit, idx, delta;
// 	const unsigned short INV_TAB64A[65] = { 0x1FFF, 0x1FFF, 0x1000, 0x0AAA, 0x0800, 0x0666, 0x0555, 0x0492,
// 		0x0400, 0x038E, 0x0333, 0x02E9, 0x02AB, 0x0276, 0x0249, 0x0222,
// 		0x0200, 0x01E2, 0x01C7, 0x01AF, 0x019A, 0x0186, 0x0174, 0x0164,
// 		0x0155, 0x0148, 0x013B, 0x012F, 0x0125, 0x011A, 0x0111, 0x0108,
// 		0x0100, 0x00F8, 0x00F1, 0x00EA, 0x00E4, 0x00DD, 0x00D8, 0x00D2,
// 		0x00CD, 0x00C8, 0x00C3, 0x00BE, 0x00BA, 0x00B6, 0x00B2, 0x00AE,
// 		0x00AB, 0x00A7, 0x00A4, 0x00A1, 0x009E, 0x009B, 0x0098, 0x0095,
// 		0x0092, 0x0090, 0x008D, 0x008B, 0x0089, 0x0086, 0x0084, 0x0082, 0x0080 };
// 	unsigned short *INV_TAB64 = (unsigned short *)&INV_TAB64A[0];
// 	for (int i = 25; i >= 0; i--)  
// 	{
// 		if (((in >> i) & 0x01) != 0)
// 		{
// 			nbit = i + 1;
// 			break;
// 		}
// 	}
// 	if (in <= 63)
// 	{
// 		*out = INV_TAB64[in];
// 		*shft = 0;
// 	}
// 	else
// 	{
// 		idx = in >> (nbit - 6);
// 		*out = INV_TAB64[idx];
// 		*shft = nbit - 6;
// 	}
// 	return 0;
// }
void alg4_func(unsigned short * d1in, unsigned short  * d1out, unsigned int width, unsigned int height)
{
	int * d1_c = (int *)malloc(((width / 2)) * (height / 2) * 4 * sizeof(int));
	int * d1_ce = (int*)malloc(((width / 2) + 12) * (height / 2 + 12) * 4 * sizeof(int));
	int i = 0,j = 0;
		
	for ( int k = 0; k < (height*width/4); k++)// ii = 1
	{
		// if(k % (width/2) == 0 && k != 0)
		// 	i++;
		i = k / (width/2);
		j = k % (width/2);
		d1_c[i * (width / 2) + j] = d1in[i * 2 * width + j * 2];
		d1_c[i * (width / 2) + j + ((width / 2)) * (height / 2)] = d1in[i * 2 * width + j * 2 + 1];
		d1_c[i * (width / 2) + j + ((width / 2)) * (height / 2) * 2] = d1in[(i * 2 + 1) * width + j * 2];
		d1_c[i * (width / 2) + j + ((width / 2)) * (height / 2) * 3] = d1in[(i * 2 + 1) * width + j * 2 + 1];
	}

	 int c = 0;i = 0;j = 0;
	//subloop1中心数据块
	for ( int k = 0; k < 4 * (height/2) * (width/2); k++)
	{	
		c = k / ((height/2) * (width/2));
		i = (k / (width/2)) % (height/2);
		j = k % ((width / 2));
		d1_ce[(6 + i) * ((width / 2) + 12) + 6 + j + c * ((width / 2) + 12) * (height / 2 + 12)] = d1_c[i *  (width / 2) + j + c * ((width / 2)) * (height / 2)];
	}
	c = 0;i = 0;j = 0;
	//subloop2左侧边界填充
	for ( int k = 0; k < 4 * (height/2) * 6; k++)
	{	
		c = k / (height/2);
		i = 6 + (k / 6) % (height/2);
		j = k % 6;
		d1_ce[i * ((width / 2) + 12) + j + c * ((width / 2) + 12) * (height / 2 + 12)] = d1_c[(i - 6) *  (width / 2) + c * ((width / 2)) * (height / 2)];
	}
	c = 0;i = 0;j = 0;
	//subloop3右侧边界填充
	for ( int k = 0; k < 4 * (height/2) * 6; k++)
	{	
		c = k / (height/2);
		i = 6 + (k / 6) % (height/2);
		j = (width / 2) + 6 + k % 6;
		d1_ce[i * ((width / 2) + 12) + j + c * ((width / 2) + 12) * (height / 2 + 12)] = d1_c[(i - 6) *  ((width / 2)) + ((width / 2)) - 1 + c * (((width / 2))) * (height / 2)];
	}
	c = 0;i = 0;j = 0;
	//subloop4顶部边界填充
	for ( int k = 0; k < 4 * 6 * (width/2+12); k++)
	{	
		// c = k / (6 * (width/2+12));
		if(k % (6 * (width/2+12)) == 0 && k != 0)
			c++;
		// i = (k / (width/2+12)) % 6;
		if(k != 0 && k % (width/2+12) == 0)
			i++;
		j = k % (width/2+12);
		d1_ce[i * (((width / 2)) + 12) + j + c * (((width / 2)) + 12) * (height / 2 + 12)] = d1_c[6 * (((width / 2)) + 12) + j + c * (((width / 2)) + 12) * (height / 2 + 12)];
	}
	c = 0;i = 0;j = 0;
	//subloop5底部边界填充
	for ( int k = 0; k < 4 * 6 * (width/2+8); k++)
	{	
		c = k / (6 * (width/2+12));
		i = height / 2 + 6 + (k / (width/2+12)) % 6;
		j = k % (width/2+12);
		d1_ce[i * (((width / 2)) + 12) + j + c * (((width / 2)) + 12) * (height / 2 + 12)] = d1_c[(height / 2 + 5) * (((width / 2)) + 12) + j + c * (((width / 2)) + 12) * (height / 2 + 12)];
	}

	int central_block[9][9] = { 0 };
	int ref_block[9][9] = { 0 };
	int filter_sum = 0;
	long long weight_sum = 0;
	long long sad = 0;
	long long weight = 0;
	unsigned int div_coef, shft;
	long sad_thr = 160 * 25;  
	unsigned int nbit, idx, delta;
	const unsigned short INV_TAB64A[65] = { 0x1FFF, 0x1FFF, 0x1000, 0x0AAA, 0x0800, 0x0666, 0x0555, 0x0492,
    0x0400, 0x038E, 0x0333, 0x02E9, 0x02AB, 0x0276, 0x0249, 0x0222,
    0x0200, 0x01E2, 0x01C7, 0x01AF, 0x019A, 0x0186, 0x0174, 0x0164,
    0x0155, 0x0148, 0x013B, 0x012F, 0x0125, 0x011A, 0x0111, 0x0108,
    0x0100, 0x00F8, 0x00F1, 0x00EA, 0x00E4, 0x00DD, 0x00D8, 0x00D2,
    0x00CD, 0x00C8, 0x00C3, 0x00BE, 0x00BA, 0x00B6, 0x00B2, 0x00AE,
    0x00AB, 0x00A7, 0x00A4, 0x00A1, 0x009E, 0x009B, 0x0098, 0x0095,
    0x0092, 0x0090, 0x008D, 0x008B, 0x0089, 0x0086, 0x0084, 0x0082, 0x0080 };
	unsigned short *INV_TAB64 = (unsigned short *)&INV_TAB64A[0];


	c = 0;i = 0;j = 0;
	i = 6;
	j = 6;
	for (int k = 0; k < 4 * (height / 2) * (width/2); k++)
	{	
		// if(k % ((height / 2) * (width/2)) == 0 && k != 0)
		// {
		// 	c++;
		// 	i = 6; // 重置 i 的初始值
		// }
		c = k / (height / 2) / (width/2);

		// if(k % (width/2) == 0 && k != 0)
		// {
		// 	i++;
		// 	j = 6; // 重置 j 的初始值
		// }
		i = 6 + k / (width/2) % (height / 2);

		// 更新 j 的值
   		j = 6 + (k % (((width / 2))));

		// y = -2, x = -2
		central_block[0][0] = d1_ce[(i - 2) * (((width / 2)) + 12) + j - 2 + c * (((width / 2)) + 12) * (height / 2 + 12)];
		// y = -2, x = -1
		central_block[0][1] = d1_ce[(i - 2) * (((width / 2)) + 12) + j - 1 + c * (((width / 2)) + 12) * (height / 2 + 12)];
		// y = -2, x = 0
		central_block[0][2] = d1_ce[(i - 2) * (((width / 2)) + 12) + j + 0 + c * (((width / 2)) + 12) * (height / 2 + 12)];
		// y = -2, x = 1
		central_block[0][3] = d1_ce[(i - 2) * (((width / 2)) + 12) + j + 1 + c * (((width / 2)) + 12) * (height / 2 + 12)];
		// y = -2, x = 2
		central_block[0][4] = d1_ce[(i - 2) * (((width / 2)) + 12) + j + 2 + c * (((width / 2)) + 12) * (height / 2 + 12)];

		// y = -1, x = -2
		central_block[1][0] = d1_ce[(i - 1) * (((width / 2)) + 12) + j - 2 + c * (((width / 2)) + 12) * (height / 2 + 12)];
		// y = -1, x = -1
		central_block[1][1] = d1_ce[(i - 1) * (((width / 2)) + 12) + j - 1 + c * (((width / 2)) + 12) * (height / 2 + 12)];
		// y = -1, x = 0
		central_block[1][2] = d1_ce[(i - 1) * (((width / 2)) + 12) + j + 0 + c * (((width / 2)) + 12) * (height / 2 + 12)];
		// y = -1, x = 1
		central_block[1][3] = d1_ce[(i - 1) * (((width / 2)) + 12) + j + 1 + c * (((width / 2)) + 12) * (height / 2 + 12)];
		// y = -1, x = 2
		central_block[1][4] = d1_ce[(i - 1) * (((width / 2)) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

		// y = 0, x = -2
		central_block[2][0] = d1_ce[(i + 0) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
		// y = 0, x = -1
		central_block[2][1] = d1_ce[(i + 0) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
		// y = 0, x = 0
		central_block[2][2] = d1_ce[(i + 0) * ((width / 2) + 12) + j + 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
		// y = 0, x = 1
		central_block[2][3] = d1_ce[(i + 0) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
		// y = 0, x = 2
		central_block[2][4] = d1_ce[(i + 0) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

		// y = 1, x = -2
		central_block[3][0] = d1_ce[(i + 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
		// y = 1, x = -1
		central_block[3][1] = d1_ce[(i + 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
		// y = 1, x = 0
		central_block[3][2] = d1_ce[(i + 1) * ((width / 2) + 12) + j + 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
		// y = 1, x = 1
		central_block[3][3] = d1_ce[(i + 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
		// y = 1, x = 2
		central_block[3][4] = d1_ce[(i + 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

		// y = 2, x = -2
		central_block[4][0] = d1_ce[(i + 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
		// y = 2, x = -1
		central_block[4][1] = d1_ce[(i + 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
		// y = 2, x = 0
		central_block[4][2] = d1_ce[(i + 2) * ((width / 2) + 12) + j + 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
		// y = 2, x = 1
		central_block[4][3] = d1_ce[(i + 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
		// y = 2, x = 2
		central_block[4][4] = d1_ce[(i + 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
		
		weight_sum = 0;
		filter_sum = 0;

		//=========================
		// m = -4, n = -4
		{
			// y = -2
			// x = -2
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-2 + 2][0 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-2 + 2][1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-2 + 2][2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = -1
			// x = -2
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-1 + 2][0 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-1 + 2][1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-1 + 2][2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 0
			// x = -2
			ref_block[0 + 2][-2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[0 + 2][-1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[0 + 2][0 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[0 + 2][1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[0 + 2][2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 1
			// x = -2
			ref_block[1 + 2][-2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[1 + 2][-1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[1 + 2][0 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[1 + 2][1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[1 + 2][2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 2
			// x = -2
			ref_block[2 + 2][-2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[2 + 2][-1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[2 + 2][0 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[2 + 2][1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[2 + 2][2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -4, n = -3
		{
			// y = -2
			// x = -2
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-2 + 2][0 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-2 + 2][1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-2 + 2][2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = -1
			// x = -2
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-1 + 2][0 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-1 + 2][1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-1 + 2][2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 0
			// x = -2
			ref_block[0 + 2][-2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[0 + 2][-1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[0 + 2][0 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[0 + 2][1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[0 + 2][2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 1
			// x = -2
			ref_block[1 + 2][-2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[1 + 2][-1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[1 + 2][0 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[1 + 2][1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[1 + 2][2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 2
			// x = -2
			ref_block[2 + 2][-2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[2 + 2][-1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[2 + 2][0 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[2 + 2][1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[2 + 2][2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -4, n = -2
		{
			// y = -2
			// x = -2
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-2 + 2][0 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-2 + 2][1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-2 + 2][2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = -1
			// x = -2
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-1 + 2][0 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-1 + 2][1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-1 + 2][2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 0
			// x = -2
			ref_block[0 + 2][-2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[0 + 2][-1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[0 + 2][0 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[0 + 2][1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[0 + 2][2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 1
			// x = -2
			ref_block[1 + 2][-2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[1 + 2][-1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[1 + 2][0 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[1 + 2][1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[1 + 2][2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 2
			// x = -2
			ref_block[2 + 2][-2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[2 + 2][-1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[2 + 2][0 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[2 + 2][1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[2 + 2][2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -4, n = -1
		{
			// y = -2
			// x = -2
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-2 + 2][0 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-2 + 2][1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-2 + 2][2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = -1
			// x = -2
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-1 + 2][0 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-1 + 2][1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-1 + 2][2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 0
			// x = -2
			ref_block[0 + 2][-2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[0 + 2][-1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[0 + 2][0 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[0 + 2][1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[0 + 2][2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 1
			// x = -2
			ref_block[1 + 2][-2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[1 + 2][-1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[1 + 2][0 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[1 + 2][1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[1 + 2][2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 2
			// x = -2
			ref_block[2 + 2][-2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[2 + 2][-1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[2 + 2][0 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[2 + 2][1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[2 + 2][2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -4, n = 0
		{
			// y = -2
			// x = -2
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-2 + 2][0 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-2 + 2][1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-2 + 2][2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = -1
			// x = -2
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-1 + 2][0 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-1 + 2][1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-1 + 2][2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 0
			// x = -2
			ref_block[0 + 2][-2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[0 + 2][-1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[0 + 2][0 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[0 + 2][1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[0 + 2][2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 1
			// x = -2
			ref_block[1 + 2][-2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[1 + 2][-1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[1 + 2][0 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[1 + 2][1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[1 + 2][2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 2
			// x = -2
			ref_block[2 + 2][-2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[2 + 2][-1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[2 + 2][0 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[2 + 2][1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[2 + 2][2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -4, n = 1
		{
			// y = -2
			// x = -2
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-2 + 2][0 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-2 + 2][1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-2 + 2][2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = -1
			// x = -2
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-1 + 2][0 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-1 + 2][1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-1 + 2][2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 0
			// x = -2
			ref_block[0 + 2][-2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[0 + 2][-1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[0 + 2][0 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[0 + 2][1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[0 + 2][2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 1
			// x = -2
			ref_block[1 + 2][-2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[1 + 2][-1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[1 + 2][0 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[1 + 2][1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[1 + 2][2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 2
			// x = -2
			ref_block[2 + 2][-2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[2 + 2][-1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[2 + 2][0 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[2 + 2][1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[2 + 2][2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -4, n = 2
		{
			// y = -2
			// x = -2
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-2 + 2][0 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-2 + 2][1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-2 + 2][2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = -1
			// x = -2
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-1 + 2][0 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-1 + 2][1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-1 + 2][2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 0
			// x = -2
			ref_block[0 + 2][-2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[0 + 2][-1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[0 + 2][0 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[0 + 2][1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[0 + 2][2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 1
			// x = -2
			ref_block[1 + 2][-2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[1 + 2][-1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[1 + 2][0 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[1 + 2][1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[1 + 2][2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 2
			// x = -2
			ref_block[2 + 2][-2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[2 + 2][-1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[2 + 2][0 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[2 + 2][1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[2 + 2][2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -4, n = 3
		{
			// y = -2
			// x = -2
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-2 + 2][0 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-2 + 2][1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-2 + 2][2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = -1
			// x = -2
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-1 + 2][0 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-1 + 2][1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-1 + 2][2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 0
			// x = -2
			ref_block[0 + 2][-2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[0 + 2][-1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[0 + 2][0 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[0 + 2][1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[0 + 2][2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 1
			// x = -2
			ref_block[1 + 2][-2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[1 + 2][-1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[1 + 2][0 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[1 + 2][1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[1 + 2][2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 2
			// x = -2
			ref_block[2 + 2][-2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[2 + 2][-1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[2 + 2][0 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[2 + 2][1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[2 + 2][2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -4, n = 4
		{
			// y = -2
			// x = -2
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-2 + 2][0 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-2 + 2][1 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-2 + 2][2 + 2] = d1_ce[(i - 4 - 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = -1
			// x = -2
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-1 + 2][0 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-1 + 2][1 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-1 + 2][2 + 2] = d1_ce[(i - 4 - 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 0
			// x = -2
			ref_block[0 + 2][-2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[0 + 2][-1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[0 + 2][0 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[0 + 2][1 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[0 + 2][2 + 2] = d1_ce[(i - 4) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 1
			// x = -2
			ref_block[1 + 2][-2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[1 + 2][-1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[1 + 2][0 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[1 + 2][1 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[1 + 2][2 + 2] = d1_ce[(i - 4 + 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 2
			// x = -2
			ref_block[2 + 2][-2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[2 + 2][-1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[2 + 2][0 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[2 + 2][1 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[2 + 2][2 + 2] = d1_ce[(i - 4 + 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}
		//=========================
		// m = -3, n = -4
		{
			// y = -2
			// x = -2
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-2 + 2][0 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-2 + 2][1 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-2 + 2][2 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = -1
			// x = -2
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-1 + 2][0 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-1 + 2][1 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-1 + 2][2 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 0
			// x = -2
			ref_block[0 + 2][-2 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[0 + 2][-1 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[0 + 2][0 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[0 + 2][1 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[0 + 2][2 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 1
			// x = -2
			ref_block[1 + 2][-2 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[1 + 2][-1 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[1 + 2][0 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[1 + 2][1 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[1 + 2][2 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 2
			// x = -2
			ref_block[2 + 2][-2 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[2 + 2][-1 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[2 + 2][0 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[2 + 2][1 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[2 + 2][2 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -3, n = -3
		{
			// y = -2
			// x = -2
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-2 + 2][0 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-2 + 2][1 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-2 + 2][2 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = -1
			// x = -2
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-1 + 2][0 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-1 + 2][1 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-1 + 2][2 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 0
			// x = -2
			ref_block[0 + 2][-2 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[0 + 2][-1 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[0 + 2][0 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[0 + 2][1 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[0 + 2][2 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 1
			// x = -2
			ref_block[1 + 2][-2 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[1 + 2][-1 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[1 + 2][0 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[1 + 2][1 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[1 + 2][2 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 2
			// x = -2
			ref_block[2 + 2][-2 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[2 + 2][-1 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[2 + 2][0 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[2 + 2][1 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[2 + 2][2 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -3, n = -2
		{
			// y = -2
			// x = -2
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-2 + 2][0 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-2 + 2][1 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-2 + 2][2 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = -1
			// x = -2
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-1 + 2][0 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-1 + 2][1 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-1 + 2][2 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 0
			// x = -2
			ref_block[0 + 2][-2 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[0 + 2][-1 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[0 + 2][0 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[0 + 2][1 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[0 + 2][2 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 1
			// x = -2
			ref_block[1 + 2][-2 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[1 + 2][-1 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[1 + 2][0 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[1 + 2][1 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[1 + 2][2 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 2
			// x = -2
			ref_block[2 + 2][-2 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[2 + 2][-1 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[2 + 2][0 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[2 + 2][1 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[2 + 2][2 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -3, n = -1
		{
			// y = -2
			// x = -2
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-2 + 2][0 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-2 + 2][1 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-2 + 2][2 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = -1
			// x = -2
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-1 + 2][0 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-1 + 2][1 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-1 + 2][2 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 0
			// x = -2
			ref_block[0 + 2][-2 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[0 + 2][-1 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[0 + 2][0 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[0 + 2][1 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[0 + 2][2 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 1
			// x = -2
			ref_block[1 + 2][-2 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[1 + 2][-1 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[1 + 2][0 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[1 + 2][1 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[1 + 2][2 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 2
			// x = -2
			ref_block[2 + 2][-2 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[2 + 2][-1 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[2 + 2][0 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[2 + 2][1 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[2 + 2][2 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -3, n = 0
		{
			// y = -2
			// x = -2
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-2 + 2][0 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-2 + 2][1 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-2 + 2][2 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = -1
			// x = -2
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[-1 + 2][0 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[-1 + 2][1 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[-1 + 2][2 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 0
			// x = -2
			ref_block[0 + 2][-2 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[0 + 2][-1 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[0 + 2][0 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[0 + 2][1 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[0 + 2][2 + 2] = d1_ce[(i - 3) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 1
			// x = -2
			ref_block[1 + 2][-2 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[1 + 2][-1 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[1 + 2][0 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[1 + 2][1 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[1 + 2][2 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// y = 2
			// x = -2
			ref_block[2 + 2][-2 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = -1
			ref_block[2 + 2][-1 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 0
			ref_block[2 + 2][0 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 1
			ref_block[2 + 2][1 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			// x = 2
			ref_block[2 + 2][2 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -3, n = 1
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -3, n = 2
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -3, n = 3
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -3, n = 4
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 3 - 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 3 - 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 3 - 0) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 3 + 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 3 + 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		//==========================
		// m = -2, n = -4
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -2, n = -3
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -2, n = -2
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -2, n = -1
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -2, n = 0
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -2, n = 1
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -2, n = 2
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -2, n = 3
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -2, n = 4
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 2 - 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 2 - 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 2 - 0) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 2 + 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 2 + 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);
			
			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}
		//===================
		// m = -1, n = -4
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -1, n = -3
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -1, n = -2
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -1, n = -1
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -1, n = 0
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -1, n = 1
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -1, n = 2
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -1, n = 3
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = -1, n = 4
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 1 - 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 1 - 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 1 - 0) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 1 + 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 1 + 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}
		//=====================================
		// m = 0, n = -4
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 0, n = -3
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			
			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 0, n = -2
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 0, n = -1
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 0, n = 1
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 0, n = 2
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 0, n = 3
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 0, n = 4
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i - 0 - 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i - 0 - 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i - 0 - 0) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i - 0 + 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i - 0 + 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight;
		}

		//=====================================
		// m = 1, n = -4
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 1, n = -3
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 1, n = -2
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 1, n = -1
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 1, n = 0
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 1, n = 1
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 1, n = 2
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 1, n = 3
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 1, n = 4
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 1 - 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 1 - 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 1 - 0) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 1 + 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 1 + 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}
		//============================================
		// m = 2, n = -4
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 2, n = -3
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 2, n = -2
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 2, n = -1
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 2, n = 0
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 2, n = 1
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 2, n = 2
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 2, n = 3
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 2, n = 4
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 2 - 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 2 - 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 2 - 0) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 2 + 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 2 + 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);
			
			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}
		//======================================
		// m = 3, n = -4
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 3, n = -3
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 3, n = -2
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);
			
			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 3, n = -1
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 3, n = 0
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 3, n = 1
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 3, n = 2
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 3, n = 3
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 3, n = 4
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 3 - 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 3 - 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 3 - 0) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 3 + 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 3 + 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);
			
			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}
		//==================================
		// m = 4, n = -4
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 4, n = -3
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 4, n = -2
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 4, n = -1
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 4, n = 0
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 0 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 0 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 0 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 0 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j - 0 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 4, n = 1
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 1 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 1 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 1 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 1 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 4, n = 2
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 2 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 2 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 2 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 2 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 4, n = 3
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 3 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 3 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 3 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 3 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 3 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}

		// m = 4, n = 4
		{
			ref_block[-2 + 2][-2 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][-1 + 2] = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][0 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][1 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-2 + 2][2 + 2]  = d1_ce[(i + 4 - 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-2 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][-1 + 2] = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][0 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][1 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[-1 + 2][2 + 2]  = d1_ce[(i + 4 - 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-2 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][-1 + 2] = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][0 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][1 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[0 + 2 ][2 + 2]  = d1_ce[(i + 4 - 0) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-2 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][-1 + 2] = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][0 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][1 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[1 + 2 ][2 + 2]  = d1_ce[(i + 4 + 1) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-2 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 4 - 2 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][-1 + 2] = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 4 - 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][0 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 4 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][1 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 4 + 1 + c * ((width / 2) + 12) * (height / 2 + 12)];
			ref_block[2 + 2 ][2 + 2]  = d1_ce[(i + 4 + 2) * ((width / 2) + 12) + j + 4 + 2 + c * ((width / 2) + 12) * (height / 2 + 12)];

			sad = 0;
			sad += abs(central_block[0][0] - ref_block[0][0]);
			sad += abs(central_block[0][1] - ref_block[0][1]);
			sad += abs(central_block[0][2] - ref_block[0][2]);
			sad += abs(central_block[0][3] - ref_block[0][3]);
			sad += abs(central_block[0][4] - ref_block[0][4]);

			sad += abs(central_block[1][0] - ref_block[1][0]);
			sad += abs(central_block[1][1] - ref_block[1][1]);
			sad += abs(central_block[1][2] - ref_block[1][2]);
			sad += abs(central_block[1][3] - ref_block[1][3]);
			sad += abs(central_block[1][4] - ref_block[1][4]);

			sad += abs(central_block[2][0] - ref_block[2][0]);
			sad += abs(central_block[2][1] - ref_block[2][1]);
			sad += abs(central_block[2][2] - ref_block[2][2]);
			sad += abs(central_block[2][3] - ref_block[2][3]);
			sad += abs(central_block[2][4] - ref_block[2][4]);

			sad += abs(central_block[3][0] - ref_block[3][0]);
			sad += abs(central_block[3][1] - ref_block[3][1]);
			sad += abs(central_block[3][2] - ref_block[3][2]);
			sad += abs(central_block[3][3] - ref_block[3][3]);
			sad += abs(central_block[3][4] - ref_block[3][4]);

			sad += abs(central_block[4][0] - ref_block[4][0]);
			sad += abs(central_block[4][1] - ref_block[4][1]);
			sad += abs(central_block[4][2] - ref_block[4][2]);
			sad += abs(central_block[4][3] - ref_block[4][3]);
			sad += abs(central_block[4][4] - ref_block[4][4]);

			weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
			weight_sum += weight;
			filter_sum += weight * ref_block[2][2];
		}


		weight_sum += sad_thr;
		filter_sum += sad_thr * central_block[2][2];

		// tnr_div64(weight_sum, &div_coef, &shft);	
		if (((weight_sum >> 25) & 0x01) != 0)
		{
			nbit = 26;
		}
		else if (((weight_sum >> 24) & 0x01) != 0)
		{
			nbit = 25;
		}
		else if (((weight_sum >> 23) & 0x01) != 0)
		{
			nbit = 24;
		}
		else if (((weight_sum >> 22) & 0x01) != 0)
		{
			nbit = 23;
		}
		else if (((weight_sum >> 21) & 0x01) != 0)
		{
			nbit = 22;
		}
		else if (((weight_sum >> 20) & 0x01) != 0)
		{
			nbit = 21;
		}
		else if (((weight_sum >> 19) & 0x01) != 0)
		{
			nbit = 20;
		}
		else if (((weight_sum >> 18) & 0x01) != 0)
		{
			nbit = 19;
		}
		else if (((weight_sum >> 17) & 0x01) != 0)
		{
			nbit = 18;
		}
		else if (((weight_sum >> 16) & 0x01) != 0)
		{
			nbit = 17;
		}
		else if (((weight_sum >> 15) & 0x01) != 0)
		{
			nbit = 16;
		}
		else if (((weight_sum >> 14) & 0x01) != 0)
		{
			nbit = 15;
		}
		else if (((weight_sum >> 13) & 0x01) != 0)
		{
			nbit = 14;
		}
		else if (((weight_sum >> 12) & 0x01) != 0)
		{
			nbit = 13;
		}
		else if (((weight_sum >> 11) & 0x01) != 0)
		{
			nbit = 12;
		}
		else if (((weight_sum >> 10) & 0x01) != 0)
		{
			nbit = 11;
		}
		else if (((weight_sum >> 9) & 0x01) != 0)
		{
			nbit = 10;
		}
		else if (((weight_sum >> 8) & 0x01) != 0)
		{
			nbit = 9;
		}
		else if (((weight_sum >> 7) & 0x01) != 0)
		{
			nbit = 8;
		}
		else if (((weight_sum >> 6) & 0x01) != 0)
		{
			nbit = 7;
		}
		else if (((weight_sum >> 5) & 0x01) != 0)
		{
			nbit = 6;
		}
		else if (((weight_sum >> 4) & 0x01) != 0)
		{
			nbit = 5;
		}
		else if (((weight_sum >> 3) & 0x01) != 0)
		{
			nbit = 4;
		}
		else if (((weight_sum >> 2) & 0x01) != 0)
		{
			nbit = 3;
		}
		else if (((weight_sum >> 1) & 0x01) != 0)
		{
			nbit = 2;
		}
		else if (((weight_sum >> 0) & 0x01) != 0)
		{
			nbit = 1;
		}
		else
		{
			nbit = 0;
		}

		// if (weight_sum == 0) {
		// 	nbit = 0;
		// } else {
		// 	nbit = 32 - __builtin_clz(weight_sum);  // 使用 GCC 或 Clang 的内置函数
		// }

		if (weight_sum <= 63)
		{
			div_coef = INV_TAB64[weight_sum];
			shft = 0;
		}
		else
		{
			idx = weight_sum >> (nbit - 6);
			div_coef = INV_TAB64[idx];
			// shft = nbit - 6;
			if (nbit > 6) {
				shft = nbit - 6;
			} else {
				shft = 0; 
			}
		}

		d1_c[(i - 6) * (width / 2) + (j - 6) + c * ((width / 2)) * (height / 2)] = ((long long)filter_sum * div_coef + (4096 << shft)) >> (13 + shft);
	}

	i = 0;j = 0;
	for (int k = 0; k < (height*width/4); k++)// ii = 1
	{	
		// if(k % (width/2) == 0 && k != 0)
		// 	i++;
		i = k / (width/2);
		j = k % (width/2);
		d1out[i * 2 * width + j * 2] = d1_c[i * (width / 2) + j];
		d1out[i * 2 * width + j * 2] = d1_c[i * (width / 2) + j];
		d1out[i * 2 * width + j * 2 + 1] = d1_c[i * (width / 2) + j + ((width / 2)) * (height / 2)];
		d1out[(i * 2 + 1) * width + j * 2] = d1_c[i * (width / 2) + j + ((width / 2)) * (height / 2) * 2];
		d1out[(i * 2 + 1) * width + j * 2 + 1] = d1_c[i * (width / 2) + j + ((width / 2)) * (height / 2) * 3];
	}
	free(d1_c);
	free(d1_ce);
}