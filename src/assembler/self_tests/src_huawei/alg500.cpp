#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alg5.h"
#define HALF_W ALG5_WIDTH / 2
#define HALF_H ALG5_HEIGHT / 2
unsigned short(*c1) [HALF_W];   //指针c1 指向一个长度为 HALF_W 的无符号短整型数组。
unsigned short(*c2)[HALF_W];
unsigned short(*c3)[HALF_W];
unsigned short(*c4) [HALF_W];
int sum = 0;
void alg5_func(short d1[ALG5_HEIGHT][ALG5_WIDTH], unsigned short d2[ALG5_HEIGHT][ALG5_WIDTH][3])
 {
	// unsigned short(*c1) [HALF_W];
	// unsigned short(*c2)[HALF_W];
	// unsigned short(*c3)[HALF_W];
	// unsigned short(*c4) [HALF_W];
    //每个 malloc 调用分配 HALF_H 行的内存，每行有 HALF_W 个 unsigned short 类型的元素。总共分配的内存大小为 HALF_H * HALF_W * sizeof(unsigned short)。
    //每次 malloc 返回的指针被强制转换为 unsigned short(*)[HALF_W] 类型，并赋值给相应的指针变量。
    //malloc 函数返回一个 void* 类型的指针，表示它可以指向任何类型的数据。所以需要强制类型组转换
	// c1 = (unsigned short(*)[HALF_W])malloc(HALF_H * sizeof(unsigned short[HALF_W]));
	// c2 = (unsigned short(*)[HALF_W])malloc(HALF_H * sizeof(unsigned short[HALF_W]));
	// c3 = (unsigned short(*)[HALF_W])malloc(HALF_H * sizeof(unsigned short[HALF_W]));
	// c4 = (unsigned short(*)[HALF_W])malloc(HALF_H * sizeof(unsigned short[HALF_W]));
    int RowIdx = 0, ColIdx, RowPos, ColPos;
    //   original code 
    /*
    根据 RowIdx 和 ColIdx 的奇偶性，将 d1 中的数据分配到四个不同的二维数组指针 c1、c2、c3 和 c4 中。
        如果 RowIdx 和 ColIdx 都是偶数，将 d1[RowIdx][ColIdx] 的值分配给 c1。
        如果 RowIdx 是偶数而 ColIdx 是奇数，将 d1[RowIdx][ColIdx] 的值分配给 c2。
        如果 RowIdx 是奇数而 ColIdx 是偶数，将 d1[RowIdx][ColIdx] 的值分配给 c3。
        如果 RowIdx 和 ColIdx 都是奇数，将 d1[RowIdx][ColIdx] 的值分配给 c4。
    */
    for(int RowIdx=0; RowIdx<ALG5_HEIGHT; RowIdx++) {
        for(int ColIdx=0; ColIdx<ALG5_WIDTH; ColIdx++) {
            int RowPos = RowIdx / 2;
            int ColPos = ColIdx / 2;
            if((RowIdx % 2 == 0) && (ColIdx % 2 == 0)) {
                *(*(c1+RowPos)+ColPos) = d1[RowIdx][ColIdx];
            }
            else if ((RowIdx % 2 == 0) && (ColIdx % 2 == 1)) {
                * (*(c2 + RowPos) + ColPos) = d1[RowIdx][ColIdx];
            }
            else if ((RowIdx % 2 == 1) && (ColIdx % 2 == 0)) {
				*(*(c3 + RowPos) + ColPos) = d1[RowIdx][ColIdx];
            }
            else if ((RowIdx % 2 == 1) && (ColIdx % 2 == 1)) {
				*(*(c4 + RowPos) + ColPos) = d1[RowIdx][ColIdx];
            }
        }
    }
    /*
    根据 RowIdx 和 ColIdx 的奇偶性，从 c1、c2、c3 和 c4 中读取数据，并生成三维数组 d2 的值。
        如果 RowIdx 和 ColIdx 都是偶数，d2[RowIdx][ColIdx] 的第一个元素从 c1 读取，第二个元素是 c2 和 c3 的平均值，第三个元素从 c4 读取。
        如果 RowIdx 是偶数而 ColIdx 是奇数，d2[RowIdx][ColIdx] 的三个元素分别从 c1、c2 和 c3 读取。
        如果 RowIdx 是奇数而 ColIdx 是偶数，d2[RowIdx][ColIdx] 的三个元素分别从 c1、c2 和 c3 读取。
        如果 RowIdx 和 ColIdx 都是奇数，d2[RowIdx][ColIdx] 的第一个元素从 c1 读取，第二个元素是 c2 和 c3 的平均值，第三个元素从 c4 读取。
    */
    for(int RowIdx=0; RowIdx<ALG5_HEIGHT; RowIdx++) {
        for(int ColIdx=0; ColIdx<ALG5_WIDTH; ColIdx++) {
            int RowPos = RowIdx / 2;
            int ColPos = ColIdx / 2;
            if((RowIdx % 2 == 0) && (ColIdx % 2 == 0)) {
                d2[RowIdx][ColIdx][0] = *(*(c1 + RowPos) + ColPos);
                d2[RowIdx][ColIdx][1] = (*(*(c2 + RowPos) + ColPos) + *(*(c3 + RowPos) + ColPos)) / 2;
                d2[RowIdx][ColIdx][2] = *(*(c4 + RowPos) + ColPos);
            }
            else if ((RowIdx % 2 == 0) && (ColIdx % 2 == 1)) {
                d2[RowIdx][ColIdx][0] = *(*(c1 + RowPos) + ColPos);
                d2[RowIdx][ColIdx][1] = *(*(c2 + RowPos) + ColPos);
                d2[RowIdx][ColIdx][2] = *(*(c3 + RowPos) + ColPos);
            }
            else if ((RowIdx % 2 == 1) && (ColIdx % 2 == 0)) {
                d2[RowIdx][ColIdx][0] = *(*(c1 + RowPos) + ColPos);
				d2[RowIdx][ColIdx][1] = *(*(c2 + RowPos) + ColPos);
				d2[RowIdx][ColIdx][2] = *(*(c3 + RowPos) + ColPos);
            }
            else if ((RowIdx % 2 == 1) && (ColIdx % 2 == 1)) {
                d2[RowIdx][ColIdx][0] = *(*(c1 + RowPos) + ColPos);
				d2[RowIdx][ColIdx][1] = (*(*(c2 + RowPos) + ColPos) + *(*(c3 + RowPos) + ColPos)) / 2;
				d2[RowIdx][ColIdx][2] = *(*(c4 + RowPos) + ColPos);
            }
        }
    }

//==================== 拆分后的代码
    for (int i = 0; i < ALG5_HEIGHT * ALG5_WIDTH; i++) {
        if (i % ALG5_WIDTH == 0) {
            RowIdx++; // CGRA 无法使用除法
        }
        ColIdx = i % ALG5_WIDTH;
        RowPos = RowIdx / 2;
        ColPos = ColIdx / 2;
        if((RowIdx % 2 == 0) && (ColIdx % 2 == 0)) {
            *(*(c1+RowPos)+ColPos) = d1[RowIdx][ColIdx];
        }
        else if ((RowIdx % 2 == 0) && (ColIdx % 2 == 1)) {
            * (*(c2 + RowPos) + ColPos) = d1[RowIdx][ColIdx];
        }
        else if ((RowIdx % 2 == 1) && (ColIdx % 2 == 0)) {
            *(*(c3 + RowPos) + ColPos) = d1[RowIdx][ColIdx];
        }
        else if ((RowIdx % 2 == 1) && (ColIdx % 2 == 1)) {
            *(*(c4 + RowPos) + ColPos) = d1[RowIdx][ColIdx];
        }
    }
    for (int i = 0; i < ALG5_HEIGHT * ALG5_WIDTH; i++) {
        if (i % ALG5_WIDTH == 0) {
            RowIdx++; // CGRA 无法使用除法
        }
        int ColIdx = i % ALG5_WIDTH;
        int RowPos = RowIdx / 2;
        int ColPos = ColIdx / 2;
        if((RowIdx % 2 == 0) && (ColIdx % 2 == 0)) {
            d2[RowIdx][ColIdx][0] = *(*(c1 + RowPos) + ColPos);
            d2[RowIdx][ColIdx][1] = (*(*(c2 + RowPos) + ColPos) + *(*(c3 + RowPos) + ColPos)) / 2;
            d2[RowIdx][ColIdx][2] = *(*(c4 + RowPos) + ColPos);
        }
        else if ((RowIdx % 2 == 0) && (ColIdx % 2 == 1)) {
            d2[RowIdx][ColIdx][0] = *(*(c1 + RowPos) + ColPos);
            d2[RowIdx][ColIdx][1] = *(*(c2 + RowPos) + ColPos);
            d2[RowIdx][ColIdx][2] = *(*(c3 + RowPos) + ColPos);
        }
        else if ((RowIdx % 2 == 1) && (ColIdx % 2 == 0)) {
            d2[RowIdx][ColIdx][0] = *(*(c1 + RowPos) + ColPos);
            d2[RowIdx][ColIdx][1] = *(*(c2 + RowPos) + ColPos);
            d2[RowIdx][ColIdx][2] = *(*(c3 + RowPos) + ColPos);
        }
        else if ((RowIdx % 2 == 1) && (ColIdx % 2 == 1)) {
            d2[RowIdx][ColIdx][0] = *(*(c1 + RowPos) + ColPos);
            d2[RowIdx][ColIdx][1] = (*(*(c2 + RowPos) + ColPos) + *(*(c3 + RowPos) + ColPos)) / 2;
            d2[RowIdx][ColIdx][2] = *(*(c4 + RowPos) + ColPos);
        }
    }


}

/*

实际应用场景和意义

数据降采样（Downsampling）：
代码通过将原始二维数组 d1 的数据按奇偶行列分布到四个不同的二维数组中，实现了一种数据降采样的效果。这种处理方式可以用于图像处理和计算机视觉中，减少数据量的同时保留重要的信息。
例如，在图像处理应用中，可以通过这种方式将高分辨率图像数据降采样为多个低分辨率图像块，以便于后续的处理和分析。

数据分块和分组（Data Partitioning and Grouping）：
将数据分布到不同的数组中，可以用于数据的分块和分组处理。这在并行计算和分布式计算中尤为重要，可以将数据分配到不同的处理单元中，提高计算效率。
例如，在多线程编程或GPU计算中，可以将数据分块后分配给不同的线程或计算单元进行并行处理，提高整体计算效率。

数据重组和压缩（Data Reorganization and Compression）：
这种处理方式可以用于数据的重组和压缩。通过将原始数据重新排列到不同的数组中，可以实现数据的压缩和简化，便于存储和传输。
例如，在视频编码中，可以通过这种方式将视频帧的数据重新排列，便于压缩算法进行处理，提高压缩效率。


*/