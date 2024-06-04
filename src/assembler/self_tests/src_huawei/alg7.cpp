#include "alg7.h"
inline unsigned short alg7_func_1(unsigned short* alg7_1_input, int32_t positionX, int32_t positionY, int32_t deltaX, int32_t deltaY)
{
    int32_t addX = (positionX + 1) > (INIT_XSIZE - 1) ? (INIT_XSIZE - 1) : (positionX + 1);
    int32_t addY = (positionY + 1) > (INIT_YSIZE - 1) ? (INIT_YSIZE - 1) : (positionY + 1);
	unsigned short f11 = alg7_1_input[positionY * INIT_XSIZE + positionX];
	unsigned short f12 = alg7_1_input[positionY * INIT_XSIZE + addX];
	unsigned short f21 = alg7_1_input[addY * INIT_XSIZE + positionX];
	unsigned short f22 = alg7_1_input[addY * INIT_XSIZE + addX];
	unsigned short mid1 = f11 + ((deltaX * (f12 - f11)) >> BITWIDTH1);
	unsigned short mid2 = f21 + ((deltaX * (f22 - f21)) >> BITWIDTH1);
    return (mid1 + (deltaY * (mid2 - mid1) >> BITWIDTH1));
}
void alg7_func(unsigned short src_d3_data[INIT_YSIZE * INIT_XSIZE * 2], unsigned short dst_d3_data[INIT_YSIZE * INIT_XSIZE * 2])
{
	int i = 0, j = 0;
	int rMat[4] = { 887, 512, -512, 887 };
	int32_t positionX;
	int32_t positionY;
	int32_t deltaX;
	int32_t deltaY;
    for (int k = 0; k < INIT_YSIZE * INIT_XSIZE; k++) { 
        if (k % INIT_XSIZE == 0) {
            j++;
        }
        i = k % INIT_XSIZE;

        positionX = (rMat[0] * i + rMat[1] * j) >> BITWIDTH1;
        positionY = (rMat[2] * i + rMat[3] * j) >> BITWIDTH1;
        deltaX = (rMat[0] * i + rMat[1] * j) - (positionX << BITWIDTH1);
        deltaY = (rMat[2] * i + rMat[3] * j) - (positionY << BITWIDTH1);
        if (positionX >= INIT_XSIZE || positionY >= INIT_YSIZE || positionX < 0 || positionY < 0) {
            continue;
        }
        dst_d3_data[j * INIT_XSIZE + i] = alg7_func_1(src_d3_data, positionX, positionY, deltaX, deltaY);
    }
	// for (int j = 0; j < INIT_YSIZE; j++) {
	// 	for (int i = 0; i < INIT_XSIZE; i++) {
	// 		positionX = (rMat[0] * i + rMat[1] * j) >> BITWIDTH1;
	// 		positionY = (rMat[2] * i + rMat[3] * j) >> BITWIDTH1;
	// 		deltaX = (rMat[0] * i + rMat[1] * j) - (positionX << BITWIDTH1);
	// 		deltaY = (rMat[2] * i + rMat[3] * j) - (positionY << BITWIDTH1);
	// 		if (positionX >= INIT_XSIZE || positionY >= INIT_YSIZE || positionX < 0 || positionY < 0) {
	// 			continue;
	// 		}
	// 		dst_d3_data[j * INIT_XSIZE + i] = alg7_func_1(src_d3_data, positionX, positionY, deltaX, deltaY);
	// 	}
	// }
}