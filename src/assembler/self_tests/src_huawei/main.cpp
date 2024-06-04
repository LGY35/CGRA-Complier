// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alg0.h"
#include "alg1.h"
#include "alg2.h"
#include "alg3.h"
#include "alg4.h"
#include "alg5.h"
#include "alg6.h"
#include "alg7.h"
#define SIZE_D1_H (2592)
#define SIZE_D1_W (4608)
#define DEBUG
#ifdef DEBUG
#define logi(...) printf(__VA_ARGS__)
#else
#define logi(...)
#endif
unsigned short src_d1_data[SIZE_D1_H][SIZE_D1_W];
unsigned short dst_d1_data[SIZE_D1_H][SIZE_D1_W];
unsigned short src_d2_data[SIZE_D1_H][SIZE_D1_W][3];
unsigned short dst_d2_data[SIZE_D1_H/2][SIZE_D1_W/2][3];
unsigned short src_d3_data[SIZE_D1_H/2 * SIZE_D1_W/2 * 2];
unsigned short dst_d3_data[SIZE_D1_H / 2 * SIZE_D1_W / 2 * 2];
unsigned short d4_dst[SIZE_D1_H*SIZE_D1_W];
int out_data[GRID_H][GRID_W] = { 0 };
float si;
int main()
{
	FILE *fp = NULL;
	char src_path[256];
	char dst_path[256];
	int i, j;
	unsigned int height = SIZE_D1_H;
	unsigned int width = SIZE_D1_W;
	logi("Input the testimage path: ");
	scanf("%s", src_path);      //change due to compilation error
	fp = fopen( src_path, "rb");
	if (fp == NULL) {
		logi("can not open the testimage\n");
		return 1;
	}
	else {
		logi("read testimage OK\n");
	}
	unsigned short *ptr;
	ptr = (unsigned short *)malloc(width * height * sizeof(unsigned short));
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			fread(ptr, 2, 1, fp);
			src_d1_data[i][j] = *ptr;
			ptr++;
		}
	}
	fclose(fp);
	printf("processing alg0_func\r\n");
	alg0_func(&src_d1_data[0][0], &dst_d1_data[0][0], width, height);
	printf("processing alg1_func\r\n");
	alg1_func2(&out_data[0][0], &dst_d1_data[0][0]);
	int max = out_data[0][0];
	for (i = 0; i < GRID_H; i++) {
		for (int j = 0; j < GRID_W; j++) {
			if (out_data[i][j] > max) max = out_data[i][j];
		}
	}
	if (max > 20000) {
		si = 1.6;
	}
	else {
		si = 2.0;
	}
	printf("processing alg2_func\r\n");
	alg2_func(&dst_d1_data[0][0], &src_d1_data[0][0], width, height,si);
	printf("processing alg3_func\r\n");
	alg3_func(&src_d1_data[0][0], &dst_d1_data[0][0], width, height);
	printf("processing alg4_func\r\n");
	alg4_func(&dst_d1_data[0][0], &src_d1_data[0][0], width, height);
	printf("processing alg5_func\r\n");
	alg5_func(src_d1_data, src_d2_data);
	printf("processing alg1_func1\r\n");
	alg1_func1(dst_d2_data, src_d2_data);
	printf("processing alg6_func\r\n");
	alg6_func(src_d3_data, d4_dst,dst_d2_data);
	logi("pls input image1 path for save:");
	scanf("%s", dst_path);      //change due to compilation error
	fp = fopen(dst_path, "wb");
	if (fp == NULL) {
		logi("can not write the image1\n");
		return 1;
	}
	for (i = 0; i < width / 2 * height / 2 * 2; i++) {
		fwrite(&src_d3_data[i], 2, 1, fp);
	}
	printf("processing alg7_func\r\n");
	alg7_func(d4_dst, dst_d3_data);
	logi("pls input image2 path for save:");
	scanf("%s", dst_path);      //change due to compilation error
	fp = fopen(dst_path, "wb");
	if (fp == NULL) {
		logi("can not write the image2\n");
		return 1;
	}
	for (i = 0; i < width/2*height/2*2; i++) {
		fwrite(&dst_d3_data[i], 2, 1, fp);
	}
	fclose(fp);
	return 0;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单
// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件