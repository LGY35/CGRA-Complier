#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static unsigned int tnr_div64(unsigned int in, unsigned int *out, unsigned int *shft)
{
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
	for (int i = 25; i >= 0; i--)  // ii = 1
	{
		if (((in >> i) & 0x01) != 0)
		{
			nbit = i + 1;
			break;
		}
	}
	if (in <= 63)
	{
		*out = INV_TAB64[in];
		*shft = 0;
	}
	else
	{
		idx = in >> (nbit - 6);
		*out = INV_TAB64[idx];
		*shft = nbit - 6;
	}
	return 0;
}
void alg4_func(unsigned short * d1in, unsigned short  * d1out, unsigned int width, unsigned int height)
{
	int * d1_c = (int *)malloc((width / 2) * (height / 2) * 4 * sizeof(int));
	int * d1_ce = (int*)malloc((width / 2 + 12) * (height / 2 + 12) * 4 * sizeof(int));
    int i = 0,j = 0;

	for (int k = 0; k < (height*width/4); k++)// ii = 1
	{
		i = k / (width/2);
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
		c = k / ((height/2) * (width/2));
		i = (k / (width/2)) % (height/2);
		j = k % (width / 2);
		d1_ce[(6 + i) * (width / 2 + 12) + 6 + j + c * (width / 2 + 12) * (height / 2 + 12)] = d1_c[i *  width / 2 + j + c * (width / 2) * (height / 2)];
	}
	//subloop2左侧边界填充
	for (int k = 0; k < 4 * (height/2) * 6; k++)
	{	
		c = k / (height/2);
		i = 6 + (k / 6) % (height/2);
		j = k % 6;
		d1_ce[i * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)] = d1_c[(i - 6) *  width / 2 + c * (width / 2) * (height / 2)];
	}
	//subloop3右侧边界填充
	for (int k = 0; k < 4 * (height/2) * 6; k++)
	{	
		c = k / (height/2);
		i = 6 + (k / 6) % (height/2);
		j = width / 2 + 6 + k % 6;
		d1_ce[i * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)] = d1_c[(i - 6) *  width / 2 + width / 2 - 1 + c * (width / 2) * (height / 2)];
	}
	//subloop4顶部边界填充
	for (int k = 0; k < 4 * 6 * (width/2+12); k++)
	{	
		c = k / (6 * (width/2+12));
		i = (k / (width/2+12)) % 6;
		j = k % (width/2+12);
		d1_ce[i * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)] = d1_ce[6 * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)];
	}
	//subloop5底部边界填充
	for (int k = 0; k < 4 * 6 * (width/2+8); k++)
	{	
		c = k / (6 * (width/2+12));
		i = height / 2 + 6 + (k / (width/2+12)) % 6;
		j = k % (width/2+12);
		d1_ce[i * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)] = d1_ce[(height / 2 + 5) * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)];
	}

	int central_block[9][9] = { 0 };
	int ref_block[9][9] = { 0 };
	int filter_sum = 0;
	int weight_sum = 0;
	int sad = 0;
	int weight = 0;
	unsigned int div_coef, shft;
	int sad_thr = 160 * 25;  

	c = 0;i = 0;j = 0;
	int x = 0;int y = 0;
	int m = 0;int n = 0;
	for(int k = 0; k < 4 * (height*width/4); k++)
	{
		c = k / (height*width/4);
		i = 6 + (k / (width/2)) % (height/2);
		j = 6 + k % (width / 2);

		for(int inner_xy_k = 0; inner_xy_k < 25; inner_xy_k++)
		{
			x = inner_xy_k / 5 - 2;
			y = inner_xy_k % 5 - 2;
			central_block[y + 2][x + 2] = d1_ce[(i + y) * (width / 2 + 12) + j + x + c * (width / 2 + 12) * (height / 2 + 12)];
		}
				
		weight_sum = 0;
		filter_sum = 0;
		for (int inner_mn_k = 0; inner_mn_k < 81 * 25; inner_mn_k++)
		{
			m = (inner_mn_k/25) / 9 - 4;
			n = (inner_mn_k/25) % 9 - 4;

			if (m == 0 && n == 0)
				continue;

			x = (inner_mn_k%25) / 5 - 2;
			y = (inner_mn_k%25) % 5 - 2;
			ref_block[y + 2][x + 2] = d1_ce[(i + m + y) * (width / 2 + 12) + j + n + x + c * (width / 2 + 12) * (height / 2 + 12)];
			
			 if ((inner_mn_k % 25) == 0)  // Reset SAD at the beginning of each new (m, n) processing
        		sad = 0;
			// x = (inner_mn_k%25) / 5 - 2;
			// y = (inner_mn_k%25) % 5 - 2;
			sad += abs(central_block[y + 2][x + 2] - ref_block[y + 2][x + 2]);

			if ((inner_mn_k % 25) == 24)   // After finishing all 25 xy pairs for current mn pair
			{
				weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
				weight_sum += weight;
				filter_sum += weight * ref_block[2][2];
			}
		}
		weight_sum += sad_thr;
		filter_sum += sad_thr * central_block[2][2];
		tnr_div64(weight_sum, &div_coef, &shft);
		d1_c[(i - 6) * width / 2 + (j - 6) + c * (width / 2) * (height / 2)] = ((long long)filter_sum * div_coef + (4096 << shft)) >> (13 + shft);	
	}

	for (int k = 0; k < (height*width/4); k++)// ii = 1
	{
		i = k / (width/2);
		j = k % (width/2);
		d1out[i * 2 * width + j * 2] = d1_c[i * width / 2 + j];
		d1out[i * 2 * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2)];
		d1out[(i * 2 + 1) * width + j * 2] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2];
		d1out[(i * 2 + 1) * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3];
	}
	free(d1_c);
	free(d1_ce);
}


// backup
	// c = 0;i = 0;j = 0;
	// int x = 0;int y = 0;
	// int m = 0;int n = 0;
	// for(int k = 0; k < 4 * (height*width/4); k++)
	// {
	// 	c = k / (height*width/4);
	// 	i = 6 + (k / (width/2)) % (height/2);
	// 	j = 6 + k % (width / 2);

	// 	for(int inner_xy_k = 0; inner_xy_k < 25; inner_xy_k++)
	// 	{
	// 		x = inner_xy_k / 5 - 2;
	// 		y = inner_xy_k % 5 - 2;
	// 		central_block[y + 2][x + 2] = d1_ce[(i + y) * (width / 2 + 12) + j + x + c * (width / 2 + 12) * (height / 2 + 12)];
	// 	}
				
	// 	weight_sum = 0;
	// 	filter_sum = 0;
	// 	for (int inner_mn_k = 0; inner_mn_k < 81; inner_mn_k++)
	// 	{
	// 		m = inner_mn_k / 9 - 4;
	// 		n = inner_mn_k % 9 - 4;

	// 		if (m == 0 && n == 0)
	// 			continue;

	// 		for(int inner_xy_k = 0; inner_xy_k < 25; inner_xy_k++)
	// 		{
	// 			x = inner_xy_k / 5 - 2;
	// 			y = inner_xy_k % 5 - 2;
	// 			ref_block[y + 2][x + 2] = d1_ce[(i + m + y) * (width / 2 + 12) + j + n + x + c * (width / 2 + 12) * (height / 2 + 12)];
	// 		}
	// 		sad = 0;
	// 		for(int inner_xy_k = 0; inner_xy_k < 25; inner_xy_k++)
	// 		{
	// 			x = inner_xy_k / 5 - 2;
	// 			y = inner_xy_k % 5 - 2;
	// 			sad += abs(central_block[y + 2][x + 2] - ref_block[y + 2][x + 2]);
	// 		}	
	// 		weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
	// 		weight_sum += weight;
	// 		filter_sum += weight * ref_block[2][2];
	// 	}
	// 	weight_sum += sad_thr;
	// 	filter_sum += sad_thr * central_block[2][2];
	// 	tnr_div64(weight_sum, &div_coef, &shft);
	// 	d1_c[(i - 6) * width / 2 + (j - 6) + c * (width / 2) * (height / 2)] = ((long long)filter_sum * div_coef + (4096 << shft)) >> (13 + shft);	
	// }


	// backup222 未改完的单层for
	// 	c = 0;i = 0;j = 0;
	// int x = 0;int y = 0;
	// int m = 0;int n = 0;
	// int base = height * width / 4;
	// int offset = 5 * 5 * 9 * 9;
	// for(int k = 0; k < 4 * (height*width/4) * 25 * 81; k++)
	// {
	// 	c = k / (base * offset);
	// 	int inner_index = k % (offset * base);

	// 	i = 6 + (((inner_index / offset)) / (width/2)) % (height/2);
	// 	j = 6 + (inner_index / offset) % (width / 2);

	// 	int block_index = inner_index % offset;
	// 	x = (block_index / 81) / 5 % 5 - 2; // 5x5 block adjustment
    // 	y = (block_index / 81) % 5 - 2;
	// 	central_block[y + 2][x + 2] = d1_ce[(i + y) * (width / 2 + 12) + j + x + c * (width / 2 + 12) * (height / 2 + 12)];

	// 	if(block_index == 0)	
	// 	{
	// 		weight_sum = 0;
	// 		filter_sum = 0;
	// 	}	
		
	// 	m = (block_index % 81) / 9 - 4;
	// 	n = (block_index % 81) % 9 - 4;
	// 	if (m == 0 && n == 0)
	// 		continue;
	// 	x = (inner_index / 81) / 5 % 5 - 2;
	// 	y = (inner_index / 81) % 5 - 2;
	// 	ref_block[y + 2][x + 2] = d1_ce[(i + m + y) * (width / 2 + 12) + j + n + x + c * (width / 2 + 12) * (height / 2 + 12)];
	// 	if((inner_index / 25) % 81 == 0) sad = 0;
	// 	sad += abs(central_block[y + 2][x + 2] - ref_block[y + 2][x + 2]);
		
	// 	weight = (sad > sad_thr) ? 0 : (sad_thr - sad);
	// 	weight_sum += weight;
	// 	filter_sum += weight * ref_block[2][2];

	// 	if((inner_index/25) % 81 == 80)
	// 	{
	// 		weight_sum += sad_thr;
	// 		filter_sum += sad_thr * central_block[2][2];
	// 		tnr_div64(weight_sum, &div_coef, &shft);
	// 		d1_c[(i - 6) * width / 2 + (j - 6) + c * (width / 2) * (height / 2)] = ((long long)filter_sum * div_coef + (4096 << shft)) >> (13 + shft);	
	// 	}
	// }