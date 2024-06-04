#include <iostream>
#include"alg6.h"
#define clip_bits(X, MIN, MAX)  (((X) < (MIN)) ? (MIN) : (((X) > (MAX)) ? (MAX) : (X)))
inline void alg6_func_1(
    unsigned short d3_1_dst[ALG6_WIDTH*ALG6_HEIGHT], 
    unsigned short d3_2_dst[ALG6_WIDTH / 2 * ALG6_HEIGHT], 
    unsigned short d3_3_dst[ALG6_WIDTH / 2 * ALG6_HEIGHT], 
    unsigned short d3_1_src[ALG6_WIDTH*ALG6_HEIGHT], 
    unsigned short d3_2_src[ALG6_WIDTH*ALG6_HEIGHT], 
    unsigned short d3_3_src[ALG6_WIDTH*ALG6_HEIGHT]
)
{
	int iHeight = ALG6_HEIGHT;
	int iWidth = ALG6_WIDTH;
    // 该循环不存在，因为在调用后的下一个循环会覆盖
	for (int i = 0; i < iWidth * iHeight; i++)
	{
		d3_1_dst[i] = d3_1_src[i];
	}
	int ped3_2 = 0, ped3_3 = 0, y = 0, x = 0;
	for (int i = 0; i < iHeight * iWidth; i++)
	{
		if (i % iWidth == 0 && i != 0) {
            y++;
        }
        x = i % iWidth;

        if (x % 2 == 0)
        {
            ped3_2 = d3_2_src[iWidth*y + x];
            ped3_2 = clip_bits(ped3_2, 0, 1023);
            d3_2_dst[y * iWidth / 2 + x / 2] = ped3_2;
        }
        else
        {
            ped3_3 = d3_3_src[iWidth*y + x];
            ped3_3 = clip_bits(ped3_3, 0, 1023);
            d3_3_dst[y * iWidth / 2 + x / 2] = ped3_3;
        }
	}
	// for (int y = 0; y < iHeight; y++)
	// {
	// 	for (int x = 0; x < iWidth; x++)
	// 	{
	// 		if (x % 2 == 0)
	// 		{
	// 			ped3_2 = d3_2_src[iWidth*y + x];
	// 			ped3_2 = clip_bits(ped3_2, 0, 1023);
	// 			d3_2_dst[y * iWidth / 2 + x / 2] = ped3_2;
	// 		}
	// 		else
	// 		{
	// 			ped3_3 = d3_3_src[iWidth*y + x];
	// 			ped3_3 = clip_bits(ped3_3, 0, 1023);
	// 			d3_3_dst[y * iWidth / 2 + x / 2] = ped3_3;
	// 		}
	// 	}
	// }
}
unsigned short d3_1[ALG6_HEIGHT * ALG6_WIDTH] = { 0 };
unsigned short d3_2[ALG6_HEIGHT * ALG6_WIDTH] = { 0 };
unsigned short d3_3[ALG6_HEIGHT * ALG6_WIDTH] = { 0 };
unsigned short d3_1_dst[ALG6_HEIGHT * ALG6_WIDTH] = { 0 };
unsigned short d3_2_dst[ALG6_HEIGHT * ALG6_WIDTH / 2] = { 0 };
unsigned short d3_3_dst[ALG6_HEIGHT * ALG6_WIDTH / 2] = { 0 };
void alg6_func(unsigned short src_d3_data[ALG6_HEIGHT * ALG6_WIDTH * 2], unsigned short d4_dst[ALG6_HEIGHT * ALG6_WIDTH], unsigned short d2_in[ALG6_HEIGHT][ALG6_WIDTH][3])
{
	int iHeight = ALG6_HEIGHT;
	int iWidth = ALG6_WIDTH;
	int tran_mat[9] = { 38,75,15,-22,-42,64,64,-54,-10 };
    int x = 0, y = 0;
	// for (int i = 0; i < iHeight * iWidth; i++)
	// {
	// 	if (i % iWidth == 0) {
    //         y++;
    //     }
    //     x = i % iWidth;

    //     int in_d2[3];         
    //     int ext_d3[3];         
    //     in_d2[0] = d2_in[y][x][0];
    //     in_d2[1] = d2_in[y][x][1];
    //     in_d2[2] = d2_in[y][x][2];
    //     ext_d3[0] = (in_d2[0] * tran_mat[0] + in_d2[1] * tran_mat[1] + in_d2[2] * tran_mat[2]+64) >> 7;
    //     ext_d3[1] = (in_d2[0] * tran_mat[3] + in_d2[1] * tran_mat[4] + in_d2[2] * tran_mat[5]+64) >> 7;
    //     ext_d3[2] = (in_d2[0] * tran_mat[6] + in_d2[1] * tran_mat[7] + in_d2[2] * tran_mat[8]+64) >> 7;
    //     ext_d3[0] = ext_d3[0];   // 
    //     ext_d3[1] = ext_d3[1] + (128 << 2);     // 
    //     ext_d3[2] = ext_d3[2] + (128 << 2);     // 
    //     d3_1[iWidth*y + x] = clip_bits(ext_d3[0], 0, 1023);
    //     d4_dst[iWidth*y + x] = d3_1[iWidth*y + x];
    //     d3_2[iWidth*y + x] = clip_bits(ext_d3[1], 0, 1023);
    //     d3_3[iWidth*y + x] = clip_bits(ext_d3[2], 0, 1023);
	// }

	// for (int y = 0; y < iHeight; y++)
	// {
	// 	for (int x = 0; x < iWidth; x++)
	// 	{
	// 		int in_d2[3];         
	// 		int ext_d3[3];         
	// 		in_d2[0] = d2_in[y][x][0];
	// 		in_d2[1] = d2_in[y][x][1];
	// 		in_d2[2] = d2_in[y][x][2];
 	// 		ext_d3[0] = (in_d2[0] * tran_mat[0] + in_d2[1] * tran_mat[1] + in_d2[2] * tran_mat[2]+64) >> 7;
	// 		ext_d3[1] = (in_d2[0] * tran_mat[3] + in_d2[1] * tran_mat[4] + in_d2[2] * tran_mat[5]+64) >> 7;
	// 		ext_d3[2] = (in_d2[0] * tran_mat[6] + in_d2[1] * tran_mat[7] + in_d2[2] * tran_mat[8]+64) >> 7;
	// 		ext_d3[0] = ext_d3[0];   // 
	// 		ext_d3[1] = ext_d3[1] + (128 << 2);     // 
	// 		ext_d3[2] = ext_d3[2] + (128 << 2);     // 
	// 		d3_1[iWidth*y + x] = clip_bits(ext_d3[0], 0, 1023);
	// 		d4_dst[iWidth*y + x] = d3_1[iWidth*y + x];
	// 		d3_2[iWidth*y + x] = clip_bits(ext_d3[1], 0, 1023);
	// 		d3_3[iWidth*y + x] = clip_bits(ext_d3[2], 0, 1023);
	// 	}
	// }

	alg6_func_1(d3_1_dst, d3_2_dst, d3_3_dst, d3_1, d3_2, d3_3);
    // loop 3
	for (unsigned int j = 0; j < iHeight * iWidth * 2; j++) {
		if (j % 4 == 0) {
			src_d3_data[j] = d3_2_dst[j/4];
		} else if (j % 4 == 1) {
			src_d3_data[j] = d3_1_dst[(j-1) / 2];
		} else if (j % 4 == 2) {
			src_d3_data[j] = d3_3_dst[j / 4];
		} else if (j % 4 == 3) {
			src_d3_data[j] = d3_1_dst[(j-1) / 2];
		}
	}
}