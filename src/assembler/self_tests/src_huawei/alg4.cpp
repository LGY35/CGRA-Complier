#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 完全展开，但是用宏

// 定义宏来处理每个 m, n 情况
#define PROCESS_REF_BLOCK(m, n, i, j, c, width, height, d1_ce, ref_block) \
    do { \
        ref_block[0][0] = d1_ce[(i + m - 2) * (width / 2 + 12) + j + n - 2 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[0][1] = d1_ce[(i + m - 2) * (width / 2 + 12) + j + n - 1 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[0][2] = d1_ce[(i + m - 2) * (width / 2 + 12) + j + n + 0 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[0][3] = d1_ce[(i + m - 2) * (width / 2 + 12) + j + n + 1 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[0][4] = d1_ce[(i + m - 2) * (width / 2 + 12) + j + n + 2 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[1][0] = d1_ce[(i + m - 1) * (width / 2 + 12) + j + n - 2 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[1][1] = d1_ce[(i + m - 1) * (width / 2 + 12) + j + n - 1 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[1][2] = d1_ce[(i + m - 1) * (width / 2 + 12) + j + n + 0 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[1][3] = d1_ce[(i + m - 1) * (width / 2 + 12) + j + n + 1 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[1][4] = d1_ce[(i + m - 1) * (width / 2 + 12) + j + n + 2 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[2][0] = d1_ce[(i + m + 0) * (width / 2 + 12) + j + n - 2 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[2][1] = d1_ce[(i + m + 0) * (width / 2 + 12) + j + n - 1 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[2][2] = d1_ce[(i + m + 0) * (width / 2 + 12) + j + n + 0 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[2][3] = d1_ce[(i + m + 0) * (width / 2 + 12) + j + n + 1 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[2][4] = d1_ce[(i + m + 0) * (width / 2 + 12) + j + n + 2 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[3][0] = d1_ce[(i + m + 1) * (width / 2 + 12) + j + n - 2 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[3][1] = d1_ce[(i + m + 1) * (width / 2 + 12) + j + n - 1 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[3][2] = d1_ce[(i + m + 1) * (width / 2 + 12) + j + n + 0 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[3][3] = d1_ce[(i + m + 1) * (width / 2 + 12) + j + n + 1 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[3][4] = d1_ce[(i + m + 1) * (width / 2 + 12) + j + n + 2 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[4][0] = d1_ce[(i + m + 2) * (width / 2 + 12) + j + n - 2 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[4][1] = d1_ce[(i + m + 2) * (width / 2 + 12) + j + n - 1 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[4][2] = d1_ce[(i + m + 2) * (width / 2 + 12) + j + n + 0 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[4][3] = d1_ce[(i + m + 2) * (width / 2 + 12) + j + n + 1 + c * (width / 2 + 12) * (height / 2 + 12)]; \
        ref_block[4][4] = d1_ce[(i + m + 2) * (width / 2 + 12) + j + n + 2 + c * (width / 2 + 12) * (height / 2 + 12)]; \
    } while(0)



// 定义宏来处理 sad 的计算
#define CALCULATE_SAD(central_block, ref_block, sad) \
    do { \
        sad += abs(central_block[0][0] - ref_block[0][0]); \
        sad += abs(central_block[0][1] - ref_block[0][1]); \
        sad += abs(central_block[0][2] - ref_block[0][2]); \
        sad += abs(central_block[0][3] - ref_block[0][3]); \
        sad += abs(central_block[0][4] - ref_block[0][4]); \
        sad += abs(central_block[1][0] - ref_block[1][0]); \
        sad += abs(central_block[1][1] - ref_block[1][1]); \
        sad += abs(central_block[1][2] - ref_block[1][2]); \
        sad += abs(central_block[1][3] - ref_block[1][3]); \
        sad += abs(central_block[1][4] - ref_block[1][4]); \
        sad += abs(central_block[2][0] - ref_block[2][0]); \
        sad += abs(central_block[2][1] - ref_block[2][1]); \
        sad += abs(central_block[2][2] - ref_block[2][2]); \
        sad += abs(central_block[2][3] - ref_block[2][3]); \
        sad += abs(central_block[2][4] - ref_block[2][4]); \
        sad += abs(central_block[3][0] - ref_block[3][0]); \
        sad += abs(central_block[3][1] - ref_block[3][1]); \
        sad += abs(central_block[3][2] - ref_block[3][2]); \
        sad += abs(central_block[3][3] - ref_block[3][3]); \
        sad += abs(central_block[3][4] - ref_block[3][4]); \
        sad += abs(central_block[4][0] - ref_block[4][0]); \
        sad += abs(central_block[4][1] - ref_block[4][1]); \
        sad += abs(central_block[4][2] - ref_block[4][2]); \
        sad += abs(central_block[4][3] - ref_block[4][3]); \
        sad += abs(central_block[4][4] - ref_block[4][4]); \
    } while(0)

// 定义宏来处理每个 m, n 的操作
#define PROCESS_MN_BLOCK(m, n, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum) \
    do { \
        PROCESS_REF_BLOCK(m, n, i, j, c, width, height, d1_ce, ref_block); \
        CALCULATE_SAD(central_block, ref_block, sad); \
        weight = (sad > sad_thr) ? 0 : (sad_thr - sad); \
        weight_sum += weight; \
        filter_sum += weight * ref_block[2][2]; \
    } while(0)

// 使用宏定义展开所有的 m 和 n 的组合
#define PROCESS_ALL_MN_BLOCKS(i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum) \
    do { \
        /* m = -4 */ \
        PROCESS_MN_BLOCK(-4, -4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-4, -3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-4, -2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-4, -1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-4,  0, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-4,  1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-4,  2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-4,  3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-4,  4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        /* m = -3 */ \
        PROCESS_MN_BLOCK(-3, -4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-3, -3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-3, -2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-3, -1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-3,  0, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-3,  1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-3,  2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-3,  3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-3,  4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        /* m = -2 */ \
        PROCESS_MN_BLOCK(-2, -4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-2, -3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-2, -2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-2, -1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-2,  0, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-2,  1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-2,  2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-2,  3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-2,  4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        /* m = -1 */ \
        PROCESS_MN_BLOCK(-1, -4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-1, -3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-1, -2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-1, -1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-1,  0, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-1,  1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-1,  2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-1,  3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(-1,  4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        /* m = 0 (跳过 0, 0) */ \
        PROCESS_MN_BLOCK(0, -4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(0, -3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(0, -2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(0, -1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(0,  1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(0,  2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(0,  3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(0,  4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        /* m = 1 */ \
        PROCESS_MN_BLOCK(1, -4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(1, -3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(1, -2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(1, -1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(1,  0, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(1,  1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(1,  2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(1,  3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(1,  4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        /* m = 2 */ \
        PROCESS_MN_BLOCK(2, -4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(2, -3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(2, -2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(2, -1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(2,  0, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(2,  1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(2,  2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(2,  3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(2,  4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        /* m = 3 */ \
        PROCESS_MN_BLOCK(3, -4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(3, -3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(3, -2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(3, -1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(3,  0, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(3,  1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(3,  2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(3,  3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(3,  4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        /* m = 4 */ \
        PROCESS_MN_BLOCK(4, -4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(4, -3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(4, -2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(4, -1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(4,  0, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(4,  1, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(4,  2, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(4,  3, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
        PROCESS_MN_BLOCK(4,  4, i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum); \
    } while(0)




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
// 	for (int i = 25; i >= 0; i--)  // ii = 1
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
	unsigned int * d1_c = (unsigned int *)malloc((width / 2) * (height / 2) * 4 * sizeof(unsigned int));
	unsigned int * d1_ce = (unsigned int*)malloc((width / 2 + 12) * (height / 2 + 12) * 4 * sizeof(unsigned int));
    unsigned int i = 0,j = 0;

	const unsigned short INV_TAB64A[65] = { 0x1FFF, 0x1FFF, 0x1000, 0x0AAA, 0x0800, 0x0666, 0x0555, 0x0492,
		0x0400, 0x038E, 0x0333, 0x02E9, 0x02AB, 0x0276, 0x0249, 0x0222,
		0x0200, 0x01E2, 0x01C7, 0x01AF, 0x019A, 0x0186, 0x0174, 0x0164,
		0x0155, 0x0148, 0x013B, 0x012F, 0x0125, 0x011A, 0x0111, 0x0108,
		0x0100, 0x00F8, 0x00F1, 0x00EA, 0x00E4, 0x00DD, 0x00D8, 0x00D2,
		0x00CD, 0x00C8, 0x00C3, 0x00BE, 0x00BA, 0x00B6, 0x00B2, 0x00AE,
		0x00AB, 0x00A7, 0x00A4, 0x00A1, 0x009E, 0x009B, 0x0098, 0x0095,
		0x0092, 0x0090, 0x008D, 0x008B, 0x0089, 0x0086, 0x0084, 0x0082, 0x0080 };
		
	for (unsigned int k = 0; k < (height*width/4); k++)// ii = 1
	{
		if(k % (width/2) == 0 && k != 0)
			i++;
		j = k % (width/2);
		d1_c[i * width / 2 + j] = d1in[i * 2 * width + j * 2];
		d1_c[i * width / 2 + j + (width / 2) * (height / 2)] = d1in[i * 2 * width + j * 2 + 1];
		d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2] = d1in[(i * 2 + 1) * width + j * 2];
		d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3] = d1in[(i * 2 + 1) * width + j * 2 + 1];
	}

	unsigned int c = 0;i = 0;j = 0;
	//subloop1中心数据块
	for (unsigned int k = 0; k < 4 * (height/2) * (width/2); k++)
	{	
		c = k / ((height/2) * (width/2));
		i = (k / (width/2)) % (height/2);
		j = k % (width / 2);
		d1_ce[(6 + i) * (width / 2 + 12) + 6 + j + c * (width / 2 + 12) * (height / 2 + 12)] = d1_c[i *  width / 2 + j + c * (width / 2) * (height / 2)];
	}
	c = 0;i = 0;j = 0;
	//subloop2左侧边界填充
	for (unsigned int k = 0; k < 4 * (height/2) * 6; k++)
	{	
		c = k / (height/2);
		i = 6 + (k / 6) % (height/2);
		j = k % 6;
		d1_ce[i * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)] = d1_c[(i - 6) *  width / 2 + c * (width / 2) * (height / 2)];
	}
	c = 0;i = 0;j = 0;
	//subloop3右侧边界填充
	for (unsigned int k = 0; k < 4 * (height/2) * 6; k++)
	{	
		c = k / (height/2);
		i = 6 + (k / 6) % (height/2);
		j = width / 2 + 6 + k % 6;
		d1_ce[i * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)] = d1_c[(i - 6) *  width / 2 + width / 2 - 1 + c * (width / 2) * (height / 2)];
	}
	c = 0;i = 0;j = 0;
	//subloop4顶部边界填充
	for (unsigned int k = 0; k < 4 * 6 * (width/2+12); k++)
	{	
		// c = k / (6 * (width/2+12));
		if(k % (6 * (width/2+12)) == 0 && k != 0)
			c++;
		// i = (k / (width/2+12)) % 6;
		if(k != 0 && k % (width/2+12) == 0)
			i++;
		j = k % (width/2+12);
		d1_ce[i * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)] = d1_c[6 * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)];
	}
	c = 0;i = 0;j = 0;
	//subloop5底部边界填充
	for (unsigned int k = 0; k < 4 * 6 * (width/2+8); k++)
	{	
		c = k / (6 * (width/2+12));
		i = height / 2 + 6 + (k / (width/2+12)) % 6;
		j = k % (width/2+12);
		d1_ce[i * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)] = d1_c[(height / 2 + 5) * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)];
	}

	int central_block[9][9] = { 0 };
	int ref_block[9][9] = { 0 };
	int filter_sum = 0;
	int weight_sum = 0;
	int sad = 0;
	int weight = 0;
	unsigned int div_coef, shft;
	int sad_thr = 160 * 25;  
	for(unsigned int k = 0; k < 4 * (height*width/4); k++)
	{
		c = k / (height*width/4);
		i = 6 + (k / (width/2)) % (height/2);
		j = 6 + k % (width / 2);
				
				// for (int y = -2; y <= 2; y++)
				// 	for (int x = -2; x <= 2; x++)
				// 		central_block[y + 2][x + 2] = d1_ce[(i + y) * (width / 2 + 12) + j + x + c * (width / 2 + 12) * (height / 2 + 12)];
				central_block[0][0] = d1_ce[(i - 2) * (width / 2 + 12) + j - 2 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = -2, x = -2
				central_block[0][1] = d1_ce[(i - 2) * (width / 2 + 12) + j - 1 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = -2, x = -1
				central_block[0][2] = d1_ce[(i - 2) * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)];     // y = -2, x = 0
				central_block[0][3] = d1_ce[(i - 2) * (width / 2 + 12) + j + 1 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = -2, x = 1
				central_block[0][4] = d1_ce[(i - 2) * (width / 2 + 12) + j + 2 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = -2, x = 2

				central_block[1][0] = d1_ce[(i - 1) * (width / 2 + 12) + j - 2 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = -1, x = -2
				central_block[1][1] = d1_ce[(i - 1) * (width / 2 + 12) + j - 1 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = -1, x = -1
				central_block[1][2] = d1_ce[(i - 1) * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)];     // y = -1, x = 0
				central_block[1][3] = d1_ce[(i - 1) * (width / 2 + 12) + j + 1 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = -1, x = 1
				central_block[1][4] = d1_ce[(i - 1) * (width / 2 + 12) + j + 2 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = -1, x = 2

				central_block[2][0] = d1_ce[(i) * (width / 2 + 12) + j - 2 + c * (width / 2 + 12) * (height / 2 + 12)];     // y = 0, x = -2
				central_block[2][1] = d1_ce[(i) * (width / 2 + 12) + j - 1 + c * (width / 2 + 12) * (height / 2 + 12)];     // y = 0, x = -1
				central_block[2][2] = d1_ce[(i) * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)];         // y = 0, x = 0
				central_block[2][3] = d1_ce[(i) * (width / 2 + 12) + j + 1 + c * (width / 2 + 12) * (height / 2 + 12)];     // y = 0, x = 1
				central_block[2][4] = d1_ce[(i) * (width / 2 + 12) + j + 2 + c * (width / 2 + 12) * (height / 2 + 12)];     // y = 0, x = 2

				central_block[3][0] = d1_ce[(i + 1) * (width / 2 + 12) + j - 2 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = 1, x = -2
				central_block[3][1] = d1_ce[(i + 1) * (width / 2 + 12) + j - 1 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = 1, x = -1
				central_block[3][2] = d1_ce[(i + 1) * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)];     // y = 1, x = 0
				central_block[3][3] = d1_ce[(i + 1) * (width / 2 + 12) + j + 1 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = 1, x = 1
				central_block[3][4] = d1_ce[(i + 1) * (width / 2 + 12) + j + 2 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = 1, x = 2

				central_block[4][0] = d1_ce[(i + 2) * (width / 2 + 12) + j - 2 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = 2, x = -2
				central_block[4][1] = d1_ce[(i + 2) * (width / 2 + 12) + j - 1 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = 2, x = -1
				central_block[4][2] = d1_ce[(i + 2) * (width / 2 + 12) + j + c * (width / 2 + 12) * (height / 2 + 12)];     // y = 2, x = 0
				central_block[4][3] = d1_ce[(i + 2) * (width / 2 + 12) + j + 1 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = 2, x = 1
				central_block[4][4] = d1_ce[(i + 2) * (width / 2 + 12) + j + 2 + c * (width / 2 + 12) * (height / 2 + 12)]; // y = 2, x = 2
								
				
				weight_sum = 0;
				filter_sum = 0;

				//================================================================
				// 替换原来的 m n for 循环
				PROCESS_ALL_MN_BLOCKS(i, j, c, width, height, d1_ce, central_block, ref_block, sad, sad_thr, weight, weight_sum, filter_sum);
				//================================================================

				weight_sum += sad_thr;
				filter_sum += sad_thr * central_block[2][2];

				//================================================================
				// tnr_div64(weight_sum, &div_coef, &shft);
				// 内联的 tnr_div64 函数逻辑
				unsigned int nbit = 0, idx = 0;

				// for (unsigned int i = 25; i >= 0; i--) {
				// 	if (((weight_sum >> i) & 0x01) != 0) {
				// 		nbit = i + 1;
				// 		break;
				// 	}
				// }
				// 手动展开 for 循环, 模拟逐位检查行为，并在找到第一个有效位后立即退出
				if (((weight_sum >> 25) & 0x01) != 0) {
					nbit = 26;
				} else if (((weight_sum >> 24) & 0x01) != 0) {
					nbit = 25;
				} else if (((weight_sum >> 23) & 0x01) != 0) {
					nbit = 24;
				} else if (((weight_sum >> 22) & 0x01) != 0) {
					nbit = 23;
				} else if (((weight_sum >> 21) & 0x01) != 0) {
					nbit = 22;
				} else if (((weight_sum >> 20) & 0x01) != 0) {
					nbit = 21;
				} else if (((weight_sum >> 19) & 0x01) != 0) {
					nbit = 20;
				} else if (((weight_sum >> 18) & 0x01) != 0) {
					nbit = 19;
				} else if (((weight_sum >> 17) & 0x01) != 0) {
					nbit = 18;
				} else if (((weight_sum >> 16) & 0x01) != 0) {
					nbit = 17;
				} else if (((weight_sum >> 15) & 0x01) != 0) {
					nbit = 16;
				} else if (((weight_sum >> 14) & 0x01) != 0) {
					nbit = 15;
				} else if (((weight_sum >> 13) & 0x01) != 0) {
					nbit = 14;
				} else if (((weight_sum >> 12) & 0x01) != 0) {
					nbit = 13;
				} else if (((weight_sum >> 11) & 0x01) != 0) {
					nbit = 12;
				} else if (((weight_sum >> 10) & 0x01) != 0) {
					nbit = 11;
				} else if (((weight_sum >> 9) & 0x01) != 0) {
					nbit = 10;
				} else if (((weight_sum >> 8) & 0x01) != 0) {
					nbit = 9;
				} else if (((weight_sum >> 7) & 0x01) != 0) {
					nbit = 8;
				} else if (((weight_sum >> 6) & 0x01) != 0) {
					nbit = 7;
				} else if (((weight_sum >> 5) & 0x01) != 0) {
					nbit = 6;
				} else if (((weight_sum >> 4) & 0x01) != 0) {
					nbit = 5;
				} else if (((weight_sum >> 3) & 0x01) != 0) {
					nbit = 4;
				} else if (((weight_sum >> 2) & 0x01) != 0) {
					nbit = 3;
				} else if (((weight_sum >> 1) & 0x01) != 0) {
					nbit = 2;
				} else if (((weight_sum >> 0) & 0x01) != 0) {
					nbit = 1;
				} else {
					nbit = 0;
				}
				// 后续逻辑
				if (weight_sum <= 63) {
					div_coef = INV_TAB64A[weight_sum];
					shft = 0;
				} else {
					idx = weight_sum >> (nbit - 6);
					div_coef = INV_TAB64A[idx];
					shft = nbit - 6;
				}

		//================================================================
				d1_c[(i - 6) * width / 2 + (j - 6) + c * (width / 2) * (height / 2)] = ((long long)filter_sum * div_coef + (4096 << shft)) >> (13 + shft);

	}

	i = 0;j = 0;
	for (unsigned int k = 0; k < (height*width/4); k++)// ii = 1
	{	
		if(k % (width/2) == 0 && k != 0)
			i++;
		j = k % (width/2);
		d1out[i * 2 * width + j * 2] = d1_c[i * width / 2 + j];
		d1out[i * 2 * width + j * 2] = d1_c[i * width / 2 + j];
		d1out[i * 2 * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2)];
		d1out[(i * 2 + 1) * width + j * 2] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 2];
		d1out[(i * 2 + 1) * width + j * 2 + 1] = d1_c[i * width / 2 + j + (width / 2) * (height / 2) * 3];
	}
	free(d1_c);
	free(d1_ce);
}