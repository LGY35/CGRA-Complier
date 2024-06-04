#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/alg5.hh"
#include "../include/CGRA_define.hh"
#include <string>
#include <iostream>
#define HALF_W ALG5_WIDTH / 2
#define HALF_H ALG5_HEIGHT / 2
void alg5_func(unsigned short d1[ALG5_HEIGHT][ALG5_WIDTH], unsigned short d2[ALG5_HEIGHT][ALG5_WIDTH][3])
 {
	unsigned short(*c1) [HALF_W];
	unsigned short(*c2)[HALF_W];
	unsigned short(*c3)[HALF_W];
	unsigned short(*c4) [HALF_W];
	c1 = (unsigned short(*)[HALF_W])malloc(HALF_H * sizeof(unsigned short[HALF_W]));
	c2 = (unsigned short(*)[HALF_W])malloc(HALF_H * sizeof(unsigned short[HALF_W]));
	c3 = (unsigned short(*)[HALF_W])malloc(HALF_H * sizeof(unsigned short[HALF_W]));
	c4 = (unsigned short(*)[HALF_W])malloc(HALF_H * sizeof(unsigned short[HALF_W]));
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


    //=================output for debug==========================
    logi("writing matrix c1/c2/c3/c4 to alg5_func_c1/c2/c3/c4_output.raw\n");
 
    FILE* fp1 = NULL;
    FILE* fp2 = NULL;
    FILE* fp3 = NULL;
    FILE* fp4 = NULL;
    char alg5_c1_dst_path[256]= {"../dst_pic/isp_alg5_func_c1_output.raw"};
    char alg5_c2_dst_path[256]= {"../dst_pic/isp_alg5_func_c2_output.raw"};
    char alg5_c3_dst_path[256]= {"../dst_pic/isp_alg5_func_c3_output.raw"};
    char alg5_c4_dst_path[256]= {"../dst_pic/isp_alg5_func_c4_output.raw"};


	fopen_s(&fp1, alg5_c1_dst_path, "wb");
    fopen_s(&fp2, alg5_c2_dst_path, "wb");
    fopen_s(&fp3, alg5_c3_dst_path, "wb");
    fopen_s(&fp4, alg5_c4_dst_path, "wb");

	if(fp1==NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL)
	{
		logi("can not write the alg5_func_c1/c2/c3/c4_output\n");
		return;
	}
	else{
		logi("read alg5_func_c1/c2/c3/c4_output file pointer OK\n");
		for(int i = 0; i < HALF_H; i++)
		{
			for(int j = 0 ; j < HALF_W; j++)
			{
				fwrite(&*(*(c1+i)+j),2,1,fp1);
                fwrite(&*(*(c2+i)+j),2,1,fp2);
                fwrite(&*(*(c3+i)+j),2,1,fp3);
                fwrite(&*(*(c4+i)+j),2,1,fp4);
			}
		}
		
        logi("write alg5_func_c1/c2/c3/c4_output file is done\n");
	}
	fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);


    //================check output write is coorect or not================
    // cout<<"=======================alg5 write and read check begins ============================"<<endl;
	// fopen_s(&fp1, alg5_c1_dst_path, "rb");
    // fopen_s(&fp2, alg5_c2_dst_path, "rb");
    // fopen_s(&fp3, alg5_c3_dst_path, "rb");
    // fopen_s(&fp4, alg5_c4_dst_path, "rb");



	// if(fp1==NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL)
	// {
	// 	logi("can not read the alg5_func_c1/c2/c3/c4_output\n");
	// 	return;
	// }
	// else {
    //     logi("read alg5_func_c1/c2/c3/c4_output file pointer OK\n");
	// 	unsigned short* ptr1 = NULL;
    //     unsigned short* ptr2 = NULL;
    //     unsigned short* ptr3 = NULL;
    //     unsigned short* ptr4 = NULL;
	// 	ptr1 = (unsigned short*)malloc(sizeof(unsigned short));
    //     ptr2 = (unsigned short*)malloc(sizeof(unsigned short));
    //     ptr3 = (unsigned short*)malloc(sizeof(unsigned short));
    //     ptr4 = (unsigned short*)malloc(sizeof(unsigned short));
	// 	for (int i = 0; i < HALF_H; i++) 
	// 	{
	// 		for (int j = 0; j < HALF_W; j++) 
	// 		{				
	// 			fread(ptr1, 2, 1, fp1);
    //             fread(ptr2, 2, 1, fp2);
    //             fread(ptr3, 2, 1, fp3);
    //             fread(ptr4, 2, 1, fp4);
	// 			unsigned short temp1 = *ptr1;
    //             unsigned short temp2 = *ptr2;
    //             unsigned short temp3 = *ptr3;
    //             unsigned short temp4 = *ptr4;
	// 			if( (*(*(c1+i)+j)) != temp1) { cout<<" alg5_func_c1["<<i<<"]["<<j<<"] doesn't match algorithm output "; abort(); return; }
    //             if( (*(*(c2+i)+j)) != temp2) { cout<<" alg5_func_c2["<<i<<"]["<<j<<"] doesn't match algorithm output"; abort(); return; }
    //             if( (*(*(c3+i)+j)) != temp3) { cout<<" alg5_func_c3["<<i<<"]["<<j<<"] doesn't match algorithm output"; abort(); return; }
    //             if( (*(*(c4+i)+j)) != temp4) { cout<<" alg5_func_c4["<<i<<"]["<<j<<"] doesn't match algorithm output"; abort(); return; }
	// 		}
	// 	}	
	// 	fclose(fp1);
    //     fclose(fp2);
    //     fclose(fp3);
    //     fclose(fp4);
	// 	free(ptr1);
    //     free(ptr2);
    //     free(ptr3);
    //     free(ptr4);
	// 	ptr1 = NULL;
    //     ptr2 = NULL;
    //     ptr3 = NULL;
    //     ptr4 = NULL;
		
	// }
    // cout<<"=======================alg5 write and read check is done ============================"<<endl;

















    //=================output for debug==========================

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
}