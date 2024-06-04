#include <iostream>
#include"../include/alg1.hh"
#include<stdlib.h>
#include <malloc.h>

#define GRID_H 16
#define GRID_W 8
#define clip_bits(X, MIN, MAX)  (((X) < (MIN)) ? (MIN) : (((X) > (MAX-1)) ? (MAX-1) : (X)))

void alg1_func1(unsigned short d2_out[D2_HEIGHT_OUT][D2_WIDTH_OUT][3], unsigned short d2_in[D2_HEIGHT_IN][D2_WIDTH_IN][3])
{
	int i_src_left = 0;
	int i_src_right = 0;
	int j_src_left = 0;
	int j_src_right = 0;
	int weight_wide = 0;
	int weight_high = 0;
	int val0 = 0;
	int val1 = 0;
	int val2 = 0;
	int val3 = 0;
	int temp0 = 0;
	int temp1 = 0;
	int grid_length_wide = (D2_WIDTH_IN << 10) / D2_WIDTH_OUT;
	int grid_length_high = (D2_HEIGHT_IN << 10) / D2_HEIGHT_OUT;
	//for (int i = 0;i < D2_HEIGHT_OUT;i++) 
	for (int j = 0;j < D2_WIDTH_OUT;j++)
	{
		//for (int j = 0;j < D2_WIDTH_OUT;j++)
		for (int i = 0;i < D2_HEIGHT_OUT;i++) 
		{
			i_src_left = (i * grid_length_wide) >> 10;
			i_src_right = (i_src_left + 1) >= D2_HEIGHT_IN ? i_src_left : (i_src_left + 1);
			j_src_left = (j * grid_length_high) >> 10;
			j_src_right = (j_src_left + 1) >= D2_WIDTH_IN ? j_src_left : (j_src_left + 1);
			
				


			val0 = d2_in[i_src_left][j_src_left][0];
			val1 = d2_in[i_src_left][j_src_right][0];
			val2 = d2_in[i_src_right][j_src_left][0];
			val3 = d2_in[i_src_right][j_src_right][0];

			/*if (count < 100) {
			std::cout << "val0: " << val0 << " val1: " << val1 << " val2: " << val2 << " val3: " << val3 << std::endl;
			}*/

			weight_high = i * grid_length_high - (i_src_left << 10);
			weight_wide = j * grid_length_wide - (j_src_left << 10); 
			temp0 = (weight_wide * val0 + (1024 - weight_wide) * val1) >> 10;
			temp1 = (weight_wide * val2 + (1024 - weight_wide) * val3) >> 10;
			d2_out[i][j][0] = (weight_high * temp0 + (1024 - weight_high) * temp1) >> 10;
		
			

			val0 = d2_in[i_src_left][j_src_left][1];
			val1 = d2_in[i_src_left][j_src_right][1];
			val2 = d2_in[i_src_right][j_src_left][1];
			val3 = d2_in[i_src_right][j_src_right][1];
			temp0 = (weight_wide*val0 + (1024 - weight_wide)*val1) >> 10;
			temp1 = (weight_wide*val2 + (1024 - weight_wide)*val3) >> 10;

			d2_out[i][j][1] = (weight_high*temp0 + (1024 - weight_high)*temp1) >> 10;
			val0 = d2_in[i_src_left][j_src_left][2];
			val1 = d2_in[i_src_left][j_src_right][2];
			val2 = d2_in[i_src_right][j_src_left][2];
			val3 = d2_in[i_src_right][j_src_right][2];
			temp0 = (weight_wide*val0 + (1024 - weight_wide)*val1) >> 10;
			temp1 = (weight_wide*val2 + (1024 - weight_wide)*val3) >> 10;

			d2_out[i][j][2] = (weight_high*temp0 + (1024 - weight_high)*temp1) >> 10;

		}
	}
}


void alg1_func2(int out[GRID_H*GRID_W], unsigned short D1[D2_WIDTH_IN*D2_HEIGHT_IN])
{

	int * v1 = (int *)malloc((D2_WIDTH_IN / 2) * (D2_HEIGHT_IN / 2) * sizeof(int));
	int * v2 = (int *)malloc((D2_WIDTH_IN / 2) * (D2_HEIGHT_IN / 2) * sizeof(int));
	
	for (int i = 0; i < D2_HEIGHT_IN / 2; i++) {
		for (int j = 0; j < D2_WIDTH_IN / 2; j++) {
			if(D1[2 * (i * D2_WIDTH_IN + j) + 1]!= 0 )
			v1[i*D2_WIDTH_IN/2+j] = clip_bits((D1[2 * (i*D2_WIDTH_IN + j)] << 10) / (D1[2 * (i*D2_WIDTH_IN + j) + 1]), 0, 4095);
			if(D1[2 * (i * D2_WIDTH_IN + j) + 1] != 0 )
			v2[i*D2_WIDTH_IN/2+j] = clip_bits((D1[2 * (i*D2_WIDTH_IN + j) + 1+ D2_WIDTH_IN] << 10) / (D1[2 * (i*D2_WIDTH_IN + j) + 1]), 0, 4095);
		}
	}
	int index_w = 0;
	int index_h = 0;
	int step_w = 4095 / GRID_H;
	int step_h = 4095 / GRID_W;
	for (int i = 0; i < GRID_H*GRID_W; i++) {
		out[i] = 0;
	}
	for (int i = 0; i < D2_HEIGHT_IN / 2; i++)
	{
		for (int j = 0; j < D2_WIDTH_IN / 2; j++)
		{
			index_w = v1[i*D2_WIDTH_IN / 2 + j] / step_w;
			index_h = v2[i*D2_WIDTH_IN / 2 + j] / step_h;
			index_w = clip_bits(index_w, 0, GRID_W);
			index_h = clip_bits(index_h, 0, GRID_H);
			out[index_w*GRID_H + index_h] += 1;
		}
	}
	free(v1);
	free(v2);
}