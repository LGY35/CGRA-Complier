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
    int i = 0;
	for (int i = 0; i < height / 2; i++)// ii = 1
	{
		for (int j = 0; j < width / 2; j++)
		{
			d1_c[i * width / 2 + j] = d1in[i * 2 * width + j * 2];
			d1_c[i * width / 2 + j + (width / 2) * (height / 2)] = d1in[i * 2 * width + j * 2 + 1];
			d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2] = d1in[(i * 2 + 1) * width + j * 2];
			d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3] = d1in[(i * 2 + 1) * width + j * 2 + 1];
		}
	}
	for (int c = 0; c < 4; c++)        // ii = 7
	{

		for (int i = 0; i < height / 2; i++)
			for (int j = 0; j < width / 2; j++)
				d1_ce[(6 + i) * (width / 2 + 12) + 6 + j + c * (width / 2 + 12) * (height / 2 + 12)] = d1_c[i *  width / 2 + j + c * (width / 2) * (height / 2)];

		for (int i = 6; i < height / 2 + 6; i++)
			for (int j = 0; j < 6; j++)
				d1_ce[i * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)] = d1_c[(i - 6) *  width / 2 + c * (width / 2) * (height / 2)];

		for (int i = 6; i < height / 2 + 6; i++)
			for (int j = width / 2 + 6; j < width / 2 + 12; j++)
				d1_ce[i * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)] = d1_c[(i - 6) *  width / 2 + width / 2 - 1 + c * (width / 2) * (height / 2)];

		for (int i = 0; i < 6; i++)
			for (int j = 0; j < width / 2 + 12; j++)
				d1_ce[i * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)] = d1_ce[6 * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)];
	
		for (int i = height / 2 + 6; i < height / 2 + 12; i++)
			for (int j = 0; j < width / 2 + 12; j++)
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
	for (int c = 0; c < 4; c++)// ii = 10
	{
		for (int i = 6; i < height / 2 + 6; i++)
		{
			for (int j = 6; j < width / 2 + 6; j++)
			{

				for (int y = -2; y <= 2; y++)
					for (int x = -2; x <= 2; x++)
						central_block[y + 2][x + 2] = d1_ce[(i + y) * (width / 2 + 12) + j + x + c * (width / 2 + 12) * (height / 2 + 12)];
				weight_sum = 0;
				filter_sum = 0;
				for (int m = -4; m <= 4; m++)
				{
					for (int n = -4; n <= 4; n++)
					{

						if (m == 0 && n == 0)
							continue;
	
						for (int y = -2; y <= 2; y++)
							for (int x = -2; x <= 2; x++)
								ref_block[y + 2][x + 2] = d1_ce[(i + m + y) * (width / 2 + 12) + j + n + x + c * (width / 2 + 12) * (height / 2 + 12)];
		
						sad = 0;
						for (int y = -2; y <= 2; y++)
							for (int x = -2; x <= 2; x++)
								sad += abs(central_block[y + 2][x + 2] - ref_block[y + 2][x + 2]);
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
		}
	}

	for (int i = 0; i < height / 2; i++)// ii = 1
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