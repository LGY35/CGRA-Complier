#include <iostream>
#include"alg6.h"
#define clip_bits(X, MIN, MAX)  (((X) < (MIN)) ? (MIN) : (((X) > (MAX)) ? (MAX) : (X)))    //限制X的范围
//负责将源图像数据重新分布到目标数组中
//这个函数的三个参数分别对应图像的三个层级
inline void alg6_func_1(	
    unsigned short d3_1_dst[ALG6_WIDTH*ALG6_HEIGHT], 	//d3 是指dimension3，然后123分别指通道
    unsigned short d3_2_dst[ALG6_WIDTH / 2 * ALG6_HEIGHT], 
    unsigned short d3_3_dst[ALG6_WIDTH / 2 * ALG6_HEIGHT], 
    unsigned short d3_1_src[ALG6_WIDTH*ALG6_HEIGHT], 
    unsigned short d3_2_src[ALG6_WIDTH*ALG6_HEIGHT], 
    unsigned short d3_3_src[ALG6_WIDTH*ALG6_HEIGHT]
)
{
	int iHeight = ALG6_HEIGHT;
	int iWidth = ALG6_WIDTH;

	//将 d3_1_src 的数据直接复制到 d3_1_dst：
    // 该循环不存在，因为在调用后的下一个循环会覆盖
	for (int i = 0; i < iWidth * iHeight; i++)
	{
		d3_1_dst[i] = d3_1_src[i];
	}

	//根据 x 的奇偶性，将 d3_2_src 和 d3_3_src 中的数据重新分配到 d3_2_dst 和 d3_3_dst：	
	int ped3_2 = 0, ped3_3 = 0, y = 0, x = 0;
	for (int i = 0; i < iHeight * iWidth; i++)
	{
		if (i % iWidth == 0 && i != 0) {
            y++;
        }
        x = i % iWidth;

        if (x % 2 == 0)	//如果是偶数—：对d_3_2的数据进行处理
        {
            ped3_2 = d3_2_src[iWidth*y + x];//取出源数据
            ped3_2 = clip_bits(ped3_2, 0, 1023);//限制为10bit
            d3_2_dst[y * iWidth / 2 + x / 2] = ped3_2;//放入目标数组。因为目标数组里面是ALG6_WIDTH / 2，所以这里iWidth / 2，x = i % iWidth也要 / 2
        }
        else		//如果是奇数：对d_3_3的数据进行处理
        {
            ped3_3 = d3_3_src[iWidth*y + x];//
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
unsigned short d3_1[ALG6_HEIGHT * ALG6_WIDTH] = { 0 };//存储三个通道经过线性变换、数据调整、数据剪裁之后的结果——数据预处理之后的结果
unsigned short d3_2[ALG6_HEIGHT * ALG6_WIDTH] = { 0 };
unsigned short d3_3[ALG6_HEIGHT * ALG6_WIDTH] = { 0 };
unsigned short d3_1_dst[ALG6_HEIGHT * ALG6_WIDTH] = { 0 };//经过上面的最终处理之后的结果——即重新分布之后的结果
unsigned short d3_2_dst[ALG6_HEIGHT * ALG6_WIDTH / 2] = { 0 };
unsigned short d3_3_dst[ALG6_HEIGHT * ALG6_WIDTH / 2] = { 0 };

//调用 alg6_func_1 进行部分处理，并将处理后的数据重新排列存储到 src_d3_data 数组中。
/*
	src_d3_data：处理后的源数据，将重新排列存储到这个数组中。
	d4_dst：用于存储最终处理后的数据。
	d2_in：输入的二维图像数据，三通道。这三个通道会利用fun_1函数进行处理
*/
void alg6_func(unsigned short src_d3_data[ALG6_HEIGHT * ALG6_WIDTH * 2], unsigned short d4_dst[ALG6_HEIGHT * ALG6_WIDTH], unsigned short d2_in[ALG6_HEIGHT][ALG6_WIDTH][3])
{
	int iHeight = ALG6_HEIGHT;
	int iWidth = ALG6_WIDTH;
	int tran_mat[9] = { 38,75,15,-22,-42,64,64,-54,-10 };
    int x = 0, y = 0;
	//处理 d2_in 数据并转换成 d3_1、d3_2 和 d3_3 数据：
	for (int i = 0; i < iHeight * iWidth; i++)
	{
		if (i % iWidth == 0 && i != 0) {	
            y++;
        }
        x = i % iWidth;

        int in_d2[3];         
        int ext_d3[3];         
		// 逻辑是从 d2_in 中提取三通道数据，通过一个转换矩阵 tran_mat 进行线性变换，生成新的 d3_1、d3_2 和 d3_3 数据。
        in_d2[0] = d2_in[y][x][0];	//这里是每个通道下，逐像素处理，所以这里还是需要放在循环体内
        in_d2[1] = d2_in[y][x][1];
        in_d2[2] = d2_in[y][x][2];
		// 线性变换
        ext_d3[0] = (in_d2[0] * tran_mat[0] + in_d2[1] * tran_mat[1] + in_d2[2] * tran_mat[2]+64) >> 7;//最后的结果除以128，其中加上64实现对结果的四舍五入
        ext_d3[1] = (in_d2[0] * tran_mat[3] + in_d2[1] * tran_mat[4] + in_d2[2] * tran_mat[5]+64) >> 7;//应该是因为tran mat的大小限制在128内
        ext_d3[2] = (in_d2[0] * tran_mat[6] + in_d2[1] * tran_mat[7] + in_d2[2] * tran_mat[8]+64) >> 7;
        // 数据调整
		ext_d3[0] = ext_d3[0];   // 
        ext_d3[1] = ext_d3[1] + (128 << 2);     // (128 << 2) 等价于 128 * 2^2，也就是 128 * 4，结果是 512。
        ext_d3[2] = ext_d3[2] + (128 << 2);     // （1）增加偏移量可以将数据调整到一个适合的范围。例如，如果转换后的数据需要在一个非负的范围内，增加一个常数偏移量可以确保数据不会出现负值。（2）在某些颜色空间转换（例如 RGB 转 YCbCr 或者类似的颜色空间转换）中，转换后的某些通道需要增加一个偏移量，以确保其值在某个范围内。例如，在 YCbCr 颜色空间中，Cr 和 Cb 通常会有一个偏移量，使其中心值在中间，而不是在 0。
        // 数据剪裁
		d3_1[iWidth*y + x] = clip_bits(ext_d3[0], 0, 1023);
        d4_dst[iWidth*y + x] = d3_1[iWidth*y + x];	//用于存储中间处理结果的数组。但在当前的代码片段中没有看到 d4_dst 的进一步使用
        d3_2[iWidth*y + x] = clip_bits(ext_d3[1], 0, 1023);
        d3_3[iWidth*y + x] = clip_bits(ext_d3[2], 0, 1023);
	}

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
	//将 d3_1_dst、d3_2_dst 和 d3_3_dst 的数据重新排列并存储到 src_d3_data：
	for (unsigned int j = 0; j < iHeight * iWidth * 2; j++) {
		if (j % 4 == 0) {	//4的倍数
			src_d3_data[j] = d3_2_dst[j/4];	//直接除以4即可，即src中 4的倍数 = d3_2_dst中 1 2 3 4 ...
		} else if (j % 4 == 1) {
			src_d3_data[j] = d3_1_dst[(j-1) / 2];	//src中 4的倍数+1 的位置 = d3_1_dst中 偶数的位置（5-1/2=2  9-1/2 = 4 13-1/2 = 6）
		} else if (j % 4 == 2) {
			src_d3_data[j] = d3_3_dst[j / 4];		//src中 4的倍数+2 的位置 = d3_3_dst中 1 2 3 4 ...（6/4=1  10/4 = 2 14/4 = 3）
		} else if (j % 4 == 3) {
			src_d3_data[j] = d3_1_dst[(j-1) / 2];	//src中 4的倍数+3 的位置 = d3_1_dst中 奇数的位置（7-1/2=3  11-1/2 = 5 15-1/2 = 7）
		}
		//经过fun1函数处理之后，d3_1_dst 不变，对应上面的奇数偶数；
		//另外两个都变成了原来长度的一半，
	}
}


